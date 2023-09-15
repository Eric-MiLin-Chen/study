#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 1010;
int V, M, t[MAXN], v[MAXN], f[MAXN][MAXN];

int main()
{
    cin >> V >> M;
    for (int i = 1; i <= M; i++)
        cin >> t[i] >> v[i];
    // for (int i = 1; i <= M; i++)
    // {
    //     for (int j = 0; j <= T; j++)
    //     {
    //         f[i][j] = f[i - 1][j];
    //         if (j >= v[i])
    //         {
    //             f[i][j] = max(f[i][j], f[i][j - t[i]] + v[i]);
    //         }
    //     }
    // }
    for (int i = 1; i <= M; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            f[i][j] = f[i - 1][j];
            if (j >= t[i])
            {
                f[i][j] = max(f[i][j], f[i - 1][j - t[i]] + v[i]);
            }
        }
    }
    cout << f[M][V] << endl;
    return 0;
}