#include <iostream>
#include <math.h>
using namespace std;
typedef long long ll;

const int MAXN = 300010;
const int mod = 998244353;
int n, l, r[MAXN];
ll a[MAXN], b[MAXN], src[MAXN], ans[MAXN];

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

inline int inv(int x) { return ksm(x, mod - 2); }

const int g = 3, gi = inv(g);

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

void Fast_Fast_TLE(int len, ll *src, ll *ans)
{
    if (len == 1)
    {
        ans[0] = inv(src[0]);
        return;
    }
    Fast_Fast_TLE((len + 1) >> 1, src, ans);
    int limit = 1, bit = 0;
    while (limit <= len + n)
        limit <<= 1, bit++;
    for (int i = 1; i < limit; i++)
        r[i] = (r[i >> 1] >> 1 | ((i & 1) << (bit - 1)));
    for (int i = 0; i < limit; i++)
        a[i] = src[i], b[i] = (i < (len + 1) >> 1 ? ans[i] : 0);
    NTT(a, limit, 1);
    NTT(b, limit, 1);
    for (int i = 0; i < limit; i++)
        a[i] = b[i] * ((2 - a[i] * b[i] % mod + mod) % mod) % mod;
    NTT(a, limit, -1);
    int invup = inv(limit);
    for (int i = 0; i < len; i++)
        ans[i] = a[i] * invup % mod;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &src[i]);
    Fast_Fast_TLE(n, src, ans);
    for (int i = 0; i < n; i++)
        printf("%lld ", ans[i]);
}
