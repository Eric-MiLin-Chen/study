#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    ll n = 0, ans = 0, tmp;
    cin >> n;
    while (n--)
    {
        cin >> tmp;
        pq.push(tmp);
    }
    while (pq.size() >= 2)
    {
        ll a = pq.top();
        pq.pop();
        ll b = pq.top();
        pq.pop();
        ans += a + b;
        pq.push(a + b);
    }
    cout << ans << endl;
    return 0;
}