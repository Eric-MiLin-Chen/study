#include <iostream>
#include "AdjMatrixUndirGraph.h" // 无向图邻接矩阵
#include "MyDFS.h"
using namespace std;

int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    int m[9][9] = {
        {0, 1, 0, 1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0}};
    int n = 9;
    AdjMatrixUndirGraph<char> g(vexs, n);
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (m[u][v] == 1)
                g.InsertArc(u, v);
    g.Display();
    DFS(g, 'D', 'E');
    // DFS(g, 3, 5);
    return 0;
}