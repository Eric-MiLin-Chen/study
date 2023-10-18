#include <iostream>
using namespace std;

int parent[100005] = {0};
bool exist[100005] = {0};

// int find(int x)
// {
//     return parent[x] == x ? x : find(parent[x]);
// }

int find(int x) // 不能递归搜索，会tle
{
    while (x != parent[x])
        x = parent[x];
    return x;
}

bool merge(int a, int b)
{
    int pa = find(a), pb = find(b);
    if (pa != pb)
    {
        parent[pb] = pa;
        return true;
    }
    return false;
}

int main()
{
    int x, y, flag = 1, total = 0;
    while (~scanf("%d%d", &x, &y))
    {
        if (x == -1 && y == -1)
            break;
        if (!x && !y)
        {
            printf("Yes\n");
            continue;
        }
        memset(parent, 0, sizeof(parent));
        memset(exist, 0, sizeof(exist));
        flag = 1;
        total = 1;
        parent[x] = x;
        parent[y] = y;
        exist[x] = exist[y] = 1;
        merge(x, y);
        while (~scanf("%d%d", &x, &y))
        {
            if (!x && !y)
                break;
            if (!exist[x])
            {
                parent[x] = x;
                exist[x] = 1;
                total++;
            }
            if (!exist[y])
            {
                parent[y] = y;
                exist[y] = 1;
                total++;
            }
            if (!merge(x, y))
                flag = 0;
            else
                total--;
        }
        if (flag && total == 1)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}