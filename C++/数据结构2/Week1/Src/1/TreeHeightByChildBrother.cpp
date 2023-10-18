#include <iostream>
#include "../../Lib/BinaryTree.h"

int main()
{
    BinaryTree<char> r;
    r.Build();    // 用先根遍历的顺序建树
    r.PreOrder(); // 先根遍历树
    cout << endl;
    r.UnrecursionPreOrder(); // 非递归先根遍历树
    cout << endl;
    r.PostOrder(); // 后根遍历树
    cout << endl;
    cout << r.GetDepth(); // 获取树的深度
    cout << endl;
    // abc##d##e##
    // abc#d#e##fg#h##i#j#k###
    return 0;
}
