#include <iostream>
using namespace std;

int city[10005];
int counts[10005];
int moves[10005];
char mod;
int t, n, q;

// int find(int x)
// {
//     return city[x] == x ? x : find(city[x]);
// }

int find(int x)
{
    if (x != city[x])
    {
        int t = city[x];
        city[x] = find(city[x]);
        moves[x] += moves[t];
    }
    return city[x];
}

bool merge(int dst, int src)
{
    int px = find(dst), py = find(src);
    if (px != py)
    {
        city[px] = py;
        counts[py] += counts[px];
        // counts[px] = 0;
        moves[px]++;
        return true;
    }
    return false;
}

int main()
{
    scanf("%d", &t);
    for (int times = 1; times <= t; ++times)
    {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; ++i)
            counts[i] += 1;
        printf("Case %d:\n", times);
        for (int i = 1; i <= n; i++)
            city[i] = i;
        for (int i = 0; i < q; i++)
        {
            getchar();
            scanf("%c", &mod);
            if (mod == 'T')
            {
                int dst, src;
                scanf("%d%d", &dst, &src);
                merge(dst, src);
            }
            else if (mod == 'Q')
            {
                int ball_index;
                scanf("%d", &ball_index);
                int city_index = find(ball_index), trans_time = 0;
                int tmp = ball_index;
                while (tmp != city_index)
                {
                    tmp = city[tmp];
                    trans_time++;
                }
                printf("%d %d %d\n", city_index, counts[city_index], moves[ball_index]);
            }
        }
    }
    return 0;
}