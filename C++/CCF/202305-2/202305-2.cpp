#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main()
{
    int n, d;
    cin >> n >> d;

    vector<vector<vector<ll>>> M(3, vector<vector<ll>>(n, vector<ll>(d)));
    vector<ll> W(n);
    vector<vector<ll>> tmp(n, vector<ll>(n, 0));
    vector<vector<ll>> ans(n, vector<ll>(d, 0));

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < d; ++k)
                scanf("%lld", &M[i][j][k]);

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < d; k++)
        {
            ll tmpq = M[0][i][k];
            for (int j = 0; j < n; j++)
                tmp[i][j] += tmpq * M[1][j][k];
        }
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &W[i]);
        for (int j = 0; j < n; j++)
            tmp[i][j] *= W[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            ll tmpwqk = tmp[i][k];
            for (int j = 0; j < d; j++)
                ans[i][j] += tmpwqk * M[2][k][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
            printf("%lld ", ans[i][j]);
        printf("\n");
    }
    return 0;
}
