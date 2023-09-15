#include "../lib/week6.h"
#include <bits/stdc++.h>

GeneralList::GeneralList(char *&s)
{
    GLNode *g;
    char ch = *s++; // 取一个字符
    if (ch != '\0') // 串未结束判断
    {
        g = (GLNode *)malloc(sizeof(GLNode)); // 创建一个新节点
        if (ch == '(')                        // 当前字符为左括号时
        {
            g->tag = 1;                           // 新节点作为表头节点
            g->val.sublist = GeneralList(s).head; // 递归构造子表并链到表头节点
        }
        else if (ch == ')')
            g = NULL;       // 遇到')'字符,g置为空
        else if (ch == '#') // 遇到'#'字符，表示为空表
            g = NULL;
        else // 为原子字符
        {
            g->tag = 0; // 新节点作为原子节点
            g->val.data = ch;
        }
    }
    else // 串结束,g置为空
        g = NULL;
    ch = *s++;     // 取下一个字符
    if (g != NULL) // 串未结束，继续构造兄弟节点
    {
        if (ch == ',')                     // 当前字符为','
            g->link = GeneralList(s).head; // 递归构造兄弟节点
        else                               // 没有兄弟了,将兄弟指针置为NULL
            g->link = NULL;
    }
    head = g; // 返回广义表g
}

GeneralList::GeneralList(GLNode *g) : head(g) {}

int GeneralList::GLLength() // 求广义表g的长度
{
    int n = 0;
    GLNode *g1;
    g1 = head->val.sublist; // g指向广义表的第一个元素
    while (g1 != NULL)
    {
        n++; // 累加元素个数
        g1 = g1->link;
    }
    return n;
}

GLNode *GeneralList::gethead()
{
    return head;
}

int GeneralList::GLDepth(GLNode *g, bool flag) // 求广义表g的深度
{
    GLNode *g1;
    if (!flag)
        g = head;
    int max = 0, dep;
    if (g->tag == 0) // 为原子时返回0
        return 0;
    g1 = g->val.sublist; // g1指向第一个元素
    if (g1 == NULL)      // 为空表时返回1
        return 1;
    while (g1 != NULL) // 遍历表中的每一个元素
    {
        if (g1->tag == 1) // 元素为子表的情况
        {
            dep = GLDepth(g1, 1); // 递归调用求出子表的深度
            if (dep > max)        // max为同一层所求过的子表中深度的最大值
                max = dep;
        }
        g1 = g1->link; // 使g1指向下一个元素
    }
    return (max + 1); // 返回表的深度
}

void GeneralList::DispGL(GLNode *g) // 输出广义表g
{
    if (g == NULL)
        g = head;
    if (g != NULL) // 表不为空判断
    {
        // 先处理g的元素
        if (g->tag == 0)               // g的元素为原子时
            printf("%c", g->val.data); // 输出原子值
        else                           // g的元素为子表时
        {
            printf("(");                // 输出'('
            if (g->val.sublist == NULL) // 为空表时
                printf("#");
            else                        // 为非空子表时
                DispGL(g->val.sublist); // 递归输出子表
            printf(")");                // 输出')'
        }
        if (g->link != NULL)
        {
            printf(",");
            DispGL(g->link); // 递归输出后续表的内容
        }
    }
}

int GeneralList::atomnum(GLNode *g, bool flag) // 求广义表g中的原子个数
{
    if (!flag)
        g = head;
    if (g != NULL)
    {
        if (g->tag == 0)
            return 1 + atomnum(g->link, 1);
        else
            return atomnum(g->val.sublist, 1) + atomnum(g->link, 1);
    }
    else
        return 0;
}