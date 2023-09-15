#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 100003;

ll f(ll a, ll b)
{
    ll s = 1;
    while (b)
    {
        if (b % 2 == 1)
            s = (s * a) % MAXN;
        b = b / 2;
        a = (a * a) % MAXN;
    }
    return s;
}

int main()
{
    ll m, n, s = 0;
    scanf("%lld%lld", &m, &n);
    s = (f(m, n) - m * f(m - 1, n - 1) % MAXN + MAXN) % MAXN;
    printf("%lld", s);
    return 0;
}