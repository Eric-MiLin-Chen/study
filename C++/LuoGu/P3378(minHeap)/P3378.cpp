#include <bits/stdc++.h>
using namespace std;

template<typename T>
class myHeap
{
private:
    vector<T> heap;
    bool type = 0; // 默认小根堆
    // void _sort();//默认小根堆
public:
    myHeap(int _type = 0);
    // ~myHeap();
    void push(const T& value);
    void pop();
    bool empty() const;
    T top() const;
    int size() const;
    void show() const;
};

template<typename T>
myHeap<T>::myHeap(int _type):type(_type)
{
    heap.push_back(0);
}

template<typename T>
void myHeap<T>::show() const
{
    for (T x : heap) cout << x << " ";
    cout << endl;
    return;
}

// template<typename T>
// void myHeap<T>::_sort()
// {
//     int son = heap.size() - 1, father = son / 2;
//     if (!type)
//     {
//         while(heap[son] < heap[father] && father >= 1){
//             if (son % 2 == 1)
//                 swap(heap[son] < heap[son - 1] ? heap[son] : heap[son - 1], heap[father]);
//             else
//                 swap(heap[son], heap[father]);
//             son = father;
//             father = son / 2;
//         }
//     }
//     else
//     {
//         while(heap[son] > heap[father] && father >= 1){
//             if (son % 2 == 1)
//                 swap(heap[son] > heap[son - 1] ? heap[son] : heap[son - 1], heap[father]);
//             else
//                 swap(heap[son], heap[father]);
//             son = father;
//             father = son / 2;
//         }
//     }
// }

template<typename T>
void myHeap<T>::push(const T& value)
{
    heap.push_back(value);
    int son = heap.size() - 1, father = son / 2;
    while(heap[son] < heap[father] && father >= 1){
        swap(heap[son], heap[father]);
        son = father;
        father = son / 2;
    }
}

template<typename T>
void myHeap<T>::pop()
{
    swap(heap[1], heap[heap.size() - 1]);
    heap.pop_back();
    int father = 1, son = 2, len = heap.size() - 1;
	while(son <= len){
		if (son < len && heap[son] > heap[son+1]) son++;
		if (heap[father] > heap[son]){
			swap(heap[father], heap[son]);
			father = son;
            son = father * 2;
		}
        else break;
    }
}

template<typename T>
bool myHeap<T>::empty() const
{
    return heap.size() <= 1;
}

template<typename T>
T myHeap<T>::top() const
{
    return heap[1];
}

template<typename T>
int myHeap<T>::size() const
{
    return heap.size() - 1;
}

int main()
{
    myHeap<int> heap;
    int n, op;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            int tmp;
            cin >> tmp;
            heap.push(tmp);
            break;
        case 2:
            cout << heap.top() << endl;
            break;
        case 3:
            heap.pop();
            break;
        default:
            break;
        }
    }
    return 0;
}

// int main()
// {
//     myHeap<int> heap;
//     for (int i = 0; i < 12; i++) heap.push(i);
//     heap.pop();
//     heap.show();
// }