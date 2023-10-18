#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct _Stack // 创建栈空间
{
    int data;
    struct _Stack *next;
} Stack, *StackPtr;
typedef struct _Point // 创建指向栈顶的指针空间
{
    StackPtr top;
} Point, *PointPtr;
PointPtr Point_Creat() // 创造链栈
{
    PointPtr p = (PointPtr)malloc(sizeof(Point));
    p->top = NULL;
    return p;
}
void Stack_Add(PointPtr p, int num) // 入栈
{
    StackPtr q = (StackPtr)malloc(sizeof(Stack));
    q->data = num;
    ;
    q->next = p->top;
    p->top = q;
}
int Stack_Pop(PointPtr p) // 出栈
{
    StackPtr q = p->top;
    int num = q->data;
    p->top = p->top->next;
    free(q);
    return num;
}
int IsNum(char c) // 判断是否是数字
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Operator(char c, PointPtr Top) // 遇到符号的操作
{
    int left, right;
    right = Stack_Pop(Top); // 左操作数
    left = Stack_Pop(Top);  // 右操作数
    /*匹配相关运算符进行运算*/
    if (c == '+')
    {
        Stack_Add(Top, left + right);
    }
    else if (c == '-')
    {
        Stack_Add(Top, left - right);
    }
    else if (c == '*')
    {
        Stack_Add(Top, left * right);
    }
    else
    {
        Stack_Add(Top, left / right);
    }
}
void Control(char c, PointPtr Top) // 判断符号还是数字
{
    if (IsNum(c)) // 如果是数字就入栈
    {
        Stack_Add(Top, c - '0');
    }
    else // 是符号就符号操作
    {
        Operator(c, Top);
    }
}
int evalRPN(char (*tokens)[10], int tokensSize)
{                                 // 传入后缀表达式
    PointPtr Top = Point_Creat(); // 创建链栈
    for (int i = 0; i < tokensSize; i++)
    {
        int len = strlen(tokens[i]); // 计算长度
        if (len == 1)                // 如果长度是1就判断是符号还是数字
        {
            Control(tokens[i][0], Top);
        }
        else // 长度大于1
        {
            int num = 0, flag = 0;
            for (int j = 0; j < len; j++)
            {
                if (j == 0 && tokens[i][0] == '-') // 如果是负数就标记下
                {
                    flag = 1;
                }
                else // 将字符串转换为数字
                {
                    num = (num * 10 + (tokens[i][j] - '0'));
                }
            }
            if (flag) // 如果是负数就取负值
            {
                num = num * -1;
            }
            Stack_Add(Top, num); // 把数字入栈
        }
    }
    return Top->top->data; // 返回计算的结果(就是链栈最后一个值)
}
int main()
{
    char tokens[20][10] = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    printf("%d", evalRPN(tokens, 13));
    return 0;
}
