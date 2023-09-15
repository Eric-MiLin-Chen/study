#include <bits/stdc++.h>
#define MAXN 15005
#define MAXP 32005
using namespace std;

struct star_point
{
    int x, y;
};

star_point star[MAXN];
int n, level[MAXN];

int lowbit(int x)
{
    return (x & -x);
}

void update(int i, int val) // 单点更新
{
    {
        star[i] += val;
        i += lowbit(i); // 由叶子节点向上更新树状数组C，从左往右更新
    }
}
int sum(int i) // 求区间[1,i]内所有元素的和
{
    int ans = 0;
    while (i > 0)
    {
        ans += star[i]; // 从右往左累加求和
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
}