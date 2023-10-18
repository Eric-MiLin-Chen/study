#ifndef __DFS_FIND_CIRCLE_H__
#define __DFS_FIND_CIRCLE_H__
#include <iostream>
#include "AdjMatrixUndirNetwork.h"
using namespace std;

template <typename ElemType, typename WeightType>
class MiniSpanTreeBreakCircle
{
private:
    AdjMatrixUndirNetwork<ElemType, WeightType> &_graph;
    int *path;
    int VexNum;
    bool circle_exist;
    int path_top;
    int _find(int Vex);
    int *_DFSFindCircle(int i, int &len);
    int *GetCircle(int &len);
    void _Init();

public:
    // AdjMatrixUndirNetwork<ElemType, WeightType> _graph;
    MiniSpanTreeBreakCircle(AdjMatrixUndirNetwork<ElemType, WeightType> &graph);
    ~MiniSpanTreeBreakCircle();
    AdjMatrixUndirNetwork<ElemType, WeightType> GetMST();
};

template <typename ElemType, typename WeightType>
void MiniSpanTreeBreakCircle<ElemType, WeightType>::_Init()
{
    circle_exist = false;
    path_top = -1;
    memset(path, 0, VexNum);
    for (int i = 0; i < VexNum; i++)
        _graph.SetTag(i, UNVISITED);
    return;
}

template <typename Elemtype, typename WeightType>
MiniSpanTreeBreakCircle<Elemtype, WeightType>::MiniSpanTreeBreakCircle(AdjMatrixUndirNetwork<Elemtype, WeightType> &graph) : _graph(graph)
{
    // _graph = graph;
    VexNum = graph.GetVexNum();
    path = new int[VexNum];
    _Init();
}

template <typename Elemtype, typename WeightType>
MiniSpanTreeBreakCircle<Elemtype, WeightType>::~MiniSpanTreeBreakCircle()
{
    if (path != NULL)
        delete[] path;
}

template <typename Elemtype, typename WeightType>
int *MiniSpanTreeBreakCircle<Elemtype, WeightType>::GetCircle(int &len)
{
    _Init();
    for (int i = 0; i < VexNum; i++)
    {
        if (_graph.GetTag(i) == UNVISITED)
            return _DFSFindCircle(i, len);
    }
    return NULL;
}

template <typename Elemtype, typename WeightType>
int *MiniSpanTreeBreakCircle<Elemtype, WeightType>::_DFSFindCircle(int i, int &len)
{
    path[++path_top] = i;
    _graph.SetTag(i, VISITED);
    int tmp = path_top;
    int *ans = NULL;
    for (int u = _graph.FirstAdjVex(i); u >= 0; u = _graph.NextAdjVex(i, u))
    {
        path_top = tmp;
        if (_graph.GetWeight(i, u) != _graph.GetInfinity())
        {
            if (_graph.GetTag(u) == UNVISITED)
            {
                ans = _DFSFindCircle(u, len);
                if (ans != NULL)
                    return ans;
            }
            else
            {
                int start = _find(u);
                if (start != -1)
                {
                    ans = new int[path_top - start];
                    for (int j = start; j <= path_top; j++)
                        ans[j - start] = path[j];
                    len = path_top - start + 1;
                    // for (int i = 0; i <= path_top; i++)
                    //     printf("%d ", ans[i]);
                    // printf("\n");
                    return ans;
                }
            }
        }
    }
    if (circle_exist == false)
    {
        len = 0;
        return NULL;
    }
    return NULL;
}

template <typename Elemtype, typename WeightType>
int MiniSpanTreeBreakCircle<Elemtype, WeightType>::_find(int Vex)
{
    int index = -1;
    for (int i = 0; i <= path_top; i++)
    {
        if (path[i] == Vex && path_top - i > 1)
        {
            circle_exist = true;
            index = i;
        }
    }
    return index;
}

template <typename ElemType, typename WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> MiniSpanTreeBreakCircle<ElemType, WeightType>::GetMST()
{
    _Init();
    int len;
    int *circle = GetCircle(len);
    int MaxArcVex1 = 0, MaxArcVex2 = 1;
    while (circle)
    {
        // for (int i = 0; i < len; i++)
        // {
        //     cout << circle[i] << " ";
        // }
        // cout << endl;
        for (int i = 0; i < len; i++)
        {
            int ArcVex1 = i % len, ArcVex2 = (i + 1) % len;
            if (_graph.GetWeight(circle[ArcVex1], circle[ArcVex2]) > _graph.GetWeight(circle[MaxArcVex1], circle[MaxArcVex2]))
            {
                MaxArcVex1 = ArcVex1;
                MaxArcVex2 = ArcVex2;
            }
        }
        _graph.DeleteArc(circle[MaxArcVex1], circle[MaxArcVex2]);
        // _graph.Display();
        MaxArcVex1 = 0, MaxArcVex2 = 1;
        delete[] circle;
        _Init();
        circle = GetCircle(len);
    }
    AdjMatrixUndirNetwork<ElemType, WeightType> ans = _graph;
    return ans;
}

template <typename ElemType, typename WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> MiniSpanTreeBC(AdjMatrixUndirNetwork<ElemType, WeightType> &graph)
{
    MiniSpanTreeBreakCircle<char, int> temp(graph);
    return temp.GetMST();
}

#endif