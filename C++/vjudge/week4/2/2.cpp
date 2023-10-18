#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 20005;
int V, M, v[MAXN], f[MAXN];

int main()
{
    cin >> V >> M;
    for (int i = 1; i <= M; i++)
        cin >> v[i];
    for (int i = 1; i <= M; i++)
    {
        for (int j = V; j >= v[i]; j--)
        {
            f[j] = max(f[j - v[i]] + v[i], f[j]);
        }
    }
    cout << V - f[V] << endl;
    return 0;
}