#ifndef _TREE_H
#define _TREE_H
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
struct BinaryTreeNode
{
    T val;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
};

template <typename T>
class BinaryTree
{
public:
    BinaryTree() { root = NULL; }
    virtual ~BinaryTree() { clear(root); }
    void Build() { root = BuildTree(); }  // 建树
    void PreOrder() { PreOrder(root); }   // 前序
    void UnrecursionPreOrder();           // 非递归前序
    void InOrder() { InOrder(root); }     // 中序
    void PostOrder() { PostOrder(root); } // 后序
    void LevelOrder() { LevelOrder(root); }
    void clear()
    {
        clear(root);
        root = NULL;
    } // 清空
    int GetDepth() { return GetDepth(root); }
    int GetDegree() { return GetDegree(root); }
    // 临时函数
    BinaryTreeNode<T> *GetRoot()
    {
        return root;
    }

protected:
    BinaryTreeNode<T> *BuildTree();
    void clear(BinaryTreeNode<T> *&r1);
    void PreOrder(BinaryTreeNode<T> *r);
    void InOrder(BinaryTreeNode<T> *r);
    void PostOrder(BinaryTreeNode<T> *r);
    void LevelOrder(BinaryTreeNode<T> *r);
    int GetDepth(BinaryTreeNode<T> *node);
    int GetDegree(BinaryTreeNode<T> *node);
    BinaryTreeNode<T> *root;
};
template <class T>
void BinaryTree<T>::clear(BinaryTreeNode<T> *&r1)
{
    if (!r1)
        return;
    clear(r1->left);
    clear(r1->right);
    delete r1;
}

template <class T>
BinaryTreeNode<T> *BinaryTree<T>::BuildTree()
{
    BinaryTreeNode<T> *k;
    char c;
    cin >> c;
    if (c == '#')
        return NULL;
    k = new BinaryTreeNode<T>;
    k->val = c;
    k->left = BuildTree();
    k->right = BuildTree();
    return k;
}
template <class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T> *r)
{
    if (!r)
        return;
    cout << r->val << " ";
    PreOrder(r->left);
    PreOrder(r->right);
}
template <class T>
void BinaryTree<T>::UnrecursionPreOrder()
{
    if (root == NULL)
        return;
    stack<BinaryTreeNode<T> *> s;
    BinaryTreeNode<T> *t = root;
    while (t || !s.empty())
    {
        while (t)
        {
            cout << t->val << " ";
            s.push(t);
            t = t->left;
        }
        if (!s.empty())
        {
            t = s.top();
            s.pop();
            t = t->right;
        }
    }
}
template <class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T> *r)
{
    if (!r)
        return;
    InOrder(r->left);
    cout << r->val << " ";
    InOrder(r->right);
}
template <class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T> *r)
{
    if (!r)
        return;
    PostOrder(r->left);
    PostOrder(r->right);
    cout << r->val << " ";
}

template <typename T>
int BinaryTree<T>::GetDepth(BinaryTreeNode<T> *node)
{
    // 1.确定递归函数的返回值和参数：参数-传入节点 返回值-int
    // 2.终止条件：如果为空节点，返回0，表示高度为0
    if (node == NULL)
        return 0;
    // 3.确定单层递归的逻辑
    int leftdepth = GetDepth(node->left);   // 递归求左子树高度
    int rightdepth = GetDepth(node->right); // 递归求右子树高度
    // int depth = 1 + max(leftdepth, rightdepth);//树的高度是根到叶子最长路径上的结点的数量
    int depth = 1 + (leftdepth > rightdepth ? leftdepth : rightdepth); // 这样写和上一行一样
    // 所以，每次要找最高的那个子树，所以要使用max函数
    // 调用两个递归函数直接可以算出来两个子树的高度，取最高的子树就作为子树高度，再加上根节点高度就行
    return depth; // 在这个题目中，我们认为的高度是从根节点到叶子节点最长路径上结点的数量
    // 所以，如果这个二叉树只有一个节点，那么这个树的高度就是1
}

template <typename T>
int BinaryTree<T>::GetDegree(BinaryTreeNode<T> *node)
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

template <class T>
void BinaryTree<T>::LevelOrder(BinaryTreeNode<T> *r)
{
    if (root == NULL)
        return;
    queue<BinaryTreeNode<T> *> s;
    BinaryTreeNode<T> *t = root;
    s.push(t);
    while (!s.empty())
    {
        t = s.front();
        s.pop();
        cout << t->val << " ";
        if (t->left)
            s.push(t->left);
        if (t->right)
            s.push(t->right);
    }
}

#endif