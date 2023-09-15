#include <iostream>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), x0 = x, y0 = y;
    x = y0;
    y = x0 - (a / b) * y0;
    return d;
}

int main()
{
    ll x, y, m, n, L, a, b, c;
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L);
    a = L, b = n - m, c = x - y;
    if (b < 0)
    {
        b = -b;
        c = -c;
    }
    ll ans = exgcd(b, a, x, y);
    if (c % ans)
    {
        cout << "Impossible\n";
    }
    else
    {
        ans = ((x * (c / ans)) % (a / ans) + (a / ans)) % (a / ans);
        cout << ans << endl;
    }
    return 0;
}