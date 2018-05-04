#include <stdio.h>
#include <QtDebug>
#include <QApplication>
#include <QElapsedTimer>
#include <QThread>

#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc,argv);
	QStringList args = app.arguments();
	
	MainWindow w;
	w.show();
	return app.exec();
}
