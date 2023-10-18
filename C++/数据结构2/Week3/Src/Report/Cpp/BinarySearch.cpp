// Binary Search
#include "BSTest.h"

Ans BinarySearch(const int *arr, const int &target, const int &size)
{
    int left = 0;
    int right = size - 1;
    long long compare = 0;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        compare++;
        if (arr[mid] == target)
            return Ans(mid, compare);
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return Ans(-1, compare);
}
