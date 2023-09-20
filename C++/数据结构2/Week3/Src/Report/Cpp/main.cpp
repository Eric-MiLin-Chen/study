#include <iostream>
#include <fstream>
#include <string>
#include "BSTest.h"
using namespace std;

int main()
{
    double ansdata[3][3][9][2] = {0}; // 算法 数据类型 数据规模 数据域(内部数据平均比较次数/随机数据平均比较次数)
    int worst[3][3][9] = {0};         // 最坏情况比较次数
    int ASL = 0;
    string DataName[3] = {{"OrderedData"},
                          {"NormalOrderedData"},
                          {"RandomOrderedData"}};
    string fsize[9] = {
        {"32"},
        {"64"},
        {"128"},
        {"256"},
        {"512"},
        {"1024"},
        {"2048"},
        {"4096"},
        {"8192"}};
    int num;
    for (int i = 0; i < 3; i++)
    {
        double compare_sum_BS = 0;
        double compare_sum_FS = 0;
        double compare_sum_IS = 0;
        int worst_compare_BS = 0;
        int worst_compare_FS = 0;
        int worst_compare_IS = 0;
        for (int j = 0; j < 9; j++)
        {
            int size = stoi(fsize[j]);
            int data[size];
            ifstream file("./../../../Data/" + DataName[i] + fsize[j] + ".txt");
            // cout << DataName[i] + fsize[j] + ".txt" << endl;
            for (int i = 0; i < size; i++)
                file >> data[i];
            file.close();
            for (int target = 0; target < 10 * size; target++)
            {
                int tmp;
                tmp = BinarySearch(data, target, size).compare;
                worst_compare_BS = tmp > worst_compare_BS ? tmp : worst_compare_BS;
                compare_sum_BS += tmp;

                tmp = FibSearch(data, target, size).compare;
                worst_compare_FS = tmp > worst_compare_FS ? tmp : worst_compare_FS;
                compare_sum_FS += tmp;

                tmp = InterpolationSearch(data, target, size).compare;
                worst_compare_IS = tmp > worst_compare_IS ? tmp : worst_compare_IS;
                compare_sum_IS += tmp;
            }
            ansdata[0][i][j][1] = compare_sum_BS / size;
            ansdata[1][i][j][1] = compare_sum_FS / size;
            ansdata[2][i][j][1] = compare_sum_IS / size;
            worst[0][i][j] = worst_compare_BS;
            worst[1][i][j] = worst_compare_FS;
            worst[2][i][j] = worst_compare_IS;
            compare_sum_BS = 0;
            compare_sum_FS = 0;
            compare_sum_IS = 0;
            for (int target = 0; target < size; target++)
            {
                compare_sum_BS += BinarySearch(data, data[target], size).compare;
                compare_sum_FS += FibSearch(data, data[target], size).compare;
                compare_sum_IS += InterpolationSearch(data, data[target], size).compare;
            }
            ansdata[0][i][j][0] = compare_sum_BS / size;
            ansdata[1][i][j][0] = compare_sum_FS / size;
            ansdata[2][i][j][0] = compare_sum_IS / size;
        }
    }
    for (int f = 0; f < 3; f++)
    {
        cout << "func" << f << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "   " << DataName[i] << endl;
            for (int d = 0; d < 2; d++)
            {
                cout << "        ";
                for (int j = 0; j < 9; j++)
                {
                    cout << ansdata[f][i][j][d] << " ";
                }
                cout << endl;
            }
        }
    }

    for (int f = 0; f < 3; f++)
    {
        cout << "func" << f << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "   " << DataName[i] << endl;
            cout << "        ";
            for (int j = 0; j < 9; j++)
                cout << worst[f][i][j] << " ";
            cout << endl;
        }
    }
    ofstream outfile;
    outfile.open("./../../../Data/file.txt", ios::out);
    for (int f = 0; f < 3; f++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int d = 0; d < 2; d++)
            {
                for (int j = 0; j < 9; j++)
                {
                    outfile << ansdata[f][i][j][d] << " ";
                }
                outfile << "\n";
            }
        }
    }
    outfile.close();
    ofstream outfile;
    outfile.open("./../../../Data/worst.txt", ios::out);
    for (int f = 0; f < 3; f++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 9; j++)
                outfile << worst[f][i][j] << " ";
            outfile << endl;
        }
    }
    outfile.close();
    return 0;
}
