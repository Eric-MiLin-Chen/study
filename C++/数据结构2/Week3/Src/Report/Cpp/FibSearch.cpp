// FibSearch.cpp
#include "BSTest.h"

inline int min(int a, int b)
{
    return a < b ? a : b;
}

Ans FibSearch(const int *arr, const int &target, const int &size)
{
    int fib1 = 0;
    int fib2 = 1;
    int fib = fib1 + fib2;
    int compare = 0;
    while (fib < size)
    {
        fib1 = fib2;
        fib2 = fib;
        fib = fib1 + fib2;
    }
    int offset = -1;
    while (fib > 1)
    {
        int i = min(offset + fib1, size - 1);
        if (arr[i] < target)
        {
            compare++;
            fib = fib2;
            fib2 = fib1;
            fib1 = fib - fib2;
            offset = i;
        }
        else if (arr[i] > target)
        {
            compare++;
            fib = fib1;
            fib2 = fib2 - fib1;
            fib1 = fib - fib2;
        }
        else
        {
            return Ans(i, compare);
        }
    }
    if (fib2 && offset + 1 < size && arr[offset + 1] == target)
    {
        return Ans(offset + 1, compare);
    }
    return Ans(-1, compare);
}
