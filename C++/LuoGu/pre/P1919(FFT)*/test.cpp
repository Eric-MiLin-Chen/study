#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 5000010;
const double pi = acos(-1);
string s;
ll n, m, limit, c[MAXN];

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

void FFT(const ll &limit, complex *a, ll op) // 迭代版
{
    for (ll i = 0; i < limit; i++)
    {
        if (i < c[i])
            swap(a[i], a[c[i]]);
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
        c[i] = (c[i >> 1] >> 1) | ((i & 1) << (l - 1));
    FFT(limit, a, 1);
    FFT(limit, b, 1);
    for (ll i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    FFT(limit, a, -1);
    // 上面都是FFT板子，不解释
    memset(c, 0, sizeof(c)); // c数组要清零，因为前面有赋值
    for (ll i = 0; i <= n + m + 1; i++)
        c[i] = a[i].real / limit + 0.5; // 模仿FFT输出时赋值
    for (ll i = 0; i <= n + m; i++)
    { // 进位
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    limit = n + m + 1;
    while (c[limit])
    { // 还有前面没有处理的
        c[limit + 1] += c[limit] / 10;
        c[limit] %= 10;
        limit++;
    }
    for (ll i = limit - 1; i >= 0; i--)
        printf("%lld", c[i]); // 输出
    return 0;
}