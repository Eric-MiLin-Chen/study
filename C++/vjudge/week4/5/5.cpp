#include <iostream>
#include <math.h>
using namespace std;
typedef long long ll;

int count(ll num, ll *ans)
{
    int len = 0;
    ll tmp = num;
    while (tmp)
        tmp /= 10, len++;
    while (len--)
    {
        tmp = num / pow(10, len);
        num %= (int)pow(10, len--);
    }
}