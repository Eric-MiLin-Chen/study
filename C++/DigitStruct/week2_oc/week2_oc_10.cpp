#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *MakeList(int x)
{
    ListNode *head = NULL, *cur = head;
    for (int i = 0; i < x; i++)
    {
        if (!head)
        {
            head = new ListNode;
            cur = head;
        }
        else
        {
            cur->next = new ListNode;
            cur = cur->next;
        }
    }
    return head;
}

istream &operator>>(istream &in, ListNode *list)
{
    ListNode *cur = list;
    while (cur)
    {
        in >> cur->val;
        cur = cur->next;
    }
    return in;
}

ostream &operator<<(ostream &out, ListNode *list)
{
    ListNode *cur = list;
    while (cur)
    {
        out << cur->val << " ";
        cur = cur->next;
    }
    return out;
}

ListNode *reverse(ListNode *list)
{
    ListNode *pre = NULL, *cur = list, *next = NULL;
    while (cur)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;
    if (list1->val <= list2->val)
    {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
    else
    {
        list1->next = mergeTwoLists(list2, list1->next);
        return list1;
    }
}

int main()
{
    ListNode *head1 = MakeList(10), *head2 = MakeList(5);
    cout << "输入list1:";
    cin >> head1;
    cout << "输入list2:";
    cin >> head2;
    cout << "list1:" << head1 << endl;
    cout << "list2:" << head2 << endl;
    head1 = reverse(head1);
    head2 = reverse(head2);
    ListNode *mergedlist = mergeTwoLists(head1, head2);
    cout << "mergedlist:" << mergedlist << endl;
    return 0;
}