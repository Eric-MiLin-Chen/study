// https://www.cnblogs.com/kuangbin/archive/2013/07/24/3210565.html 题解
// http://acm.hdu.edu.cn/showproblem.php?pid=4609 原题
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;

struct complex
{
    double real, imag;
    complex(double _real = 0, double _imag = 0)
    {
        real = _real;
        imag = _imag;
    }
};

inline complex operator+(complex a, complex b) { return complex(a.real + b.real, a.imag + b.imag); }
inline complex operator-(complex a, complex b) { return complex(a.real - b.real, a.imag - b.imag); }
inline complex operator*(complex a, complex b) { return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real); }

const double pi = acos(-1.0);
const int MAXN = 400040;
complex x1[MAXN];
int a[MAXN / 4];
ll sum[MAXN], num[MAXN], r[MAXN]; // 100000*100000会超int

void FFT(const ll &limit, complex *a, ll op) // 迭代版
{
    for (ll i = 0; i < limit; i++)
    {
        if (i < r[i])
            swap(a[i], a[r[i]]);
    }
    for (ll mid = 1; mid < limit; mid <<= 1)
    {
        complex W(cos(pi / mid), op * sin(pi / mid));
        for (ll r = mid << 1, j = 0; j < limit; j += r)
        {
            complex w(1, 0);
            for (ll l = 0; l < mid; l++, w = w * W)
            {
                complex x = a[j + l], y = w * a[j + mid + l];
                a[j + l] = x + y;
                a[j + mid + l] = x - y;
            }
        }
    }
}

int main()
{
    int T;
    int n;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
            num[a[i]]++;
        }
        sort(a, a + n);
        int len1 = a[n - 1] + 1;
        int len = 1;
        ll l = 0;
        while (len < 2 * len1)
        {
            len <<= 1;
            l++;
        }
        for (ll i = 0; i < len; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));

        for (int i = 0; i < len1; i++)
            x1[i] = complex(num[i], 0);
        for (int i = len1; i < len; i++)
            x1[i] = complex(0, 0);
        FFT(len, x1, 1);
        for (int i = 0; i < len; i++)
            x1[i] = x1[i] * x1[i];
        FFT(len, x1, -1);
        for (int i = 0; i < len; i++)
            num[i] = (ll)(x1[i].real / len + 0.5);
        len = 2 * a[n - 1];
        // 减掉取两个相同的组合
        for (int i = 0; i < n; i++)
            num[a[i] + a[i]]--;
        // 选择的无序，除以2
        for (int i = 1; i <= len; i++)
        {
            num[i] /= 2;
        }
        sum[0] = 0;
        for (int i = 1; i <= len; i++)
            sum[i] = sum[i - 1] + num[i];
        ll cnt = 0;
        for (int i = 0; i < n; i++)
        {
            cnt += sum[len] - sum[a[i]];
            // 减掉一个取大，一个取小的
            cnt -= (ll)(n - 1 - i) * i;
            // 减掉一个取本身，另外一个取其它
            cnt -= (n - 1);
            // 减掉大于它的取两个的组合
            cnt -= (ll)(n - 1 - i) * (n - i - 2) / 2;
        }
        // 总数
        ll tot = (ll)n * (n - 1) * (n - 2) / 6;
        printf("%.7lf\n", (double)cnt / tot);
    }
    return 0;
}