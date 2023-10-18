#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    string target;
    cin >> n >> target;

    map<char, int> targetMap;
    for (char c : target)
    {
        targetMap[c]++;
    }

    vector<string> routes(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> routes[i];
    }

    int minLength = -1;

    for (string start : routes)
    {
        map<char, int> currMap;
        int currLength = 0;

        for (char c : start)
        {
            currMap[c]++;
            currLength++;
        }

        bool allCollected = true;

        for (const auto &p : targetMap)
        {
            if (currMap[p.first] < p.second)
            {
                allCollected = false;
                break;
            }
        }

        if (allCollected)
        {
            for (int i = 0; i < n; ++i)
            {
                string end = routes[i];
                if (end[0] == start.back())
                {
                    currLength += (end.length() - 1);
                    minLength = (minLength == -1) ? currLength : min(minLength, currLength);
                }
            }
        }
    }

    cout << minLength << endl;

    return 0;
}
