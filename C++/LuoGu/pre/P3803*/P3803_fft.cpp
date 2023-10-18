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

int main()
{
    scanf("%lld%lld", &m, &n);
    for (ll i = 0; i <= m; i++)
        scanf("%lf", &a[m - i].real);
    for (ll i = 0; i <= n; i++)
        scanf("%lf", &b[n - i].real);
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
    for (ll i = m + n; i >= 0; i--)
        printf("%d ", (int)(a[i].real / limit + 0.5));
    return 0;
}