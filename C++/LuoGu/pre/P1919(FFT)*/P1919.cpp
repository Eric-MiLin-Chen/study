#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 5000010;
const double pi = acos(-1);
string s;
ll n, m, limit, r[MAXN];

struct complex
{
    double real, imag;
    complex(double _real = 0, double _imag = 0)
    {
        real = _real;
        imag = _imag;
    }
} a[MAXN], b[MAXN];

inline complex operator+(complex a, complex b) { return complex(a.real + b.real, a.imag + b.imag); }
inline complex operator-(complex a, complex b) { return complex(a.real - b.real, a.imag - b.imag); }
inline complex operator*(complex a, complex b) { return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real); }

void FFT(complex *a, const ll &limit, ll op) // 迭代版
{
    for (ll i = 0; i < limit; i++)
    {
        if (i < r[i])
            swap(a[i], a[r[i]]); // 拆分多项式
    }
    for (ll mid = 1; mid < limit; mid <<= 1)
    {
        complex W(cos(pi / mid), op * sin(pi / mid)); // 单位根
        for (ll j = 0; j < limit; j += mid << 1)
        {
            complex w(1, 0);
            for (ll i = j; i < j + mid; i++, w = w * W)
            {
                complex x = a[i], y = w * a[i + mid];
                a[i] = x + y;
                a[i + mid] = x - y;
            }
        }
    }
}

// void FFT(int limit, complex *a, int type) // 递归版
// {
//     if (limit == 1)
//         return; // 只有一个常数项
//     complex a1[limit >> 1], a2[limit >> 1];
//     for (int i = 0; i < limit; i += 2) // 根据下标的奇偶性分类
//         a1[i >> 1] = a[i], a2[i >> 1] = a[i + 1];
//     FFT(limit >> 1, a1, type);
//     FFT(limit >> 1, a2, type);
//     complex Wn = complex(cos(2.0 * pi / limit), type * sin(2.0 * pi / limit)), w = complex(1, 0);
//     // Wn为单位根，w表示幂
//     for (int i = 0; i < (limit >> 1); i++, w = w * Wn) // 这里的w相当于公式中的k
//     {
//         complex tmp = w * a2[i];
//         a[i] = a1[i] + tmp;
//         a[i + (limit >> 1)] = a1[i] - tmp; // 利用单位根的性质，O(1)得到另一部分
//     }
// }

int main()
{
    // ios::sync_with_stdio(0);
    cin >> s;
    n = s.size() - 1;
    for (ll i = 0; i <= n; i++)
        a[n - i].real = s[i] - 48;
    cin >> s;
    m = s.size() - 1;
    for (ll i = 0; i <= m; i++)
        b[m - i].real = s[i] - 48;
    // 正式模版
    limit = 1;
    ll l = 0;
    while (limit <= n + m)
    {
        limit <<= 1;
        l++;
    }
    for (ll i = 0; i < limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    FFT(a, limit, 1);
    FFT(b, limit, 1);
    for (ll i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    FFT(a, limit, -1);
    // 上面都是FFT板子，不解释
    memset(r, 0, sizeof(r)); // c数组要清零，因为前面有赋值
    for (ll i = 0; i <= n + m + 1; i++)
        r[i] = a[i].real / limit + 0.5; // 模仿FFT输出时赋值
    for (ll i = 0; i <= n + m; i++)
    { // 进位
        r[i + 1] += r[i] / 10;
        r[i] %= 10;
    }
    limit = n + m + 1;
    while (r[limit])
    { // 还有前面没有处理的
        r[limit + 1] += r[limit] / 10;
        r[limit] %= 10;
        limit++;
    }
    for (ll i = limit - 1; i >= 0; i--)
        printf("%lld", r[i]); // 输出
    return 0;
}