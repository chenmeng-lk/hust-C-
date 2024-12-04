#include <QFileDialog>
#include <QMessageBox>
#include "QtWidgetsFL.h"
#include "logiclayer.h"
#include "twnlt.h"
//�Զ����վ�㼰��·�������
QtWidgetsFL::QtWidgetsFL(QWidget* parent) :QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonStop, SIGNAL(clicked()), this, SLOT(inputStop()), Qt::UniqueConnection);
	connect(ui.pushButtonLine, SIGNAL(clicked()), this, SLOT(inputLine()), Qt::UniqueConnection);
	connect(ui.pushButtonDone, SIGNAL(clicked()), this, SLOT(checkFile()), Qt::UniqueConnection);
	connect(ui.pushButtonQuit, SIGNAL(clicked()), this, SLOT(close()), Qt::UniqueConnection);
}
void QtWidgetsFL::myShow(QGraphicsView* p) {
	parnt = p;
	show();
}
QtWidgetsFL:: ~QtWidgetsFL() {}

void QtWidgetsFL::inputStop() {
	ui.labelHits->setText("");
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("*.txt"));
	ui.textEditStop->setText(fileName);
}
void QtWidgetsFL::inputLine() {
	ui.labelHits->setText("");
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "lines", tr("*txt"));
	ui.textEditLine->setText(fileName);
}
void QtWidgetsFL::checkFile() {
	QString fs = ui.textEditStop->toPlainText();
	QString fl = ui.textEditLine->toPlainText();
	if (fs.isEmpty() && fl.isEmpty()) {
		ui.labelHits->setStyleSheet("color:rgb(255,0,0)");
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û������վ���ļ�����·�ļ�·����"));
		ui.textEditStop->setFocus();
		return;
	}
	if (fs.isEmpty()) {
		ui.labelHits->setStyleSheet("color:rgb(255,0,0)");
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û������վ���ļ�·����"));
		ui.textEditStop->setFocus();
		return;
	}
	if (fl.isEmpty()) {
		ui.labelHits->setStyleSheet("color:rgb(255,0,0)");
		ui.labelHits->setText(QString::fromLocal8Bit("������ʾ��û��������·�ļ�·����"));
		ui.textEditLine->setFocus();
		return;
	}
	ui.labelHits->setStyleSheet("color:rgb(255,0,0)");
	ui.labelHits->setText(QString::fromLocal8Bit("������ʾ�����ڴ���վ�����·�ļ���"));
	try {
		if (gis == nullptr) delete gis;
		gis = new GIS(fs.toStdString().c_str(), fl.toStdString().c_str());
		((MyScene*)(parnt->scene()))->stopLines(parnt);
	}
	catch (...) {
		gis = nullptr;
		close();
		QString m = QString::fromLocal8Bit("����վ�����·�ļ��������ʼ��ʧ�ܣ�");
		QMessageBox::information(NULL, QString::fromLocal8Bit("������ʾ"), m);
	}
	ui.labelHits->setText(" ");
	close();
}
