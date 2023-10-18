#include <bits/stdc++.h>
using namespace std;

template<typename T>
class smallest_heap<>



int main()
{
    priority_queue<int, vector<int>, greater<int>> pq;
    int n = 0, ans = 0, tmp;
    cin >> n;
    while(n--)
    {
        cin >> tmp;
        pq.push(tmp);
    }
    while(pq.size() >= 2)
    {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        ans += a + b;
        pq.push(a + b);
    }
    cout << ans << endl;
}