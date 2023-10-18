#include <bits/stdc++.h>
using namespace std;

struct cmp
{
    bool operator()(const int *x, const int *y) const { return !(*x > *y); }
};

int n, m, q, t, qy[10000000];
double u, v, p;
priority_queue<int *, vector<int *>, cmp> pq;

int main()
{
    cin >> n >> m >> q >> u >> v >> t;
    p = u / v;
    for (int i = 0; i < n; i++)
    {
        cin >> qy[i];
        pq.push(qy + i);
    }
    for (int i = 0; i < m; i++)
    {
        int *it = pq.top();
        if ((i + 1) % t == 0)
            cout << *it << " ";
        int tmp1 = int(*it * p), tmp2 = *it - tmp1;
        pq.pop();
        qy[n] = tmp1 - q;
        pq.push(qy + n++);
        qy[n] = tmp2 - q;
        pq.push(qy + n++);
        // cout << tmp2 << " " << *(qy.begin() - 1 + n) + 1 << endl;
        for (int j = 0; j < n; j++)
            qy[j] += q;
    }
    cout << endl;
    for (int i = 1; !pq.empty(); i++)
    {
        if (i % t == 0)
            cout << *pq.top() << " ";
        pq.pop();
    }
    return 0;
}