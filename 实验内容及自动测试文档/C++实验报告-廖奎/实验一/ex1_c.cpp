#include"ex1.h"
void initQueue(Queue* const p, int m)////初始化p指队列：最多申请m个元素
{
	*(int**)&p->elems = (int*)malloc(sizeof(int)*m);//p==this
	*(int*)&p->max = p->elems?m:0;
	p->head = p->tail = 0;
}
void initQueue(Queue* const p, const Queue& s) //用s深拷贝初始化p指队列
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
void initQueue(Queue* const p, Queue&& s)//用s移动初始化p指队列
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
int  number(const Queue* const p)	//返回p指队列的实际元素个数
{
	if (p->max == 0) return 0;
	return (p->tail - p->head + p->max) % p->max;
}
int  size(const Queue* const p)//返回p指队列申请的最大元素个数max
{
	return p->max;
}
Queue* const enter(Queue* const p, int e) //将e入队列尾部，并返回p
{
	if ((p->tail + 1) % p->max == p->head) {
		throw "Queue is full!";//队列满了
		return p;
	}
	*(int*)&p->elems[p->tail] = e;
	p->tail++;
	p->tail %= p->max;
	return p;
}
Queue* const leave(Queue* const p, int& e)//从队首出元素到e，并返回p
{
	if (p->head == p->tail || p->max == 0 ) {
		throw "Queue is empty!";//为空
		return p;
	}
	e = p->elems[p->head];
	p->head = (p->head+1) % p->max;
	return p;
}
Queue* const assign(Queue* const p, const Queue& q) //深拷贝赋q给队列并返回p
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
Queue* const assign(Queue* const p, Queue&& q) //移动赋q给队列并返回p
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
char* print(const Queue* const p, char* s)//打印p指队列至s并返回s
{
	int index = 0;
	for(int i = p->head; i != p->tail; i = (i + 1) % p->max) {
		index += sprintf(s + index, "%d,", p->elems[i]);
	}
	if (index > 0) {
		s[index - 1] = '\0'; // 移除最后一个逗号
	}
	return s;
}
void destroyQueue(Queue* const p)	 //销毁p指向的队列
{
	if (p->elems) {
		delete[] p->elems;
		*(int**)&p->elems = NULL;
		*(int*)&p->max = 0;
		p->head = 0;
		p->tail = 0;
	}
}
