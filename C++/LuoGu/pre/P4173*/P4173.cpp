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
    FFT(limit, a, 1);
    FFT(limit, b, 1);
    for (ll i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    FFT(limit, a, -1);
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