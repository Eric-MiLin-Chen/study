#ifndef _WEEK6_H
#define _WEEK6_H

#include <iostream>

typedef struct lnode
{
    int tag; // 节点类型标识
    union
    {
        char data;             // 原子值
        struct lnode *sublist; // 指向子表的指针
    } val;
    struct lnode *link; // 指向下一个元素
} GLNode;               // 广义表节点类型定义

class GeneralList
{
private:
    GLNode *head = NULL;

public:
    GeneralList(char *&s);
    GeneralList(GLNode *g);
    int GLLength();                               // 求广义表g的长度
    void DispGL(GLNode *g = NULL);                // 输出广义表g
    int GLDepth(GLNode *g = NULL, bool flag = 0); // 求广义表g的深度
    int atomnum(GLNode *g = NULL, bool flag = 0);
    GLNode *gethead();
};

#endif