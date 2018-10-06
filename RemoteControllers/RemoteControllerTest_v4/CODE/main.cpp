#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app{argc,argv};
	QGuiApplication::setApplicationDisplayName("The client");
	MainWindow w;
	w.show();
	return app.exec();
}

