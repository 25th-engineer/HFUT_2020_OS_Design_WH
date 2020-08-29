#include <QApplication>
#include "MemInitWindow.h"

int main(int argc,char ** argv)
{
	QApplication _a(argc,argv);
	MemInitWindow * p = new MemInitWindow();
	p->Enter();
	return _a.exec();
}

