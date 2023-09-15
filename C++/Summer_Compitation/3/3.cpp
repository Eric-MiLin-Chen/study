#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
    double nums[10000];
    int size = 0, term = 1;

    while (cin >> nums[size++])
    {
        if (getchar() == '\n')
        {
            sort(nums, nums + size);
            printf("Case %d: %.1lf\n", term++, nums[size - 1]);
            size = 0;
        }
    }
    return 0;
}