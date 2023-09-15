// https://zhuanlan.zhihu.com/p/538891353
// http://www.cnblogs.com/zwfymqz/p/8980809.html
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 998244353;
const ll N = (1 << 23);
ll n, m, r[N];
ll a[N], b[N];
ll qpow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}
const ll g = 3;
const ll gi = qpow(3, mod - 2);

void NTT(ll limit, ll *a, ll op)
{
    for (ll i = 1; i < limit; i++)
        if (i < r[i])
            swap(a[i], a[r[i]]);
    for (ll mid = 1; mid < limit; mid <<= 1)
    {
        ll Wn = qpow(op == 1 ? g : gi, (mod - 1) / (mid << 1));
        for (ll j = 0; j < limit; j += mid << 1)
        {
            ll w = 1;
            for (ll i = j; i < j + mid; i++, w = w * Wn % mod)
            {
                ll A1 = a[i], B1 = w * a[i + mid] % mod;
                a[i] = (A1 + B1) % mod;
                a[i + mid] = (A1 - B1 + mod) % mod;
            }
        }
    }
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 0; i <= n; i++)
        scanf("%lld", &a[n - i]);
    for (ll i = 0; i <= m; i++)
        scanf("%lld", &b[m - i]);
    ll limit = 1, bit = 0;
    while (limit <= n + m)
        limit <<= 1, bit++;
    for (ll i = 1; i < limit; i++)
        r[i] = (r[i >> 1] >> 1 | ((i & 1) << (bit - 1)));
    NTT(limit, a, 1);
    NTT(limit, b, 1);
    for (ll i = 0; i <= limit; i++)
    {
        a[i] = a[i] * b[i] % mod;
    }
    NTT(limit, a, -1);
    ll inv = qpow(limit, mod - 2);
    for (ll i = m + n; i >= 0; i--)
        printf("%lld ", a[i] * inv % mod);
}