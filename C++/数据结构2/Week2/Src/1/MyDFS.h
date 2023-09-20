#ifndef __MY_DFS_H__
#define __MY_DFS_H__
#include <iostream>
#include "AdjMatrixUndirGraph.h"
using namespace std;

template <typename T>
void _DFS_All(const AdjMatrixUndirGraph<T> &G, int u, int v, int Path[], int &k)
{
    G.SetTag(u, VISITED);
    T temp;
    Path[k++] = u;
    if (u == v)
    {
        for (int i = 0; i < k; i++)
        {
            G.GetElem(Path[i], temp);
            cout << temp;
        }
        cout << endl;
    }
    for (int w = G.FirstAdjVex(u); w != -1; w = G.NextAdjVex(u, w))
    {
        if (G.GetTag(w) == UNVISITED)
            _DFS_All<T>(G, w, v, Path, k);
    }
    G.SetTag(u, UNVISITED); // 一条简单路径处理完，退回一个顶点继续遍历
    k--;
}

template <typename T>
void DFS(const AdjMatrixUndirGraph<T> &G, int u, int v)
{
    int vexNum = G.GetVexNum(), k = 0;
    int *Path = new int[vexNum];
    _DFS_All<T>(G, u, v, Path, k);
    delete[] Path;
    for (int i = 0; i < vexNum; i++)
        G.SetTag(i, UNVISITED);
}

template <typename T>
void DFS(const AdjMatrixUndirGraph<T> &G, T Tu, T Tv)
{
    int u = G.GetOrder(Tu), v = G.GetOrder(Tv);
    DFS(G, u, v);
}

#endif