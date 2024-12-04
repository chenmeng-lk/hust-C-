#include"ex2.h"
using namespace std;
QUEUE::QUEUE(int m) :elems(new int[m]), max(m) //��ʼ�����У��������m��Ԫ��
{
    head = tail = 0;
}
QUEUE::QUEUE(const QUEUE& q) :elems(new int[q.max]), max(q.max)//��q�����ʼ������
{
    head = q.head;
    tail = q.tail;
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
}
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max)	//��q�ƶ���ʼ������
{
    head = q.head;
    tail = q.tail;
    *(int**)&q.elems = 0;
    *(int**)&q.max = 0;
    q.head = 0;
    q.tail = 0;
}
QUEUE::operator int() const noexcept	//���ض��е�ʵ��Ԫ�ظ���
{
    if (max == 0) return 0;
    return (tail - head + max) % max;
}
int QUEUE::size() const noexcept		//���ض�����������Ԫ�ظ���max
{
    return max;
}
QUEUE& QUEUE::operator<<(int e)  	//��e�����β���������ص�ǰ����
{
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";//��������
        return *this;
    }
    else {
        elems[tail] = e;
        tail++;
        tail %= max;
        return *this;
    }
}
QUEUE& QUEUE::operator>>(int& e) 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
{
    if (head == tail || max == 0) {
        throw "QUEUE is empty!";//Ϊ��
        return *this;
    }
    else {
        e = elems[head];
        head = (head + 1) % max;
        return *this;
    }
}
QUEUE& QUEUE::operator=(const QUEUE& q)//�����ֵ�����ر���ֵ����
{
    if (this == &q) return *this;
    if (elems != nullptr) delete[]elems;
    *(int**)&elems = new int[q.max];
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
    *(int*)&max = q.max;
    head = q.head;
    tail = q.tail;
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept//�ƶ���ֵ�����ر���ֵ����
{
    if (this == &q) return *this;
    if (this->elems != NULL) delete[]elems;
    *(int**)&elems = q.elems;
    *(int*)&max = q.max;
    head = q.head;
    tail = q.tail;
    *(int**)&q.elems = nullptr;
    *(int*)&q.max = 0;
    q.head = 0;
    q.tail = 0;
}
char* QUEUE::print(char* s) const noexcept //��ӡ������s������s
{
    int index = 0;
    for (int i = head; i != tail; i = (i + 1) % max) {
        index += sprintf_s(s + index, sizeof(s+index),"%d,", elems[i]);
    }
    if (index > 0) {
        s[index - 1] = '\0'; // �Ƴ����һ������
    }
    return s;
}
QUEUE:: ~QUEUE()	 		//���ٵ�ǰ����
{
    if(elems) delete[] elems;
    *(int**)&elems = 0;
    *(int*)&max = 0;
    head = 0;
    tail = 0;
}
