#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL ksm(LL a, LL b, LL mod)
{
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}
vector<int> get_gen(int x)
{
    int m = x;
    int phi = x;
    for (int i = 2; i * i <= m; i++)
    {
        if (m % i == 0)
        {
            phi = (LL)phi * (i - 1) / i;
            while (m % i == 0)
                m /= i;
        }
    }
    if (m != 1)
        phi = (LL)phi * (m - 1) / m;
    vector<int> pfac;
    m = phi;
    for (int i = 2; i * i <= m; i++)
    {
        if (m % i == 0)
        {
            pfac.push_back(i);
            while (m % i == 0)
                m /= i;
        }
    }
    if (m != 1)
        pfac.push_back(m);
    vector<int> res;
    for (int k = 1; k < x; k++)
    {
        int f = 1;
        if (gcd(k, x) != 1)
            continue;
        for (int i = 0; i < pfac.size(); i++)
        {
            int xx = pfac[i];
            if (ksm(k, phi / xx, x) == 1)
            {
                f = 0;
                break;
            }
        }
        if (f)
        {
            // 此k为最小原根
            res.push_back(k);
            break;
        }
    }
    int len = res.size();
    if (len)
    {
        int k = res[0];
        res.pop_back();
        for (int i = 1; i <= phi; i++)
            if (gcd(i, phi) == 1)
                res.push_back(ksm(k, i, x));
    }
    return res;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int x;
        scanf("%d", &x);
        auto res = get_gen(x);
        sort(res.begin(), res.end());
        int len = res.size();
        printf("%d\n", len);
        for (int i = 0; i < len; i++)
        {
            printf("%d ", res[i]);
        }
        puts("");
    }
}