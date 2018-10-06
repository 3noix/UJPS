#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <iostream>
#include "ProfileEngine.h"
#include "MessagesDirector.h"

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
	
	QCoreApplication app{argc,argv};
	QStringList args = app.arguments();
	args.removeFirst();
	
	// default arguments values
	bool bWhiteList = false;
	
	// white-list option
	if (args.contains("-whitelist"))
	{
		bWhiteList = true;
		args.removeAll("-whitelist");
	}
	
	if (argc == 2 || argc == 3) // to run profile from command line
	{
		// first argument: the profile dll
		QString profileDllFilePath = QFileInfo{args[0]}.absoluteFilePath();
		if (!QFile::exists(profileDllFilePath))
		{
			std::cerr << "Error: file does not exist" << std::endl;
			return 1;
		}
		
		// second optional argument, the time step (in milliseconds)
		int dtms = 15;
		if (argc == 3)
		{
			bool bok;
			dtms = args[1].toInt(&bok);
			if (!bok)
			{
				std::cerr << "Error: invalid time step value" << std::endl;
				return 1;
			}
		}
		
		ProfileEngine engine{bWhiteList};
		MessagesDirector messenger;
		messenger.startsListeningTo(&engine);
		if (!engine.loadProfile(profileDllFilePath)) {return 1;}
		if (!engine.run(dtms)) {return 1;} // only 15 ms time step for now
		return app.exec();
	}
	else
	{
		std::cerr << "Error: incorrect number of arguments provided" << std::endl;
		return 1;
	}
}

