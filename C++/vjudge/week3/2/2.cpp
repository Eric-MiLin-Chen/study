#include <iostream>
using namespace std;
typedef long long ll;

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y), x0 = x, y0 = y;
    x = y0;
    y = x0 - (a / b) * y0;
    return d;
}

int main()
{
    int a, b, x, y = 0;
    scanf("%d%d", &a, &b);
    exgcd(a, b, x, y);
    printf("%d", (x % b + b) % b);
    return 0;
}