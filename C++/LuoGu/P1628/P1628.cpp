#include <bits/stdc++.h>
using namespace std;

priority_queue<string, vector<string>, greater<string>> pq;
int n, flag = 1;
string str, f;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        pq.push(str);
    }
    cin >> f;
    while (!pq.empty())
    {
        str = pq.top();
        pq.pop();
        for (int i = 0; i < f.size(); i++)
        {
            if (f[i] != str[i])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            cout << str << endl;
        flag = 1;
    }

    return 0;
}