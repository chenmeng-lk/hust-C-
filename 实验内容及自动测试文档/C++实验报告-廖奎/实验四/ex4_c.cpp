#include"ex4.h"
template <class T>
MAT<T>::MAT(const MAT& a) : e(new T[a.r * a.c]), r(e?a.r:0), c(e?a.c:0)//深拷贝构造
{
	for (int i = 0; i < r * c; i++) {
		e[i] = a.e[i];
	}
}
template <class T>
MAT<T>::MAT(MAT&& a)noexcept :e(a.e),r(e?a.r:0), c(e?a.c:0)//移动构造
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
T* const MAT<T>::operator[ ](int r)//取矩阵r行的第一个元素地址，r越界抛异常
{
	if (r >= 0 && r < this->r)
		return &e[r * c];
	else throw"r越界";
}
template <class T>
MAT<T> MAT<T>::operator+(const MAT& a)const	//矩阵加法，不能加抛异常
{
	if (r == a.r && c == a.c) {//行列数相同才可加
		MAT<T> sum(*this);
		for (int i = 0; i < r * c; i++) {
			sum.e[i] = sum.e[i] + a.e[i];
		}
		return sum;
	}
	else throw"行列数不同，不能加";
}
template <class T>
MAT<T> MAT<T>::operator-(const MAT& a)const	//矩阵减法，不能减抛异常
{
	if (r == a.r && c == a.c) {//行列数相同才可减
		MAT<T> minus(*this);
		for (int i = 0; i < r * c; i++) {
			minus.e[i] = minus.e[i] - a.e[i];
		}
		return minus;
	}
	else throw"行列数不同，不能减";
}
template <class T>
MAT<T> MAT<T>::operator*(const MAT& a)const	//矩阵乘法，不能乘抛异常
{
	if (c == a.r) {//第一个矩阵的列数等于第二个矩阵的行数才能乘
		MAT<T> m(this->r, a.c);//m为得到的矩阵，行列为第一个矩阵的行数，第二个矩阵的列数
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
	else throw"矩阵1行数不等于矩阵2列数，不能乘";
}
template <class T>
MAT<T> MAT<T>::operator~()const//矩阵转置
{
	MAT<T> z(c, r);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			z.e[j * z.c + i] = e[i * c + j];//按照原矩阵行优先顺序，把原矩阵每一行转置成z的每一列
		}
	}
	return z;
}
template <class T>
MAT<T>& MAT<T>::operator=(const MAT& a)	//深拷贝赋值运算
{
	if (this == &a) return *this;
	if (e) delete[]e;
	*(T**)(&e) = new T[a.r * a.c];//给e申请内存
	*(int*)&r = e?a.r:0;//e内存申请失败为0
	*(int*)&c = e?a.c:0;
	for (int i = 0; i < r * c; i++) {
		e[i] = a.e[i];
	}
	return *this;
}
template <class T>
MAT<T>& MAT<T>::operator=(MAT&& a)noexcept	//移动赋值运算
{
	if (this == &a) return *this;
	if (e) delete[]e;//删除e原来的指针
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	*(T**)(&e) = a.e;
	*(T**)(&a.e) = nullptr;
	*(int*)(&a.r) = 0;
	*(int*)(&a.c) = 0;
	return *this;
}
template <class T>
MAT<T>& MAT<T>::operator+=(const MAT& a)	//“+=”运算
{
	return *this = (*this + a);
}
template <class T>
MAT<T>& MAT<T>::operator-=(const MAT& a)	//“-=”运算
{
	return *this = (*this - a);
}
template <class T>
MAT<T>& MAT<T>::operator*=(const MAT& a)	//“*=”运算
{
	return *this = (*this * a);
}
//print输出至s并返回s：列用空格隔开，行用回车结束
template <class T>
char* MAT<T>::print(char* s)const noexcept {
	int index = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (typeid(T).name() == typeid(int).name())//实例类MAT<int>
				index += sprintf(s + index, "%6ld ", e[i * c + j]);
			else if (typeid(T).name() == typeid(long long).name())//实例类MAT<long long>
				index += sprintf(s + index, "%8lf ", e[i * c + j]);
		}
		index += sprintf(s + index, "\n ");
	}
	s[index - 1] = '\0';
	//printf("%s\n", s);
	return s;
}
