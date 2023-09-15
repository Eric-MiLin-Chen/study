#include <iostream>
using namespace std;

int main()
{
    int t;
    long long n, m;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> n >> m;
        cout << (m + 1) * m / 2 + (m + n * m) * n / 2 - m << endl;
    }
    return 0;
}