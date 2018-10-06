#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <iostream>
#include "ProfileEngine.h"
#include "HMI/MainWindow.h"

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


int main(int argc, char *argv[])
{
	#ifdef DEBUG_MODE
	qInstallMessageHandler(myMessageOutput);
	QFile debugFile{QCoreApplication::applicationDirPath() + "/debug.txt"};
	debugFile.remove();
	#endif
	
	if (argc > 4)
	{
		std::cerr << "Error: too much arguments provided" << std::endl;
		return 1;
	}
	
	QApplication app{argc,argv};
	QStringList args = app.arguments();
	args.removeFirst();
	
	// default arguments values
	QString proFilePath;
	int dtms = 15;
	bool bPlay = false;
	
	// play option
	if (args.contains("-play"))
	{
		bPlay = true;
		args.removeAll("-play");
	}
	
	// profile dll and time step
	if (args.size() == 1 || args.size() == 2)
	{
		proFilePath = QFileInfo{args[0]}.absoluteFilePath();
		if (!QFile::exists(proFilePath))
		{
			std::cerr << "Error: file does not exist" << std::endl;
			return 1;
		}
		
		if (args.size() == 2)
		{
			bool bok;
			dtms = args[1].toInt(&bok);
			if (!bok)
			{
				std::cerr << "Error: invalid time step value (" << qPrintable(args[1]) << ")" << std::endl;
				return 1;
			}
		}
	}
	
	// create and show window
	MainWindow w{proFilePath,dtms,bPlay};
	w.show();
	return app.exec();
}

