#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__
#include "Assistance.h"	// ���������

// ˳���ģ��������� 
template <class ElemType>
class SeqList 
{
protected:
// ˳�������ݳ�Ա
	int length;					// ˳���ĵ�ǰ���� 
	int maxLength;				// ˳�����������
	ElemType *elems;			// Ԫ�ش洢�ռ���׵�ַ 

public:
// ˳���ĺ�����Ա
	SeqList(int size = DEFAULT_SIZE);	// ����һ���ձ� 
	SeqList(ElemType v[], int n, int size = DEFAULT_SIZE);	// ��������v�����ݹ���˳��� 
	virtual ~SeqList();			// ��������
	int GetLength() const;		// ȡ˳�����			 
	bool IsEmpty() const;		// �ж�˳����Ƿ�Ϊ��
	void Clear();				// ��˳������
	void Traverse(void (*Visit)(const ElemType &)) const;	// ����˳���
	int LocateElem(const ElemType &e) const;	// Ԫ�ض�λ����ָ��Ԫ����˳����е�λ��
	Status GetElem(int i, ElemType &e) const;	// ȡ˳����е�i��Ԫ�ص�ֵ	
	Status SetElem(int i, const ElemType &e);	// �޸�˳����е�i��Ԫ�ص�ֵ
	Status DeleteElem(int i, ElemType &e);      // ɾ��˳����е�i��Ԫ��		
	Status InsertElem(int i, const ElemType &e); // ��˳����i��λ�ò���Ԫ��
 	Status InsertElem(const ElemType &e);        // ��˳����β����Ԫ��
	SeqList(const SeqList<ElemType> &sa);        // ���ƹ��캯��
	SeqList<ElemType> &operator =(const SeqList<ElemType> &sa); // ��ֵ�������
};


// ˳�������Ա��ʵ�ֲ���

template <class ElemType>
SeqList<ElemType>::SeqList(int size)
// �������������һ���������Ϊsize�Ŀ�˳���
{
	elems = new ElemType[size];		    // ����洢�ռ�
	assert(elems);                      // ����洢�ռ�ʧ�ܣ�������ֹ 
	maxLength = size;					// ����˳�����������
	length = 0;							// �����Ա�ĳ���Ϊ0
}

template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size)
// �����������������v�е����ݹ���˳���
{
	elems = new ElemType[size];		    // ����洢�ռ�
	assert(elems);                      // ����洢�ռ�ʧ�ܣ�������ֹ 
	maxLength = size;					// ����˳�����������
	length = n;							// ˳���ĵ�ǰ����Ϊn 
	for (int i = 0; i < length; i++)	// ������v�е�Ԫ�����δ�ŵ�elems������ 
		elems[i] = v[i]; 
}
 
template <class ElemType>
SeqList<ElemType>::~SeqList()
// ���ܣ�����˳���Ĵ洢�ռ� 
{
	delete []elems;						// �ͷŴ洢�ռ�
}

template <class ElemType>
int SeqList<ElemType>::GetLength() const
// ���ܣ�����˳�����Ԫ�ظ���
{
	return length;
}

template <class ElemType>
bool SeqList<ElemType>::IsEmpty() const
// ���ܣ���˳���Ϊ�գ��򷵻�true�����򷵻�false
{
	return length == 0;
}

template <class ElemType>
void SeqList<ElemType>::Clear()
// ���ܣ����˳���
{
	length = 0;
}

template <class ElemType>
void SeqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ���ܣ����ζ�˳����ÿ��Ԫ�ص��ú���(*visit)���з��� 
{
	for (int i = 0; i < length; i++)
		(*visit)(elems[i]);
}

template <class ElemType>
int SeqList<ElemType>::LocateElem(const ElemType &e) const
// ���ܣ���Ԫ��e��˳����е����,���˳����в�����Ԫ��e�򷵻�0
{
	int i = 0;
    while (i < length && elems[i] != e)
         i++;	
    return i < length ? i+1 : 0;
}

template <class ElemType>
Status SeqList<ElemType>::GetElem(int i, ElemType &e) const
// ���ܣ���˳�����ڵ�i��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,����������NOT_PRESENT
{
	if(i < 1 || i > length)
		return NOT_PRESENT;	// ����Ԫ�ز�����
	else	{
		e = elems[i - 1];
		return ENTRY_FOUND;	// Ԫ�ش���
	}
}

template <class ElemType>
Status SeqList<ElemType>::SetElem(int i, const ElemType &e)
// ���ܣ���˳���ĵ�i��λ�õ�Ԫ�ظ�ֵΪe��i��ȡֵ��ΧΪ1��i��length,i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (i < 1 || i > length)
		return RANGE_ERROR;	// ����λ�ô�
	else	{
		elems[i - 1] = e;
		return SUCCESS;		// �����޸ĳɹ�
	}
}

template <class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType &e)
// ���ܣ�ɾ��˳����i��λ�õ�Ԫ��, ��ǰ��e������ֵ��i�ĵ�ȡֵ��ΧΪ1��i��length,i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (i < 1 || i > length)		
		return RANGE_ERROR;      // ����λ�ô�
	else	{
		e = elems[i - 1];	     // ��e���ر�ɾ��Ԫ�ص�ֵ
		for (int j = i; j < length; j++)// ��ɾ��Ԫ��֮���Ԫ����������һ��λ�� 
			elems[j-1] = elems[j]; 
		length--;				// ɾ����˳���Ԫ�ظ�����1
		return SUCCESS;	        // ����ɾ���ɹ�
	}
}

template <class ElemType>
Status SeqList<ElemType>::InsertElem(int i, const ElemType &e)
// ���ܣ���˳���ĵ�i��λ�ò���Ԫ��e,i�ĵ�ȡֵ��ΧΪ1��i��Length()+1�� 
//	��˳�������,�򷵻�OVER_FLOW,
//	��i�Ϸ�, �򷵻�SUCCESS, ����������RANGE_ERROR
{
	if (length == maxLength)
		return OVER_FLOW;	            	// ˳�������,����OVER_FLOW
	else if (i < 1 || i > length + 1)		// i��Χ��,����λ�ô�
		return RANGE_ERROR;
	else	{
		for (int j = length; j >= i; j--)  // ����λ��֮���Ԫ������
			elems[j] = elems[j - 1]; 
		elems[i - 1] = e;	               // ��e��ֵ��˳���iλ��	
   		length++;				           // �����Ԫ�ظ�����1
     	return SUCCESS;			           // ���ز���ɹ�
	}
}

template <class ElemType>
Status SeqList<ElemType>::InsertElem(const ElemType &e)
// ���ܣ���˳���ı�β����Ԫ��e,���򷵻�SUCCESS����˳�������,�򷵻�OVER_FLOW
{
	if (length==maxLength)		// ˳�����������OVER_FLOW
		return OVER_FLOW;	
	else	{
		elems[length] = e;	    // ��Ԫ��e���뵽��β	
   		length++;				// �����˳���Ԫ�ظ�����1
     	return SUCCESS;			// ���ز���ɹ�
	}
}

template <class ElemType>
SeqList<ElemType>::SeqList(const SeqList<ElemType> &sa)
// ���ܣ����ƹ��캯������˳���sa������˳���
{
	int saLength = sa.GetLength();	// ȡ˳���sa�ĳ���
	ElemType e;

	maxLength = sa.maxLength;		// ȡ˳�����������
	elems = new ElemType[maxLength];// ����洢�ռ�
	assert(elems);                  // ����洢�ռ�ʧ�� 
	length = 0;					    // ��˳���Ԫ�ظ���Ϊ0

	for (int i = 1; i <= saLength; i++)	{
		sa.getElem(i, e);		    // ȡ��˳���sa�е�i��Ԫ��
		insertElem(e);			    // ��e���뵽��ǰ˳���ı�β 
	}
}

template <class ElemType>
SeqList<ElemType> &SeqList<ElemType>::operator =(const SeqList<ElemType> &sa)
// ���ܣ���ֵ������أ���˳���sa��ֵ����ǰ˳���
{
	if (&sa != this)	{
		int saLength = sa.GetLength();	// ȡ˳���sa�ĳ���
		ElemType e;

        maxLength = sa.maxLength;		// ȡ˳�����������
        delete []elems;                 // �ͷ�˳���ԭ���Ĵ洢�ռ�
        elems = new ElemType[maxLength];// ����洢�ռ�
	    assert(elems);                  // ����洢�ռ�ʧ�� 
        length = 0;						// ��˳���Ԫ�ظ���Ϊ0
        for (int i = 1; i <= saLength; i++)	{
			sa.getElem(i, e);	        // ȡ��˳���sa�е�i��Ԫ��
			insert(e);		            // ��e���뵽��ǰ˳���ı�β
		}
	}
	return *this;
}

#endif
