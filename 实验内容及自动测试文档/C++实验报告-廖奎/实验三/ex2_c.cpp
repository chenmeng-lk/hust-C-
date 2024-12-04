#include"ex2.h"
using namespace std;
QUEUE::QUEUE(int m) :elems(new int[m]), max(m) //初始化队列：最多申请m个元素
{
    head = tail = 0;
}
QUEUE::QUEUE(const QUEUE& q) :elems(new int[q.max]), max(q.max)//用q深拷贝初始化队列
{
    head = q.head;
    tail = q.tail;
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
}
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max)	//用q移动初始化队列
{
    head = q.head;
    tail = q.tail;
    *(int**)&q.elems = 0;
    *(int**)&q.max = 0;
    q.head = 0;
    q.tail = 0;
}
QUEUE::operator int() const noexcept	//返回队列的实际元素个数
{
    if (max == 0) return 0;
    return (tail - head + max) % max;
}
int QUEUE::size() const noexcept		//返回队列申请的最大元素个数max
{
    return max;
}
QUEUE& QUEUE::operator<<(int e)  	//将e入队列尾部，并返回当前队列
{
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";//队列满了
        return *this;
    }
    else {
        elems[tail] = e;
        tail++;
        tail %= max;
        return *this;
    }
}
QUEUE& QUEUE::operator>>(int& e) 	//从队首出元素到e，并返回当前队列
{
    if (head == tail || max == 0) {
        throw "QUEUE is empty!";//为空
        return *this;
    }
    else {
        e = elems[head];
        head = (head + 1) % max;
        return *this;
    }
}
QUEUE& QUEUE::operator=(const QUEUE& q)//深拷贝赋值并返回被赋值队列
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
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept//移动赋值并返回被赋值队列
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
char* QUEUE::print(char* s) const noexcept //打印队列至s并返回s
{
    int index = 0;
    for (int i = head; i != tail; i = (i + 1) % max) {
        index += sprintf_s(s + index, sizeof(s+index),"%d,", elems[i]);
    }
    if (index > 0) {
        s[index - 1] = '\0'; // 移除最后一个逗号
    }
    return s;
}
QUEUE:: ~QUEUE()	 		//销毁当前队列
{
    if(elems) delete[] elems;
    *(int**)&elems = 0;
    *(int*)&max = 0;
    head = 0;
    tail = 0;
}
