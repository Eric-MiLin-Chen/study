#include "BSTest.h"

Ans InterpolationSearch(const int *arr, int target, int size)
{
    int low = 0;
    int high = size - 1;
    int compare = 0;
    while (low <= high && target >= arr[low] && target <= arr[high])
    {
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (arr[pos] == target)
        {
            compare++;
            return Ans(pos, compare);
        }
        else if (arr[pos] < target)
        {
            compare++;
            low = pos + 1;
        }
        else
            high = pos - 1;
    }
    return Ans(-1, compare);
}