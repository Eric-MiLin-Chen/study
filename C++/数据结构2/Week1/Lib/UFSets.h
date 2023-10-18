#ifndef _U_F_SETS_H
#define _U_F_SETS_H
#include <iostream>

using namespace std;

template <typename T>
class UFSets;

template <typename T>
struct ElemNode
{ // 数据成员:
    T data;
    int parent;
};

template <typename T>
class UFSets
{
protected: // 并查集的数据成员:
    ElemNode<T> *sets;
    int size; // 辅助函数

public:
    int Find(T e) const;
    int CollapsingFind(T e) const; // 使用折叠规则压缩路径的查找算法
    // 并查集的函数成员:
    UFSets(T es[], int n);
    UFSets(const UFSets &t); // 复制构造函数
    virtual ~UFSets();
    T GetElem(int p) const;
    int GetOrder(T e) const;
    void NormalUnion(T a, T b, bool FindType = 0); // 合并a与b所在的等价类
    void WeightUnion(T a, T b, bool FindType = 0); // 加权合并a与b所在的等价类
    bool Differ(T a, T b);                         // 判断元素a、b是否在同一个等价类
    UFSets &operator=(const UFSets &t);            // 赋值运算符
    // 其他
    void Display();
};

template <typename T>
int UFSets<T>::Find(T e) const
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++; // 求元素e在数组中的下标
    if (p == size)
        return -1; // 集合中不存在元素e
    while (sets[p].parent > -1)
        p = sets[p].parent; // 查找e所在的等价类的根
    return p;
}

template <typename T>
int UFSets<T>::CollapsingFind(T e) const
{
    int i, k, p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        return -1;
    if (sets[p].parent < 0) // 书上缺了此特判
        return p;
    for (i = p; sets[i].parent >= 0; i = sets[i].parent)
        ;
    while (i != sets[p].parent)
    {
        k = sets[p].parent;
        sets[p].parent = i;
        p = k;
    }
    return i;
}

// // 折叠规则压缩路径
// void Coollapsingfind(int i)
// {
//     int j = i;
//     while (parent[j] >= 0) // 寻找树的根节点
//     {
//         j = parent[j];
//     }
//     while (i != j)
//     {
//         int tmp = parent[i];
//         parent[i] = j;
//         i = tmp;
//     }
// }

template <typename T>
UFSets<T>::UFSets(T es[], int n)
{
    size = n;                     // 设置容量
    sets = new ElemNode<T>[size]; // 分配空间
    for (int i = 0; i < size; i++)
    {
        sets[i].data = es[i];
        sets[i].parent = -1;
    }
}

template <typename T>
UFSets<T>::UFSets(const UFSets &t)
{
    size = t.size;                // 设置容量
    sets = new ElemNode<T>[size]; // 分配空间
    for (int i = 0; i < size; i++)
    {
        sets[i].data = t.sets[i].data;
        sets[i].parent = t.sets[i].parent;
    }
}

template <typename T>
UFSets<T>::~UFSets()
{
    delete[] sets;
    size = 0;
    return;
}

template <typename T>
T UFSets<T>::GetElem(int p) const
{
    return sets[p].data;
}

template <typename T>
int UFSets<T>::GetOrder(T e) const
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        return -1; // 集合中不存在元素e
    return p;      // 返回元素下标
}

template <typename T>
void UFSets<T>::NormalUnion(T a, T b, bool FindType)
{
    int r1, r2;
    if (!FindType)
    {
        r1 = Find(a); // 查找a所在等价类的根
        r2 = Find(b); // 查找b所在等价类的根
    }
    else
    {
        r1 = CollapsingFind(a);
        r2 = CollapsingFind(b);
    }
    if (r1 != r2 && r1 != -1 && r2 != -1)
    {
        sets[r1].parent += sets[r2].parent;
        sets[r2].parent = r1; // 合并等价类
    }
}

template <typename T>
void UFSets<T>::WeightUnion(T a, T b, bool FindType)
{
    int r1, r2;
    if (!FindType)
    {
        r1 = Find(a); // 查找a所在等价类的根
        r2 = Find(b); // 查找b所在等价类的根
    }
    else
    {
        r1 = CollapsingFind(a);
        r2 = CollapsingFind(b);
    }
    if (r1 != r2 && r1 != -1 && r2 != -1)
    {
        int temp = sets[r1].parent + sets[r2].parent;
        if (sets[r1].parent <= sets[r2].parent)
        {
            sets[r2].parent = r1;
            sets[r1].parent = temp;
        }
        else
        {
            sets[r1].parent = r2;
            sets[r2].parent = temp;
        }
    }
}

template <typename T>
bool UFSets<T>::Differ(T a, T b)
{
    if (Find(a) == Find(b))
        return true;
    else
        return false;
}

template <typename T>
UFSets<T> &UFSets<T>::operator=(const UFSets &t)
{
    size = t.size;                // 设置容量
    sets = new ElemNode<T>[size]; // 分配空间
    for (int i = 0; i < size; i++)
    {
        sets[i].data = t.sets[i].data;
        sets[i].parent = t.sets[i].parent;
    }
    return *this;
}

template <typename T>
void UFSets<T>::Display()
{
    for (int i = 0; i < size; i++)
        printf("%-3d", i);
    cout << endl;
    for (int i = 0; i < size; i++)
        printf("%-3d", sets[i].parent);
    cout << endl;
    for (int i = 0; i < size; i++)
        printf("%-3c", sets[i].data);
    cout << endl
         << endl;
}

#endif