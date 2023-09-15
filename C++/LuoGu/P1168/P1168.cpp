#include <bits/stdc++.h>
using namespace std;

int main()
{
    priority_queue<int> largest_heap;
    priority_queue<int, vector<int>, greater<int>> smallest_heap;
    int n = 0, tmp, mid = -1;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> tmp;
        if(mid == -1)
        {
            mid = tmp;
            cout << mid << endl;
            continue;
        }
        if(tmp > mid) smallest_heap.push(tmp);
        else largest_heap.push(tmp);
        if(i % 2 == 1) 
        {
            while(smallest_heap.size() != largest_heap.size())
            {
                if(smallest_heap.size() > largest_heap.size())
                {
                    largest_heap.push(mid);
                    mid = smallest_heap.top();
                    smallest_heap.pop();
                }
                else if(smallest_heap.size() < largest_heap.size())
                {
                    smallest_heap.push(mid);
                    mid = largest_heap.top();
                    largest_heap.pop();
                }
            }
            cout << mid << endl;
        }
    }
    return 0;
}