#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int MAXN = 10005;
int a[MAXN];
int num[MAXN];   //记录每个城市的龙珠个数
int move1[MAXN]; //记录每个龙珠移动的次数
int find(int x)
{
    if (x != a[x])
    {
        int t = a[x];
        a[x] = find(a[x]);
        move1[x] += move1[t]; //别忘了加上父节点的移动次数
    }
    return a[x];
}
void unionn(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    else
    {
        a[x] = y;
        num[y] += num[x];
        move1[x]++;
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int j = 1; j <= t; j++)
    {
        char c[3];
        int n, q;
        scanf("%d %d", &n, &q);
        for (int i = 1; i <= n; i++)
        {
            a[i] = i;   //最开始
            num[i] = 1; //每个城市最开始有一个
            move1[i] = 0;
        }
        printf("Case %d:\n", j);
        for (int ii = 0; ii < q; ii++)
        {
            scanf("%s", c); //这里如果输入%c会是错的哦
            if (c[0] == 'T')
            {
                int x, y;
                scanf("%d %d", &x, &y);
                unionn(x, y);
            }
            else
            {
                int x;
                scanf("%d", &x);
                int id = find(x);
                printf("%d %d %d\n", id, num[id], move1[x]);
            }
        }
    }
    return 0;
}
