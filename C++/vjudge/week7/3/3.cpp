#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = pow(10, 9) + 7;

int cnt[11][10][10], T, L, R;

void init()
{
    for (int i = 1; i < 10; i++)
        cnt[1][i][i] = 1;
    for (int i = 2; i < 11; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int u = 0; u < 10; u++)
            {
                if (j == u)
                    cnt[i][j][u] += pow(10, i - 1);
                for (int k = 0; k < 10; k++)
                    cnt[i][j][u] += cnt[i - 1][k][u];
            }
        }
    }
}

ll dp(int n, int u)
{
    if (!n)
        return u ? 0 : 1;
    vector<int> nums;
    while (n)
        nums.push_back(u % 10), n /= 10;
    int last = 0;
    ll ans = 0;
    for (int i = nums.size() - 1; i >= 0; i--)
        int x = nums[i];
    for (int j =)
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &L, &R);
        int temp = L;
    }
}