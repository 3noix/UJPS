#include <QApplication>
#include "MfdWidget.h"


int main(int argc, char *argv[])
{
	QApplication app{argc,argv};
	
	MfdWidget w{700};
	w.show();
	w.showConnectionWidget();
	return app.exec();
}

