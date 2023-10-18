// https://zhuanlan.zhihu.com/p/538891353
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int mod = 998244353;
const int MAXN = (1 << 22);
int n, m, sum[MAXN], r[MAXN];
char s1[MAXN], s2[MAXN];
ll a[MAXN], b[MAXN];
ll ksm(ll a, ll b)
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
const int g = 3, gi = ksm(3, mod - 2);

void NTT(ll *a, int limit, int inv)
{
    for (int i = 1; i < limit; i++)
        if (i < r[i])
            swap(a[i], a[r[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        ll W = ksm(inv == 1 ? g : gi, (mod - 1) / (mid << 1));
        for (int j = 0; j < limit; j += mid << 1)
        {
            ll w = 1;
            for (int i = j; i < j + mid; i++, w = w * W % mod)
            {
                ll x = a[i], y = w * a[i + mid] % mod;
                a[i] = (x + y) % mod;
                a[i + mid] = (x - y + mod) % mod;
            }
        }
    }
}
int main()
{
    scanf("%s%s", s1, s2);
    n = strlen(s1) - 1;
    m = strlen(s2) - 1;
    for (int i = 0; i <= n; i++)
    {
        ll x = (s1[n - i] - '0') * 1.0;
        a[i] = x;
    }
    for (int i = 0; i <= m; i++)
    {
        ll x = (s2[m - i] - '0') * 1.0;
        b[i] = x;
    }
    int len = 1, bit = 0;
    while (len <= n + m)
        len <<= 1, bit++;
    for (int i = 1; i < len; i++)
        r[i] = (r[i >> 1] >> 1 | ((i & 1) << (bit - 1)));
    NTT(a, len, 1);
    NTT(b, len, 1);
    for (int i = 0; i < len; i++)
    {
        a[i] = a[i] * b[i] % mod;
        b[i] = 0;
    }
    NTT(a, len, -1);
    ll inv = ksm(len, mod - 2);
    int ans = 0;
    for (int i = 0; i <= len; i++)
    {
        sum[i] = a[i] * inv % mod;
        a[i] = 0;
        ans += sum[i];
        sum[i] = ans % 10;
        ans /= 10;
    }
    while (sum[len] == 0 && len >= 1)
        len--;
    for (int i = len; i >= 0; i--)
    {
        printf("%d", sum[i]);
    }
    printf("\n");
}