#include <bits/stdc++.h>
using namespace std;

const int mac = 1.5e4 + 10;
const int MAXN = 3.2e4 + 10;

int lowbit(int x)
{
    return x & -x;
}
// star_postition
struct node
{
    int x, y;
} a[mac];

int n, c[32050], level[mac];
// 求和
int query(int pos)
{
    int ans = 0;
    while (pos > 0)
    {
        ans += c[pos];
        pos -= lowbit(pos);
    }
    return ans;
}
// 改变单值
void add(int pos)
{
    while (pos <= MAXN)
    {
        c[pos] += 1;
        pos += lowbit(pos);
    }
}

bool cmp(node a, node b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[i].x = x, a[i].y = y;
        }
        sort(a + 1, a + 1 + n, cmp);
        memset(level, 0, sizeof(level));
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++)
        {
            int nb = query(a[i].y + 1);
            level[nb]++;
            add(a[i].y + 1);
        }
        for (int i = 0; i < n; i++)
        {
            printf("%d\n", level[i]);
        }
    }
    return 0;
}
