#include "Sort.h"

// insertionSort
Ans insertionSort(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        _MoveCount++;
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            _CompareCount++;
            arr[j + 1] = arr[j];
            _MoveCount++;
            j--;
        }
        arr[j + 1] = key;
        _MoveCount++;
    }
    return Ans(_CompareCount, _MoveCount);
}

// shellSort
Ans shellSort(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = arr[i];
            _MoveCount++;
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                _CompareCount++;
                arr[j] = arr[j - gap];
                _MoveCount++;
            }
            arr[j] = temp;
            _MoveCount++;
        }
    }
    return Ans(_CompareCount, _MoveCount);
}

// bubbleSort
Ans bubbleSort(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                _CompareCount++;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                _MoveCount += 3;
            }
        }
    }
    return Ans(_CompareCount, _MoveCount);
}

// quickSort
Ans partition(int arr[], int low, int high)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] < pivot)
        {
            i++;
            _CompareCount++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            _MoveCount += 3;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    _MoveCount += 3;
    return Ans(_CompareCount, _MoveCount, i + 1);
}

Ans _quickSort(int arr[], int low, int high)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    if (low < high)
    {
        Ans pivot = partition(arr, low, high);
        int pivotIndex = pivot.RedundancyData;
        Ans tmp1 = _quickSort(arr, low, pivotIndex - 1);
        Ans tmp2 = _quickSort(arr, pivotIndex + 1, high);
        _CompareCount = pivot.CompareCount + tmp1.CompareCount + tmp2.CompareCount;
        _MoveCount = pivot.MoveCount + tmp1.MoveCount + tmp2.MoveCount;
    }
    return Ans(_CompareCount, _MoveCount);
}

Ans quickSort(int arr[], int n)
{
    return _quickSort(arr, 0, n - 1);
}

// selectionSort
Ans selectionSort(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                _CompareCount++;
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        _MoveCount += 3;
    }
    return Ans(_CompareCount, _MoveCount);
}

// heapSort
Ans heapify(int arr[], int n, int i)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
    {
        _CompareCount++;
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        _CompareCount++;
        largest = right;
    }
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        _MoveCount += 3;
        Ans ans = heapify(arr, n, largest);
        _CompareCount += ans.CompareCount;
        _MoveCount += ans.MoveCount;
    }
    return Ans(_CompareCount, _MoveCount);
}

Ans heapSort(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        Ans ans = heapify(arr, n, i);
        _CompareCount += ans.CompareCount;
        _MoveCount += ans.MoveCount;
    }
    for (int i = n - 1; i >= 0; --i)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        _MoveCount += 3;
        Ans ans = heapify(arr, i, 0);
        _CompareCount += ans.CompareCount;
        _MoveCount += ans.MoveCount;
    }
    return Ans(_CompareCount, _MoveCount);
}

// mergeSort
Ans merge(int arr[], int left, int mid, int right)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
        _MoveCount++;
    }
    for (int i = 0; i < n2; ++i)
    {
        R[i] = arr[mid + 1 + i];
        _MoveCount++;
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        _CompareCount++;
        _MoveCount++;
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        _MoveCount++;
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        _MoveCount++;
        j++;
        k++;
    }
    return Ans(_CompareCount, _MoveCount);
}

Ans _mergeSort(int arr[], int left, int right)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        Ans ans_mergeSort1 = _mergeSort(arr, left, mid);
        Ans ans_mergeSort2 = _mergeSort(arr, mid + 1, right);
        Ans ans_merge = merge(arr, left, mid, right);
        _CompareCount = ans_mergeSort1.CompareCount + ans_mergeSort2.CompareCount + ans_merge.CompareCount;
        _MoveCount = ans_mergeSort1.MoveCount + ans_mergeSort2.MoveCount + ans_merge.MoveCount;
    }
    return Ans(_CompareCount, _MoveCount);
}

Ans mergeSort(int arr[], int n)
{
    return _mergeSort(arr, 0, n - 1);
}

// radixSort
Ans getMax(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    int max = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > max)
        {
            _CompareCount++;
            max = arr[i];
            _MoveCount++;
        }
    }
    return Ans(_CompareCount, _MoveCount, max);
}

Ans countSort(int arr[], int n, int exp)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; ++i)
    {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        _MoveCount++;
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; ++i)
    {
        arr[i] = output[i];
        _MoveCount++;
    }
    return Ans(_CompareCount, _MoveCount);
}

Ans radixSort(int arr[], int n)
{
    long long _CompareCount = 0;
    long long _MoveCount = 0;
    Ans ans_getMax = getMax(arr, n);
    int max = ans_getMax.RedundancyData;
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        Ans ans_countSort = countSort(arr, n, exp);
        _CompareCount += ans_countSort.CompareCount;
        _MoveCount += ans_countSort.MoveCount;
    }
    return Ans(_CompareCount, _MoveCount);
}
