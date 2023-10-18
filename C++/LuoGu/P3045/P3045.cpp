#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct cow
{
    int c, p;
    bool perchased = false;
};

struct cmp_p
{
    bool operator()(const cow *x, const cow *y) const { return x->p > y->p; }
};

struct cmp_c
{
    bool operator()(const cow *x, const cow *y) const { return x->c > y->c; }
};

struct cmp_pminc
{
    bool operator()(const cow *x, const cow *y) const { return x->p - x->c > y->p - y->c; }
};

priority_queue<cow *, vector<cow *>, cmp_p> pq_p;
priority_queue<cow *, vector<cow *>, cmp_c> pq_c;
priority_queue<cow *, vector<cow *>, cmp_pminc> pq_pminc;
cow cows[50005];
int n, k, ans = 0;
ll m;

int main()
{
    cin >> n >> k >> m;
    for (int i = 0; i < n; ++i)
    {
        cin >> cows[i].p >> cows[i].c;
        pq_p.push(cows + i);
        pq_c.push(cows + i);
    }
    for (int i = 0; i < min(n, k); ++i)
    {
        m -= pq_c.top()->c;
        if (m < 0)
        {
            cout << ans;
            return 0;
        }
        ans++;
        pq_c.top()->perchased = true;
        pq_pminc.push(pq_c.top());
        pq_c.pop();
    }
    for (int i = k; i < n; ++i)
    {
        while (pq_p.top()->perchased)
            pq_p.pop();
        while (pq_c.top()->perchased)
            pq_c.pop();
        if (pq_p.top()->p < pq_c.top()->c + pq_pminc.top()->p - pq_pminc.top()->c)
        {
            m -= pq_p.top()->p;
            pq_p.top()->perchased = true;
            pq_pminc.push(pq_p.top());
            pq_p.pop();
        }
        else
        {
            m -= pq_c.top()->c + pq_pminc.top()->p - pq_pminc.top()->c;
            pq_c.top()->perchased = true;
            pq_c.pop();
            pq_pminc.pop();
        }
        if (m < 0)
            break;
        ans++;
    }
    cout << ans;
    return 0;
}
