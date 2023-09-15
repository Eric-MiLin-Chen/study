#include <iostream>
#include <string>
using namespace std;

int main()
{
    int T;
    string s, ans = "", temp = "";
    cin >> T;
    while (T--)
    {
        cin >> s;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == 's') i += 14;
            else if (s[i] == '(' || s[i] == ')' || s[i] == ',')
            {
                ans += temp;
                temp = "";
                ans += s[i];
            }
            else
            {
                temp += s[i];
            }
        }
        cout << ans << endl;
        ans = "";
    }
    return 0;
}