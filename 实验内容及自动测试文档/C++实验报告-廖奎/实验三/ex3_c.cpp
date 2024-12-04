#include"ex3.h"
using namespace std;
STACK::STACK(int m):QUEUE(m),q(QUEUE(m)) { }	//初始化栈：最多存放2m-2个元素
STACK::STACK(const STACK& s): QUEUE(s), q(s.q) { }  	//用栈s深拷贝初始化栈
STACK::STACK(STACK&& s)noexcept:QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) { }  //用栈s移动拷贝初始化栈
int STACK::size()const noexcept		  		//返回栈的容量即2m
{
	return QUEUE::size()*2;
}
STACK::operator int() const noexcept	   		//返回栈的实际元素个数
{
	return QUEUE::operator int() + int(q);
}
STACK& STACK::operator<<(int e) //将e入栈，并返回当前栈
{
	if (QUEUE::operator int() < QUEUE::size()-1) QUEUE::operator<<(e);//基类q1没满
	else if (q.operator int() < q.size()-1) q << e;//q2没满
	else throw"STACK is full!";
	return *this;
}
STACK& STACK::operator>>(int& e)     		//出栈到e，并返回当前栈
{
	if (q.operator int()) {//q2不为空
		int n = q.operator int();
		for (int k = 0; k < n - 1; k++)
		{
			q >> e;
			q << e;
		}
		q >> e;
	}
	else if (QUEUE::operator int()) {//q1不为空
		int n = QUEUE::operator int();
		for (int k = 0; k < n - 1; k++)
		{
			QUEUE::operator >> (e);
			QUEUE::operator << (e);
		}
		QUEUE::operator >> (e);
	}
	else throw"STACK is empty!";
	return *this;
}
STACK& STACK::operator=(const STACK& s)	//深拷贝赋值并返回被赋值栈
{
	if (this != &s) {
		QUEUE::operator=(s);
		q = s.q;
	}
	return *this;
}
STACK& STACK::operator=(STACK&& s)noexcept//移动赋值并返回被赋值栈
{
	if (this != &s) {
		*(QUEUE*)this = (QUEUE&&)s;
		q = (QUEUE &&) s.q;
	}
	return *this;
}
char* STACK::print(char* b)const noexcept	//从栈底到栈顶打印栈元素 
{
	QUEUE::print(b);
	if (q.operator int())
	{
		int len = strlen(b);
		b[len] = ',';
		q.print(b + len + 1);
	}
	return b;
}
STACK::~STACK()noexcept {}        	//销毁栈

