#include <iostream>
#define MAXN 10000005
using namespace std;

int boys[MAXN], num[MAXN], max_num, a, b, n;

int find(int x) // 不能递归搜索，会tle
{
    if (x != boys[x])
    {
        boys[x] = find(boys[x]);
    }
    return boys[x];
}

void merge(int src, int dst)
{
    int px = find(src), py = find(dst);
    if (px != py)
    {
        boys[px] = py;
        num[py] += num[px];
        if (num[py] > max_num)
            max_num = num[py];
    }
}

int main()
{
    while (~scanf("%d", &n))
    {
        max_num = 1;
        for (int i = 1; i < MAXN; i++)
        {
            boys[i] = i;
            num[i] = 1;
        }
        while (n--)
        {
            scanf("%d%d", &a, &b);
            merge(a, b);
        }
        printf("%d\n", max_num);
    }
    return 0;
}