#include <iostream>
#include "../../Lib/BinaryTree.h"

int main()
{
    BinaryTree<char> r;
    r.Build();
    r.PreOrder();
    cout << endl;
    r.UnrecursionPreOrder();
    cout << endl;
    r.InOrder();
    cout << endl;
    r.PostOrder();
    cout << endl;
    cout << r.GetDegree();
    cout << endl;
    // abc##d##e##
    // abc#d#e##fg#h##i#j#k###
    return 0;
}
