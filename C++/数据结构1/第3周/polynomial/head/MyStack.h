#ifndef __MY__STACK_H
#define __MY__STACK_H

#include "Node.h" // 结点类

// 单链表类
template <class ElemType>
class MyStack
{
protected:
	//  单链表的数据成员
	Node<ElemType> *head;							 // 头结点指针
	Node<ElemType> *top;							 // 栈顶节点指针
	int length;										 // 单链表长度
	int maxsize = 10000;							 // 栈的最大大小
	Status GetElem(int position, ElemType &e) const; // 求指定位置的元素

public:
	//  单链表的函数成员
	MyStack(); // 无参数的构造函数
	// MyStack(ElemType v[], int n);					  // 有参数的构造函数
	virtual ~MyStack();									  // 析构函数
	int GetLength() const;								  // 求单链表长度
	bool IsEmpty() const;								  // 判断单链表是否为空
	void Clear();										  // 将单链表清空
	void Traverse(void (*Visit)(const ElemType &)) const; // 遍历单链表
	// int LocateElem(const ElemType &e) const;					 // 元素定位
	// Status SetElem(int position, const ElemType &e);			 // 设置指定位置的元素值
	// Status DeleteElem(int position, ElemType &e);			 // 删除元素
	// Status InsertElem(int position, const ElemType &e);	     // 在制定位置插入元素
	Status push(const ElemType &e);								 // 在表尾插入元素
	MyStack(const MyStack<ElemType> &copy);						 // 复制构造函数
	MyStack<ElemType> &operator=(const MyStack<ElemType> &copy); // 重载赋值运算
	Status top(ElemType &e);									 // 取栈顶元素
	Status pop();												 // 出栈
};

// 单链表类的实现部分

template <class ElemType>
MyStack<ElemType>::MyStack()
// 操作结果：构造一个空链表
{
	head = new Node<ElemType>; // 构造头结点
	assert(head != 0);		   // 构造头结点失败，终止程序运行
	length = 0;				   // 初始化单链表长度为0
}

// template <class ElemType>
// MyStack<ElemType>::MyStack(ElemType v[], int n)
// // 操作结果：根据数组v中的元素构造单链表
// {
// 	Node<ElemType> *p;
// 	p = head = new Node<ElemType>; // 构造头结点
// 	assert(head != 0);			   // 构造头结点失败，终止程序运行
// 	for (int i = 0; i < n; i++)
// 	{
// 		p->next = new Node<ElemType>(v[i], NULL);
// 		assert(p->next != 0); // 构造元素结点失败，终止程序运行
// 		p = p->next;
// 	}
// 	length = n; // 初始化单链表长度为n
// }

template <class ElemType>
MyStack<ElemType>::~MyStack()
// 操作结果：销毁单链表
{
	Clear();	 // 清空单链表
	delete head; // 释放头结点所指空间
}

template <class ElemType>
int MyStack<ElemType>::GetLength() const
// 操作结果：返回单链表的长度
{
	return length;
}

template <class ElemType>
bool MyStack<ElemType>::IsEmpty() const
// 操作结果：如单链表为空，则返回true，否则返回false
{
	return head->next == NULL;
}

template <class ElemType>
void MyStack<ElemType>::Clear()
// 操作结果：清空单链表,删除单链表中所有元素结点
{
	Node<ElemType> *p = head->next;
	while (p != NULL)
	{
		head->next = p->next;
		delete p;
		p = head->next;
	}
	length = 0;
}

template <class ElemType>
void MyStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对单链表的每个元素调用函数(*visit)访问
{
	Node<ElemType> *p = head->next;
	while (p != NULL)
	{
		(*Visit)(p->data); // 对单链表中每个元素调用函数(*visit)访问
		p = p->next;
	}
}

// template <class ElemType>
// int MyStack<ElemType>::LocateElem(const ElemType &e) const
// // 元素定位
// {
// 	Node<ElemType> *p = head->next;
// 	int count = 1;
// 	while (p != NULL && p->data != e)
// 	{
// 		count++;
// 		p = p->next;
// 	}
// 	return (p != NULL) ? count : 0;
// }

template <class ElemType>
Status MyStack<ElemType>::GetElem(int i, ElemType &e) const
// 操作结果：当单链表存在第i个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else
	{
		Node<ElemType> *p = head->next;
		int count;
		for (count = 1; count < i; count++)
			p = p->next; // p指向第i个结点
		e = p->data;	 // 用e返回第i个元素的值
		return ENTRY_FOUND;
	}
}

// template <class ElemType>
// Status MyStack<ElemType>::SetElem(int i, const ElemType &e)
// // 操作结果：将单链表的第i个位置的元素赋值为e,
// //	i的取值范围为1≤i≤length,
// //	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
// {
// 	if (i < 1 || i > length)
// 		return RANGE_ERROR;
// 	else
// 	{
// 		Node<ElemType> *p = head->next;
// 		int count;
// 		for (count = 1; count < i; count++)
// 			p = p->next; // 取出指向第i个结点的指针
// 		p->data = e;	 // 修改第i个元素的值为e
// 		return SUCCESS;
// 	}
// }

// template <class ElemType>
// Status MyStack<ElemType>::DeleteElem(int i, ElemType &e)
// // 操作结果：删除单链表的第i个位置的元素, 并用e返回其值,
// //	i的取值范围为1≤i≤length,
// //	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
// {
// 	if (i < 1 || i > length)
// 		return RANGE_ERROR; // i范围错
// 	else
// 	{
// 		Node<ElemType> *p = head, *q;
// 		int count;
// 		for (count = 1; count < i; count++)
// 			p = p->next;   // p指向第i-1个结点
// 		q = p->next;	   // q指向第i个结点
// 		p->next = q->next; // 删除结点
// 		e = q->data;	   // 用e返回被删结点元素值
// 		length--;		   // 删除成功后元素个数减1
// 		delete q;		   // 释放被删结点
// 		return SUCCESS;
// 	}
// }

// template <class ElemType>
// Status MyStack<ElemType>::InsertElem(int i, const ElemType &e)
// // 操作结果：在单链表的第i个位置前插入元素e
// //	i的取值范围为1≤i≤length+1
// //	i合法时返回SUCCESS, 否则函数返回RANGE_ERROR
// {
// 	if (i < 1 || i > length + 1)
// 		return RANGE_ERROR;
// 	else
// 	{
// 		Node<ElemType> *p = head, *q;
// 		int count;
// 		for (count = 1; count < i; count++)
// 			p = p->next;					// p指向第i-1个结点
// 		q = new Node<ElemType>(e, p->next); // 生成新结点q
// 		assert(q != 0);						// 申请结点失败，终止程序运行
// 		p->next = q;						// 将q插入到链表中
// 		length++;							// 插入成功后，单链表长度加1
// 		return SUCCESS;
// 	}
// }

template <class ElemType>
Status MyStack<ElemType>::push(const ElemType &e)
// 操作结果：在单链表的表尾位置插入元素e
{
	if (length + 1 == maxsize)
	{
		return OVER_FLOW;
	}
	Node<ElemType> *q;
	q = new Node<ElemType>(e, NULL); // 生成新结点q
	assert(q != 0);					 // 申请结点失败，终止程序运行
	top->next = q;					 // p指向表尾结点
	p->next = q;					 // 在单链表的表尾位置插入新结点
	length++;						 // 插入成功后，单链表长度加1
	return SUCCESS;
}

template <class ElemType>
Status MyStack<ElemType>::top(const ElemType &e)
// 操作结果：在单链表的表尾位置插入元素e
{
	if (length + 1 == maxsize)
	{
		return OVER_FLOW;
	}
	Node<ElemType> *p, *q;
	q = new Node<ElemType>(e, NULL); // 生成新结点q
	assert(q != 0);					 // 申请结点失败，终止程序运行
	for (p = head; p->next != NULL; p = p->next)
		;		 // p指向表尾结点
	p->next = q; // 在单链表的表尾位置插入新结点
	length++;	 // 插入成功后，单链表长度加1
	return SUCCESS;
}

template <class ElemType>
MyStack<ElemType>::MyStack(const MyStack<ElemType> &copy)
// 操作结果：复制构造函数，由单链表copy构造新单链表
{
	int copyLength = copy.GetLength(); // 取被复制单链表的长度
	ElemType e;
	head = new Node<ElemType>; // 构造头指针
	assert(head != 0);		   // 构造头指针失败，终止程序运行
	length = 0;				   // 初始化元素个数

	for (int i = 1; i <= copyLength; i++)
	{						// 复制数据元素
		copy.GetElem(i, e); // 取出第i个元素的值放在e中
		push(e);			// 将e插入到当前单链表的表尾
	}
}

template <class ElemType>
MyStack<ElemType> &MyStack<ElemType>::operator=(const MyStack<ElemType> &other)
// 操作结果：重载赋值运算符，将单链表other赋值给当前单链表
{
	if (&other != this)
	{
		int otherLength = other.GetLength(); // 取被赋值单链表的长度
		ElemType e;
		Clear(); // 清空当前单链表
		for (int i = 1; i <= otherLength; i++)
		{
			other.GetElem(i, e); // 取出第i个元素的值放在e中
			push(e);			 // 将e插入到当前单链表的表尾
		}
	}
	return *this;
}

#endif
