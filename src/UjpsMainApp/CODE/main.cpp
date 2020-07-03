#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <iostream>
#include "HMI/MainWindow.h"


int main(int argc, char *argv[])
{
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

