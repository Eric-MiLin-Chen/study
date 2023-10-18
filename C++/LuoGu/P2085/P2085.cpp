#include <bits/stdc++.h>
using namespace std;

struct data
{
    int a, b, c, val;
    int n = 1;
    data(){}
    data(int _a, int _b, int _c, int _n):a(_a), b(_b), c(_c), n(_n){}
    bool operator<(const data& _data) const
    {
        return val<_data.val;
    }
    bool operator>(const data& _data) const
    {
        return val>_data.val;
    }
};

int main()
{
    priority_queue<struct data, vector<struct data>, greater<struct data> > pq;
    int n, m;
    cin >> n >> m;
    struct data data[n];
    for (int i = 0; i < n; ++i) 
    {
        cin >> data[i].a >> data[i].b >> data[i].c;
        data[i].val = data[i].a * data[i].n * data[i].n + data[i].b * data[i].n + data[i].c;
        pq.push(data[i]);
    }
    for (int i = 0; i < m; ++i) 
    {
        struct data temp = pq.top();
        cout << temp.val << " ";
        pq.pop();
        temp.n++;
        temp.val = temp.a * temp.n * temp.n + temp.b * temp.n + temp.c;
        pq.push(temp);
    }
    return 0;
}
