#include <iostream>
#include <math.h>
#define ll long long
#define il inline
#define rep(i, s, t) for (int i = (s); i <= (t); i++)
#define rev_rep(i, s, t) for (int i = (s); i >= (t); i--)
#define pt(x) putchar(x)
using namespace std;
il int ci()
{
    char ch;
    int f = 1;
    while (!isdigit(ch = getchar()))
        f = ch == '-' ? -1 : 1;
    int x = ch ^ '0';
    while (isdigit(ch = getchar()))
        x = (x * 10) + (ch ^ '0');
    return f * x;
}
template <typename T>
il bool chk_max(T &x, T y) { return (x < y ? (x = y, 1) : 0); }

const int mod = 998244353;
enum
{
    N = 270023
};
il ll qpow(ll a, ll b)
{
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
        {
            ans = ans * a % mod;
        }
    return ans;
}
il ll inv(ll x) { return qpow(x, mod - 2); }

const ll g0 = 3;
const ll invg0 = inv(g0);
int rev[N], init_rev_n;
il void init_rev(int n)
{
    if (n == init_rev_n)
        return;
    int t = log2(n);
    init_rev_n = n;
    rep(i, 1, n - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
}
int NTT(ll *A, int n, int IDFT)
{
    init_rev(n);
    rep(i, 1, n - 1) if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int t = 1; t < n; t <<= 1)
    {
        ll w0 = qpow(IDFT == -1 ? invg0 : g0, (mod - 1) / (t * 2));
        for (int i = 0; i < n; i += t * 2)
        {
            for (int j = 0, w = 1; j < t; j++, w = w * w0 % mod)
            {
                ll x = A[i + j], y = A[i + t + j];
                A[i + j] = (x + w * y) % mod;
                A[i + t + j] = (x - w * y) % mod;
            }
        }
    }
    if (IDFT == -1)
    {
        ll invn = inv(n);
        rep(i, 0, n - 1) A[i] = A[i] * invn % mod;
    }
    return n;
}
il int set2(int n) { return 1 << ((int)log2(n - 1) + 1); } // 原代码的模板都进行了压行处理

ll t[N], s[N];
int a[N], b[N];

int main()
{
    int n = ci(), m = ci();
    rep(i, 1, n) a[ci()]++;
    rep(i, 1, m) b[i] = a[i];
    sort(b, b + m + 1);
    int T = unique(b, b + m + 1) - b - 1;
    rep(d, 1, T)
    {
        rep(i, 1, m * 2) t[i] = a[i] >= b[d];
        int L = set2(m * 2);
        NTT(t, L, 1);
        rep(i, 0, L - 1) t[i] = t[i] * t[i] % mod;
        NTT(t, L, -1);
        rep(i, 1, m * 2) s[i] += 1ll * (b[d] - b[d - 1]) * ((t[i] + mod) % mod);
    }
    ll ans = 0, ans2 = 0;
    rep(i, 1, m * 2) if (chk_max(ans, s[i] / 2)) ans2 = i;
    printf("%lld %lld\n", ans, ans2);
    return 0;
}