#ifndef __DIGISTRA_H__
#define __DIGISTRA_H__
#include <iostream>
#include "AdjMatrixUndirNetwork.h"

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int **path, WeightType **dist)
{
    for (int u = 0; u < g.GetVexNum(); u++) // 初始化
        for (int v = 0; v < g.GetVexNum(); v++)
        {
            dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
            if (u != v && dist[u][v] < g.GetInfinity())
                path[u][v] = u;
            else
                path[u][v] = -1;
        }
    for (int k = 0; k < g.GetVexNum(); k++)     // 求A(k)
        for (int i = 0; i < g.GetVexNum(); i++) // 加入k为中间顶点
            for (int j = 0; j < g.GetVexNum(); j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
}

template <class ElemType, class WeightType>
void ShortestPathDij(const AdjMatrixUndirNetwork<ElemType, WeightType> &graph, int v0, int *path, WeightType *dist)
{
    WeightType minVal, infinity = graph.GetInfinity();
    int v, u;
    // 初始化dist和path数组
    for (v = 0; v < graph.GetVexNum(); v++)
    {
        dist[v] = graph.GetWeight(v0, v);
        if (dist[v] == infinity)
            path[v] = -1;
        else
            path[v] = v0;
        graph.SetTag(v, UNVISITED);
    }
    graph.SetTag(v0, VISITED);
    for (int i = 1; i < graph.GetVexNum(); i++)
    { // 找n-1个终点
        minVal = infinity;
        u = v0;
        for (v = 0; v < graph.GetVexNum(); v++) // 找最短的路径
            if (graph.GetTag(v) == UNVISITED && dist[v] < minVal)
            {
                u = v;
                minVal = dist[v];
            }
        graph.SetTag(u, VISITED);
        // 对u的邻接点，修改路径和路径长度
        for (v = graph.FirstAdjVex(u); v != -1; v = graph.NextAdjVex(u, v))
            if (graph.GetTag(v) == UNVISITED &&
                minVal + graph.GetWeight(u, v) < dist[v])
            {
                dist[v] = minVal + graph.GetWeight(u, v);
                path[v] = u;
            }
    }
}

template <typename ElemType, typename WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> CreateNet(int n, int m)
{
    char vexs[n];
    for (int i = 0; i < n; i++)
        vexs[i] = 'A' + i;
    AdjMatrixUndirNetwork<char, int> net(vexs, n);
    for (int i = 0; i < m; i++)
    {
        int u, v, arc;
        cin >> u >> v >> arc;
        if (arc == -1)
            arc = AdjMatrixUndirNetwork<ElemType, WeightType>().GetInfinity();
        net.InsertArc(u, v, arc);
    }
    return net;
}

template <typename ElemType, typename WeightType>
void GetShortestPathDij(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int n, const int &src, const int &dst)
{
    int path[n], dist[n];
    ShortestPathDij(net, src, path, dist);
    int temp = dst, ShortestPathLen = 0, MaxArc = 0, Arc = 0;
    int ShortestPath[n];
    char Vex;
    while (temp != path[temp])
    {
        ShortestPath[ShortestPathLen++] = temp;
        temp = path[temp];
    }
    ShortestPath[ShortestPathLen++] = temp;
    cout << "Shortest Path: ";
    for (int i = ShortestPathLen - 1; i >= 0; i--)
    {
        net.GetElem(ShortestPath[i], Vex);
        Arc = net.GetWeight(ShortestPath[i % ShortestPathLen], ShortestPath[(i - 1 + ShortestPathLen) % ShortestPathLen]);
        Arc = Arc == net.GetInfinity() ? -1 : Arc;
        MaxArc = Arc > MaxArc ? Arc : MaxArc;
        cout << Vex << " ";
    }
    cout << endl;
    cout << "Max Noise: " << MaxArc << endl;
    for (int i = 0; i < n; i++)
        cout << path[i] << "\t";
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << dist[i] << "\t";
    cout << endl;
    return;
}

#endif