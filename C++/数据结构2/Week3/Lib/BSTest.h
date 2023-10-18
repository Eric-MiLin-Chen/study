#ifndef __BSTEST_H
#define __BSTEST_H

struct Ans
{
    int index;
    long long compare;
    Ans(int _index, long long _compare)
    {
        index = _index;
        compare = _compare;
    }
};

Ans FibSearch(const int *arr, const int &target, const int &size);
int min(int a, int b);
Ans BinarySearch(const int *arr, const int &target, const int &size);
Ans InterpolationSearch(const int *arr, int target, int size);

#endif