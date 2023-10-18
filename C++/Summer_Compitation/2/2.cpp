#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    double cal1, cal2, ans;
    ll term = 1;
    char opt;
    char opts[] = "+-*/";
    while (cin >> cal1)
    {
        cin >> opt;
        if (opt == '+')
        {
            cin >> cal2 >> opt >> ans;
            cal1 += cal2;
        }
        else if (opt == '-')
        {
            cin >> cal2 >> opt >> ans;
            cal1 -= cal2;
        }
        else if (opt == '*')
        {
            cin >> cal2 >> opt >> ans;
            cal1 *= cal2;
        }
        else if (opt == '/')
        {
            cin >> cal2 >> opt >> ans;
            cal1 /= cal2;
        }
        printf("Case %lld: ", term++);
        if (cal1 == ans)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}