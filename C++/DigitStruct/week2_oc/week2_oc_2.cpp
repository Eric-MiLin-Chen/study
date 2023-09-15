#include <iostream>
using namespace std;

class Node
{
private:
    int data;
    Node *next;
    Node *MakeList(int n);
    friend class sql;
};

Node *Node::MakeList(int n)
{
    Node *head = NULL, *cur = head;
    for (int i = 0; i < n; i++)
    {
        if (!head)
        {
            head = new Node;
            cur = head;
        }
        else
        {
            cur->next = new Node;
            cur = cur->next;
        }
    }
    return head;
}

class sql
{
private:
    Node *data = NULL;
    int size = 0;

public:
    sql();
    sql(int n);
    sql(const sql &_sql);
    Node *insert(int _data);
    void remove(int _data);
    void remove(int s, int j);
    Node *merge(const sql &_sql1, const sql &_sql2);
    ~sql();
};

sql::sql()
{
}

sql::sql(int n)
{
    data = data->MakeList(n);
    size = n;
}

sql::sql(const sql &_sql)
{
    head = sql(_sql.size)
}