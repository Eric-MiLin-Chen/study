#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    ll num;
    ll term = 1;
    while (cin >> num)
    {
        ll comp = 5;
        ll zeros = 0;
        while (comp <= num)
        {
            zeros += num / comp;
            comp *= 5;
        }
        printf("Case %lld: %lld, %lld\n", term++, num, zeros);
    }
    return 0;
}