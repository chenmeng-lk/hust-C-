#include"ex3.h"
using namespace std;
STACK::STACK(int m):QUEUE(m),q(QUEUE(m)) { }	//��ʼ��ջ�������2m-2��Ԫ��
STACK::STACK(const STACK& s): QUEUE(s), q(s.q) { }  	//��ջs�����ʼ��ջ
STACK::STACK(STACK&& s)noexcept:QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) { }  //��ջs�ƶ�������ʼ��ջ
int STACK::size()const noexcept		  		//����ջ��������2m
{
	return QUEUE::size()*2;
}
STACK::operator int() const noexcept	   		//����ջ��ʵ��Ԫ�ظ���
{
	return QUEUE::operator int() + int(q);
}
STACK& STACK::operator<<(int e) //��e��ջ�������ص�ǰջ
{
	if (QUEUE::operator int() < QUEUE::size()-1) QUEUE::operator<<(e);//����q1û��
	else if (q.operator int() < q.size()-1) q << e;//q2û��
	else throw"STACK is full!";
	return *this;
}
STACK& STACK::operator>>(int& e)     		//��ջ��e�������ص�ǰջ
{
	if (q.operator int()) {//q2��Ϊ��
		int n = q.operator int();
		for (int k = 0; k < n - 1; k++)
		{
			q >> e;
			q << e;
		}
		q >> e;
	}
	else if (QUEUE::operator int()) {//q1��Ϊ��
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
STACK& STACK::operator=(const STACK& s)	//�����ֵ�����ر���ֵջ
{
	if (this != &s) {
		QUEUE::operator=(s);
		q = s.q;
	}
	return *this;
}
STACK& STACK::operator=(STACK&& s)noexcept//�ƶ���ֵ�����ر���ֵջ
{
	if (this != &s) {
		*(QUEUE*)this = (QUEUE&&)s;
		q = (QUEUE &&) s.q;
	}
	return *this;
}
char* STACK::print(char* b)const noexcept	//��ջ�׵�ջ����ӡջԪ�� 
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
STACK::~STACK()noexcept {}        	//����ջ

