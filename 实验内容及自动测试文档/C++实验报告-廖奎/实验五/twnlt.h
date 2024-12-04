#pragma once
#include <QtWidgets/QMainWindow>
#include <QGraphicsRectItem>
#include "ui_twnlt.h"
class QtWidgetsFL;
class QtWidgetsLS;
class twnlt : public QMainWindow
{
	Q_OBJECT
public:
	twnlt(QWidget* parent = Q_NULLPTR);
	~twnlt();
private:
	Ui::twnltClass ui;
	QtWidgetsFL* fl;
	QtWidgetsLS* ls;
	QTimer* m_Timer;
	QGraphicsItemGroup* gItem;
	void deleteItems();
protected:
	void closeEvent(QCloseEvent* event);
private slots:
	void loadmap();
	void closewnd();
	void zszc();
	void zdjl();
	void zdcx();
};
class MyScene : public QGraphicsScene
{
public:
	explicit MyScene(QObject* parent = 0);
	void stopLines(QGraphicsView*);
	void clickmouse(int, int, int);
protected:
	QGraphicsView* qgv;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
public slots:
};
class MyItem : public QGraphicsRectItem {
	int cx, cy;//����ʱ������
	int cf;//���������1����ʾ�ص㣻�Ҽ�������2����ʾ�յ�
	int cs;//�����õ���������
	int bs[6];//�����6��վ��ı��
public:
	MyItem(int x, int y, int f);
	MyItem& operator<<(int s);
	int operator()(int x, int y);
	int& x();
	int& y();
	int& f();
	int& c();
	int& operator[](int);
	int checkAllStops();
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
};