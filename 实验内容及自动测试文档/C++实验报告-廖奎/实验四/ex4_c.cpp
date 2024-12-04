#include"ex4.h"
template <class T>
MAT<T>::MAT(const MAT& a) : e(new T[a.r * a.c]), r(e?a.r:0), c(e?a.c:0)//�������
{
	for (int i = 0; i < r * c; i++) {
		e[i] = a.e[i];
	}
}
template <class T>
MAT<T>::MAT(MAT&& a)noexcept :e(a.e),r(e?a.r:0), c(e?a.c:0)//�ƶ�����
{
	*(T**)(&a.e) = nullptr;
	*(int*)(&a.r) = 0;
	*(int*)(&a.c) = 0;
}
template <class T>
MAT<T>::~MAT()noexcept {
	if (e) {
		delete[]e;
		*(int*)(&r) = 0;
		*(int*)(&c) = 0;
	}
}
template <class T>
T* const MAT<T>::operator[ ](int r)//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
{
	if (r >= 0 && r < this->r)
		return &e[r * c];
	else throw"rԽ��";
}
template <class T>
MAT<T> MAT<T>::operator+(const MAT& a)const	//����ӷ������ܼ����쳣
{
	if (r == a.r && c == a.c) {//��������ͬ�ſɼ�
		MAT<T> sum(*this);
		for (int i = 0; i < r * c; i++) {
			sum.e[i] = sum.e[i] + a.e[i];
		}
		return sum;
	}
	else throw"��������ͬ�����ܼ�";
}
template <class T>
MAT<T> MAT<T>::operator-(const MAT& a)const	//������������ܼ����쳣
{
	if (r == a.r && c == a.c) {//��������ͬ�ſɼ�
		MAT<T> minus(*this);
		for (int i = 0; i < r * c; i++) {
			minus.e[i] = minus.e[i] - a.e[i];
		}
		return minus;
	}
	else throw"��������ͬ�����ܼ�";
}
template <class T>
MAT<T> MAT<T>::operator*(const MAT& a)const	//����˷������ܳ����쳣
{
	if (c == a.r) {//��һ��������������ڵڶ���������������ܳ�
		MAT<T> m(this->r, a.c);//mΪ�õ��ľ�������Ϊ��һ��������������ڶ������������
		T sum;
		for (int i = 0; i < m.r; i++) {
			for (int j = 0; j < m.c; j++) {
				sum = 0;
				for (int k = 0; k < c; k++) {
					sum += e[i * c + k] * a.e[k * a.r + j];
				}
				m.e[i * m.c + j] = sum;
			}
		}
		return m;
	}
	else throw"����1���������ھ���2���������ܳ�";
}
template <class T>
MAT<T> MAT<T>::operator~()const//����ת��
{
	MAT<T> z(c, r);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			z.e[j * z.c + i] = e[i * c + j];//����ԭ����������˳�򣬰�ԭ����ÿһ��ת�ó�z��ÿһ��
		}
	}
	return z;
}
template <class T>
MAT<T>& MAT<T>::operator=(const MAT& a)	//�����ֵ����
{
	if (this == &a) return *this;
	if (e) delete[]e;
	*(T**)(&e) = new T[a.r * a.c];//��e�����ڴ�
	*(int*)&r = e?a.r:0;//e�ڴ�����ʧ��Ϊ0
	*(int*)&c = e?a.c:0;
	for (int i = 0; i < r * c; i++) {
		e[i] = a.e[i];
	}
	return *this;
}
template <class T>
MAT<T>& MAT<T>::operator=(MAT&& a)noexcept	//�ƶ���ֵ����
{
	if (this == &a) return *this;
	if (e) delete[]e;//ɾ��eԭ����ָ��
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	*(T**)(&e) = a.e;
	*(T**)(&a.e) = nullptr;
	*(int*)(&a.r) = 0;
	*(int*)(&a.c) = 0;
	return *this;
}
template <class T>
MAT<T>& MAT<T>::operator+=(const MAT& a)	//��+=������
{
	return *this = (*this + a);
}
template <class T>
MAT<T>& MAT<T>::operator-=(const MAT& a)	//��-=������
{
	return *this = (*this - a);
}
template <class T>
MAT<T>& MAT<T>::operator*=(const MAT& a)	//��*=������
{
	return *this = (*this * a);
}
//print�����s������s�����ÿո���������ûس�����
template <class T>
char* MAT<T>::print(char* s)const noexcept {
	int index = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (typeid(T).name() == typeid(int).name())//ʵ����MAT<int>
				index += sprintf(s + index, "%6ld ", e[i * c + j]);
			else if (typeid(T).name() == typeid(long long).name())//ʵ����MAT<long long>
				index += sprintf(s + index, "%8lf ", e[i * c + j]);
		}
		index += sprintf(s + index, "\n ");
	}
	s[index - 1] = '\0';
	//printf("%s\n", s);
	return s;
}
