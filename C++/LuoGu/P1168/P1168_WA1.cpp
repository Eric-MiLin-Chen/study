#include <bits/stdc++.h>
using namespace std;

int main()
{
    priority_queue<int> largest_heap;
    priority_queue<int, vector<int>, greater<int>> smallest_heap;
    int n = 0, tmp;
    cin >> n;
    while(n--)
    {
        cin >> tmp;
        smallest_heap.push(tmp);
        if(smallest_heap.size() > largest_heap.size())
        {
            tmp = smallest_heap.top();
            smallest_heap.pop();
            largest_heap.push(tmp);
        }
        if(smallest_heap.top() < largest_heap.top())
        {
            largest_heap.push(smallest_heap.top());
            smallest_heap.pop();
            smallest_heap.push(largest_heap.top());
            largest_heap.pop();
        }
        if(n % 2 == 0) cout << largest_heap.top() << endl;
    }
    return 0;
}