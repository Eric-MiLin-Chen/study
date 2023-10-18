#ifndef __DBL_NODE_H__
#define __DBL_NODE_H__


// ˫����������
template <class ElemType>
struct DblNode 
{
// ���ݳ�Ա:
	ElemType data;				// ������
	DblNode<ElemType> *prior;	// ָ��ǰ������ָ����
	DblNode<ElemType> *next;	// ָ���̽���ָ����

// ���캯��:
	DblNode();						// �����ݵĹ��캯��
	DblNode(ElemType item, 
	DblNode<ElemType> *priorlink = NULL,
	DblNode<ElemType> *nextlink = NULL);// ��֪�������ָ�������ṹ
};


// ˫�����������ʵ�ֲ���

template<class ElemType>
DblNode<ElemType>::DblNode()
// �������������ָ����Ϊ�յĽ��
{
   prior = NULL;
   next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,
			DblNode<ElemType> *priorlink,
			DblNode<ElemType> *nextlink)
// �������������һ��������Ϊitem��priorָ����Ϊpriorlink��nextָ����Ϊnextlink�Ľ��
{
   data = item;
   prior = priorlink;
   next = nextlink;
}

#endif
