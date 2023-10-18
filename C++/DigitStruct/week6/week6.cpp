#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

enum GenListNodeType
{
    ATOM,
    LIST
};

template <typename T>
struct GenListNode
{
    GenListNodeType tag;
    GenListNode<T> *tlink;
    union
    {
        int ref;
        T atom;
        GenListNode<T> *hlink;
    } val;
    GenListNode(GenListNodeType _tag = ATOM, GenListNode<T> *_next = NULL) : tag(_tag), tlink(_next) {}
};

template <typename T>
class GenList
{
protected:
    GenListNode<T> *head;
    void ShowHelp(GenListNode<T> *hd) const;
    int DepthHelp(const GenListNode<T> *hd);
    void ClearHelp(GenListNode<T> *hd);
    void CopyHelp(const GenListNode<T> *src, GenListNode<T> *dst);
    static void CreateHelp(GenListNode<T> *&first);

public:
    GenList();
    GenList(GenListNode<T> *hd);
    ~GenList();
    GenListNode<T> *First() const;
    GenListNode<T> *Next(GenListNode<T> *p) const;
    bool IsEmpty const;
    void Insert(const T &e);
    void Insert(GenList<T> &subList);
    Status Delete(int i);
    int GetDepth();
    int GetLength();
    GenList(const GenList<T> &g);
    GenList<T> &operator=(const GenList<T> &g);
    void Input(void);
    void Show(void);
};

template <typename T>
int GenList<T>::DepthHelp(const GenListNode<T> *hd)
{
    if (hd->tLink == NULL)
        return 1;
    int subMaxDepth = 0;
    for (GenListNode<T> *p = hd->tlink; *p != NULL; p = p->tlink)
    {
        if (p->tag == LIST)
        {
            int curSubDepth = DepthHelp(p->hlink);
            if (subMaxDepth < curDubDepth)
                subMaxDepth = curSubDepth;
        }
    }
    return subMaxDepth + 1;
}

template <typename T>
void GenList<T>::ClearHelp(GenListNode<T> *hd)
{
}

int main()
{

    return 0;
}