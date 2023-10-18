#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "Sort.h"
using namespace std;

void test(Ans (*func)(int arr[], int n))
{
    int arr[10];
    for (int i = 0; i < 10; ++i)
        arr[i] = 10 - i;
    for (int i = 0; i < 10; ++i)
        cout << arr[i] << " ";
    cout << endl;
    Ans ans = func(arr, 10);
    for (int i = 0; i < 10; ++i)
        cout << arr[i] << " ";
    cout << endl;
    cout << ans.CompareCount << " " << ans.MoveCount << endl;
}

Ans TestFunc(Ans (*func)(int arr[], int n), const int arr[], int n)
{
    int arrcpy[n];
    memcpy(arrcpy, arr, n * sizeof(arr[0]));
    // for (int i = 0; i < 10; ++i)
    //     cout << arrcpy[i] << " ";
    // cout << endl;
    // Ans ans = func(arrcpy, 10);
    // for (int i = 0; i < 10; ++i)
    //     cout << arrcpy[i] << " ";
    // cout << endl;
    // cout << ans.CompareCount << " " << ans.MoveCount << endl;
    return func(arrcpy, n);
}

vector<int> LoadData(const string FileName)
{
    ifstream file("./../../Data/" + FileName);
    vector<int> Data;
    int tmp;
    while (file >> tmp)
        Data.push_back(tmp);
    return Data;
}

void Display(long long (*result)[4][9][2])
{
    for (int f = 0; f < 8; f++)
    {
        cout << "Function " << f + 1 << ": " << endl;
        for (int type = 0; type < 4; type++)
        {
            cout << "    File Type " << type + 1 << endl;
            for (int dtype = 0; dtype < 2; dtype++)
            {
                cout << "    ";
                for (int size = 0; size < 9; size++)
                    cout << result[f][type][size][dtype] << " ";
                cout << endl;
            }
        }
    }
}

void SaveData(long long (*result)[4][9][2])
{
    ofstream file;
    file.open("./../../Data/File.txt", ios::out);
    for (int f = 0; f < 8; f++)
    {
        for (int type = 0; type < 4; type++)
        {
            for (int dtype = 0; dtype < 2; dtype++)
            {
                for (int size = 0; size < 9; size++)
                {
                    file << result[f][type][size][dtype] << " ";
                }
                file << "\n";
            }
        }
    }
}

int main()
{
    long long result[8][4][9][2] = {0}; // Function TestFileType TestFileSize CompareCount/MoveCount
    string TestFileType[4] = {"PartiallySortedData", "RandomData", "ReversedData", "SortedData"};
    string TestFileSize[9] = {{"32"}, {"64"}, {"128"}, {"256"}, {"512"}, {"1024"}, {"2048"}, {"4096"}, {"8192"}};
    Ans (*func[8])(int arr[], int n) = {insertionSort, shellSort, bubbleSort, quickSort, selectionSort, heapSort, mergeSort, radixSort};

    for (int type = 0; type < 4; type++)
    {
        for (int size = 0; size < 9; size++)
        {
            vector<int> vData = LoadData(TestFileType[type] + TestFileSize[size] + ".txt");
            int Data[vData.size()];
            for (int i = 0; i < vData.size(); i++)
                Data[i] = vData[i];
            for (int f = 0; f < 8; f++)
            {
                Ans tmp = TestFunc(func[f], Data, vData.size());
                result[f][type][size][0] = tmp.CompareCount;
                result[f][type][size][1] = tmp.MoveCount;
            }
        }
    }

    Display(result);

    SaveData(result);

    return 0;
}