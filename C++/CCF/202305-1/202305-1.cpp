#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
    unordered_map<string, int> dict;
    int n;
    // 输入的第一行包含一个正整数n，表示这盘棋总共有n步。
    scanf("%d", &n);
    // 依次输入第1到第n步棋后的局面
    for (int i = 0; i < n; i++)
    {
        string key = "";
        for (int j = 0; j < 8; j++)
        {
            string tmp;
            cin >> tmp;
            key += tmp;
        }
        dict[key]++;
        cout << dict[key] << endl;
    }
    return 0;
}