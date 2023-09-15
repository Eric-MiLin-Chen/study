#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    priority_queue<int, vector<int>, greater<int>> pq;
    cin >> n;
    long long a[n], b[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        pq.push(a[i] + b[0]);
    }
    for (int i = 1; i < n; i++)
        for (int j = 0; j < n / i; j++)
            pq.push(a[j] + b[i]);
    for (int i = 0; i < n; i++)
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    return 0;
}