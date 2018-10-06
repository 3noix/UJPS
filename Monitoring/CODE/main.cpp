#include <stdio.h>
#include <QtDebug>
#include <QApplication>
#include <QElapsedTimer>
#include <QThread>

#include "MainWindow.h"

//#define DEBUG_MODE

#ifdef DEBUG_MODE
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(context)
	
	QByteArray localMsg1 = msg.toLocal8Bit();
	QByteArray localMsg2 = (msg + '\n').toLocal8Bit();
	if (type == QtDebugMsg)
	{
		// on standard output
		fprintf(stderr, "%s\r\n", localMsg1.constData());
		
		// in a file
		QFile debugFile{QCoreApplication::applicationDirPath() + "/debug.txt"};
		debugFile.open(QIODevice::Append);
		debugFile.write(localMsg2.constData());
		//debugFile.close();
	}
}

#endif


int main(int argc, char **argv)
{
	#ifdef DEBUG_MODE
	qInstallMessageHandler(myMessageOutput);
	QFile debugFile{QCoreApplication::applicationDirPath() + "/debug.txt"};
	debugFile.remove();
	#endif
	
	QApplication app{argc,argv};
	MainWindow w;
	w.show();
	return app.exec();
}

