#pragma once
class STOP {								//描述一个公交站点
	int numb;								//所有公交站点编号
	int x, y;								//公交站点坐标
public:
	STOP(int n = 0, int x = 0, int y = 0);
	virtual int& X();
	virtual int& Y();
	virtual int& N();
};
class LINE {								//描述一条公交线路
	const int numb;							//公交线路编号从1开始
	int* const stop;						//公交线路上所有站点编号
	const int nofs;							//公交线路上站点数量
public:
	LINE(int numb = 0, int nofs = 0, int* stop = nullptr);
	LINE(const LINE& r);
	LINE(LINE&& r)noexcept;
	LINE& operator=(const LINE& r);
	LINE& operator=(LINE&& r)noexcept;
	virtual int has(int s)const;			//若包含站点s，则返回线路中的站次序号：-1表示未包含
	virtual int cross(const LINE& b)const;	//若两条公交线路相交，则返回1
	virtual operator int()const;			//取公交线路编号
	virtual int NOFS()const;				//取公交线路的站点数量
	virtual double dist(int d, int a)const;	//线路从站次d到站次a的距离
	virtual int& operator[](int x);			//线路取某个站次的站点编号
	virtual ~LINE()noexcept;
};
class TRAN {								//从线路from经站点编号stop转至线路to
	int from;								//现乘的公交线路号
	int to;									//需要转乘的公交线路号
	int stop;								//由stop.txt定义的站点编号
public:
	TRAN(int from = 0, int to = 0, int stop = 0);
	int operator==(const TRAN& t)const;
	virtual int& F();						//现乘的公交线路号
	virtual int& T();						//需要转乘的公交线路号
	virtual int& S();						//转乘点的站点编号
};
class ROUTE {								//一个转乘路径
	TRAN* const tran;						//转乘路径上的所有转乘站点
	const int noft;							//转乘路径上的转乘次数
public:
	ROUTE(TRAN* tran = nullptr, int noft = 0);
	ROUTE(const TRAN& t);
	ROUTE(const ROUTE& r);
	ROUTE(ROUTE&& r)noexcept;
	virtual operator int()const;			//得到转乘次数
	virtual int operator==(const ROUTE& r)const;
	virtual ROUTE operator* ()const;		//约简：去掉重复的公交转乘方案
	virtual TRAN& operator[](int);			//一条路径上的所有转乘站点
	virtual ROUTE operator+(const ROUTE& r)const;//转乘路径连接
	virtual ROUTE& operator=(const ROUTE& r);
	virtual ROUTE& operator=(ROUTE&& r)noexcept;
	virtual ROUTE& operator+=(const ROUTE& r);
	virtual ~ROUTE()noexcept;
	virtual int print()const;				//打印转乘路径
};
class NODE {								//矩阵元素：记载的转乘次数和线路
	ROUTE* const p;							//矩阵r*c个元素记载的转乘路径方案
	int n;									//矩阵r*c个元素记载的转乘路径方案数
public:
	NODE(ROUTE* p, int n);
	NODE(int n = 0);
	NODE(const NODE& n);
	NODE(NODE&& n)noexcept;
	virtual NODE operator*()const;			//矩阵元素约简：去掉转乘中的环
	virtual NODE operator+(const ROUTE& n)const;//元素增加路径
	virtual NODE operator+(const NODE& n)const;//元素路径增加
	virtual NODE operator*(const NODE& n)const;//元素路径转乘连接
	virtual NODE& operator=(const NODE& n);
	virtual NODE& operator+=(const NODE& n);
	virtual NODE& operator+=(const ROUTE& n);
	virtual NODE& operator*=(const NODE& n);
	virtual NODE& operator=(NODE&& n)noexcept;
	virtual ROUTE& operator [](int x);		//获得第x个转乘路径
	virtual operator int&();				//返回可转乘路径数n
	virtual ~NODE()noexcept;
	virtual void print()const;				//打印可转乘矩阵的元素
};
class TMAP {
	NODE* const p;
	const int r, c;
public:
	TMAP(int r = 0, int c = 0);
	TMAP(const TMAP& a);
	TMAP(TMAP&& a)noexcept;
	virtual ~TMAP();
	virtual int notZero()const;
	virtual int miniTran(int b, int e, int& noft, ROUTE(&r)[100])const;
	virtual int miniDist(int b, int e, double& dist, ROUTE(&r)[100])const;
	static double getDist(int b, int e, ROUTE& r);
	virtual NODE* operator[](int r);
	virtual int& operator()(int r, int c);
	virtual TMAP operator*(const TMAP& a)const;
	virtual TMAP operator+(const TMAP& a)const;
	virtual TMAP& operator=(const TMAP& a);
	virtual TMAP& operator=(TMAP&& a);
	virtual TMAP& operator+=(const TMAP& a);
	virtual TMAP& operator*=(const TMAP& a);
	virtual TMAP& operator()(int r, int c, const ROUTE& a);
	virtual void print()const;
};
struct GIS {
	static STOP* st;
	static LINE* ls;
	static int ns, nl;
	static TMAP raw, tra;
	static int obs;
public:
	GIS();
	GIS(const char* flstop, const char* flines);
	int miniTran(int fx, int fy, int tx, int ty, int& f, int& t, int& n, ROUTE(&r)[100]);
	int miniDist(int fx, int fy, int tx, int ty, int& f, int& t, double& d, ROUTE(&r)[100]);
	~GIS();
};
extern GIS* gis;
