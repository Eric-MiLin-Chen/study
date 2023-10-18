#ifndef __NODE_H__
#define __NODE_H__

// �����
template <class ElemType>
struct Node 
{
// ���ݳ�Ա:
	ElemType data;				// ������
	Node<ElemType> *next;		// ָ����

// ���캯��:
	Node();						// �޲����Ĺ��캯��
	Node(ElemType e, Node<ElemType> *link = NULL);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���
template<class ElemType>
Node<ElemType>::Node()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType e, Node<ElemType> *link)
// �������������һ��������Ϊe��ָ����Ϊlink�Ľ��
{
   data = e;
   next = link;
}

#endif
