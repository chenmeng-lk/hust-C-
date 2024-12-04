#include"ex1.h"
void initQueue(Queue* const p, int m)////��ʼ��pָ���У��������m��Ԫ��
{
	*(int**)&p->elems = (int*)malloc(sizeof(int)*m);//p==this
	*(int*)&p->max = p->elems?m:0;
	p->head = p->tail = 0;
}
void initQueue(Queue* const p, const Queue& s) //��s�����ʼ��pָ����
{
	*(int**)&p->elems = new int[s.max];
	*(int*)&p->max = p->elems?s.max:0;
	p->head = s.head;
	p->tail = s.tail;
	for (int i = 0; i < s.max; i++)
	{
		*(int*)&p->elems[i] = s.elems[i];
	}
}
void initQueue(Queue* const p, Queue&& s)//��s�ƶ���ʼ��pָ����
{
	*(int**)&p->elems = s.elems;
	*(int*)&p->max = s.max;
	p->head = s.head;
	p->tail = s.tail;
	*(int**)&s.elems = 0;
	*(int*)&s.max = 0;
	s.head = 0;
	s.tail = 0;
}
int  number(const Queue* const p)	//����pָ���е�ʵ��Ԫ�ظ���
{
	if (p->max == 0) return 0;
	return (p->tail - p->head + p->max) % p->max;
}
int  size(const Queue* const p)//����pָ������������Ԫ�ظ���max
{
	return p->max;
}
Queue* const enter(Queue* const p, int e) //��e�����β����������p
{
	if ((p->tail + 1) % p->max == p->head) {
		throw "Queue is full!";//��������
		return p;
	}
	*(int*)&p->elems[p->tail] = e;
	p->tail++;
	p->tail %= p->max;
	return p;
}
Queue* const leave(Queue* const p, int& e)//�Ӷ��׳�Ԫ�ص�e��������p
{
	if (p->head == p->tail || p->max == 0 ) {
		throw "Queue is empty!";//Ϊ��
		return p;
	}
	e = p->elems[p->head];
	p->head = (p->head+1) % p->max;
	return p;
}
Queue* const assign(Queue* const p, const Queue& q) //�����q�����в�����p
{
	if (p == &q) return p;
	if (p->elems != NULL) free(p->elems);
	*(int**)&p->elems = new int[q.max];
	for (int i = 0; i<q.max; i++)
	{
		*(int*)&p->elems[i] = q.elems[i];
	}
	*(int*)&p->max = q.max;
	p->head = q.head;
	p->tail = q.tail;
	return p;
}
Queue* const assign(Queue* const p, Queue&& q) //�ƶ���q�����в�����p
{
	if (p == &q) return p;
	if (p->elems!=NULL) free(p->elems);
	*(int**)&p->elems = q.elems;
	*(int*)&p->max = q.max;
	p->head = q.head;
	p->tail = q.tail;
	*(int**)&q.elems = nullptr;
	*(int*)&q.max = 0;
	q.head = 0;
	q.tail = 0;
	return p;
}
char* print(const Queue* const p, char* s)//��ӡpָ������s������s
{
	int index = 0;
	for(int i = p->head; i != p->tail; i = (i + 1) % p->max) {
		index += sprintf(s + index, "%d,", p->elems[i]);
	}
	if (index > 0) {
		s[index - 1] = '\0'; // �Ƴ����һ������
	}
	return s;
}
void destroyQueue(Queue* const p)	 //����pָ��Ķ���
{
	if (p->elems) {
		delete[] p->elems;
		*(int**)&p->elems = NULL;
		*(int*)&p->max = 0;
		p->head = 0;
		p->tail = 0;
	}
}
