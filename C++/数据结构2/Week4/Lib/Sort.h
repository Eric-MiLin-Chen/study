#ifndef __SORT_H
#define __SORT_H

struct Ans
{
    long long CompareCount;
    long long MoveCount;
    int RedundancyData;
    Ans(long long _CompareCount = 0, long long _MoveCount = 0, int _RedundancyData = 0) : CompareCount(_CompareCount), MoveCount(_MoveCount), RedundancyData(_RedundancyData) {}
};

Ans insertionSort(int arr[], int n);
Ans shellSort(int arr[], int n);
Ans bubbleSort(int arr[], int n);
Ans quickSort(int arr[], int n);
Ans selectionSort(int arr[], int n);
Ans heapSort(int arr[], int n);
Ans mergeSort(int arr[], int n);
Ans radixSort(int arr[], int n);
#endif