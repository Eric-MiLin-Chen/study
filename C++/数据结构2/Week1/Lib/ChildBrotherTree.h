#ifndef _CHILD_BROTHER_TREE_H
#define _CHILD_BROTHER_TREE_H
#include <iostream>
#include "./BinaryTree.h"

using namespace std;

template <typename T>
int GetDegree(BinaryTreeNode<T> &root);

// template <typename T>
// class ChildBrotherTree : public BinaryTree<T>
// {
// public:
//     ChildBrotherTree();
//     ~ChildBrotherTree();
// };

template <typename T>
int GetDegree(BinaryTreeNode<T> tree)
{
    int i, j, max, tmp;
    BinaryTreeNode<T> Q[100]; // 临时存放各结点
    i = j = 0;
    max = -1;
    if (tree)
    {
        max = 0;
        Q[j++] = tree->firstchild;

        while (i < j) // 按层序遍历
        {
            tmp = 0;
            while (Q[i])
            {
                tmp++;
                // 存储有孩子的结点
                if (Q[i]->firstchild)
                    Q[j++] = Q[i]->firstchild;
                Q[i] = Q[i]->nextsibling; // 统计本层结点数
            }
            if (tmp > max)
                max = tmp;
            i++;
        }
    }
    return max;
}

template <typename T>
int GetDegree(BinaryTreeNode<T> *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        BinaryTreeNode<T> *p;
        int max = 0, d = 0;
        for (p = node->left; p != NULL; p = p->right)
        {
            d++;
            int sub = GetDegree(p);
            max = (sub < max) ? max : sub;
        }
        return (d < max) ? max : d;
    }
}

#endif