#include <iostream>
#include "Digistra.h"
#include "AdjMatrixUndirNetwork.h"
using namespace std;

int main()
{
    int infity = DEFAULT_INFINITY;
    // char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    // int m[6][6] = {
    //     {infity, 34, 46, infity, infity, 19},
    //     {34, infity, infity, infity, 12, infity},
    //     {46, infity, infity, 17, infity, 25},
    //     {infity, infity, 17, infity, 38, 25},
    //     {infity, 12, infity, 38, infity, 26},
    //     {19, infity, 25, 25, 26, infity}};
    // int n = 6;

    /*
    Input:
    6 9 3
    0 1 34
    0 2 46
    0 5 19
    1 4 12
    2 3 17
    2 5 25
    3 4 38
    3 5 25
    4 5 26
    */

    int n, m, k, src, dst;
    cin >> n >> m >> k;
    AdjMatrixUndirNetwork<char, int> net = CreateNet<char, int>(n, m);
    net.Display();
    for (int i = 0; i < k; i++)
    {
        cin >> src >> dst;
        GetShortestPathDij(net, n, src, dst);
    }
    return 0;
}