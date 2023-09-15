#ifndef __MY__STACK__ARITHMETIC_H
#define __MY__STACK__ARITHMETIC_H

#include "Assistance.h" // 辅助软件包
#include "LinkList.h"   // 链表类
#include "PolyItem.h"   // 多项式项类

// 多项式类
class StackArithmetic
{
protected:
    // 多项式实现的数据成员:
    LinkList<PolyItem> stack; // 多项式组成的线性表

public:
    //  抽象数据类型方法声明及重载编译系统默认方法声明:
    StackArithmetic(){};                                       // 无参构造函数
    ~StackArithmetic(){};                                      // 析构函数
    int Length() const;                                        // 求多项式的项数
    bool IsZero() const;                                       // 判断多项式是否为0
    void SetZero();                                            // 将多项式置为0
    void Display();                                            // 显示多项式
    void InsItem(const PolyItem &item);                        // 插入一项
    StackArithmetic operator+(const StackArithmetic &p) const; // 加法运算符重载
    StackArithmetic(const StackArithmetic &copy);              // 复制构造函数
    StackArithmetic(const LinkList<PolyItem> &copyLinkList);
    // 由多项式组成的线性表构造多项式
    StackArithmetic &operator=(const StackArithmetic &copy);            // 赋值语句重载
    StackArithmetic &operator=(const LinkList<PolyItem> &copyLinkList); // 赋值语句重载
};

#endif