#include <iostream>
using namespace std;

typedef struct BinTreeNode
{
    char data;
    struct BinTreeNode *lc, *rc;
} BTN;

void CreateTree(BTN *&T) // 先序建树
{
    char ch;
    cin >> ch;
    if (ch == '#')
        T = NULL; // 空树
    else
    {
        T = new BTN; // ch！='#',建节点
        T->data = ch;
        CreateTree(T->lc); // 左子树
        CreateTree(T->rc); // 右子树
    }
}

int count(BTN *T)
{
    if (T == NULL)
        return 0; // 节点为空不计入
    if (T->lc == NULL && T->rc == NULL)
        return 1; // 当且仅当左右孩子为空，节点date不为空时，ans++;
    else
        return count(T->lc) + count(T->rc); // 递归寻找左右子树
}

int main()
{
    BTN *T;
    CreateTree(T);
    cout << count(T) << endl;
    delete T;
    return 0;
}
