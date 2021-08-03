#include <QtDebug>
#include <stdio.h>
void cleanDirectory(QString dirPath);
void cleanProject(QString dirPath);
bool deleteDirectory(QString dirPath);

#include <QDir>
#include <QFile>
#include <QCoreApplication>

//#define NO_ARG_MODE


int main(int argc, char **argv)
{
	QCoreApplication app{argc,argv};
	QStringList args = app.arguments();
	
	if (args.size() == 2)
	{
		QString dirPathToClean = args[1];
		qDebug() << "cleaning " << dirPathToClean;
		cleanDirectory(dirPathToClean);
	}
	else
	{
		#ifdef NO_ARG_MODE
		QString dirPathToClean = QCoreApplication::applicationDirPath();
		qDebug() << "cleaning " << dirPathToClean;
		cleanDirectory(dirPathToClean);
		#else
		qDebug() << "wrong number of arguments ";
		#endif
	}
	
	qDebug() << "done ";
	//getchar();
	return 0;
}

void cleanDirectory(QString dirPath)
{
	QDir dir{dirPath};
	QStringList proFiles = dir.entryList({"*.pro"},QDir::Files);
	
	if (proFiles.size() > 0)
	{
		// if there is at least one .pro file in the directory
		cleanProject(dirPath);
	}
	else
	{
		// otherwise we do the same for the sub-directories
		QStringList directories = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		for (const QString &dirName : directories)
		{
			QString childDirPath = dirPath + "/" + dirName;
			qDebug() << "cleaning" << childDirPath;
			cleanDirectory(childDirPath);
		}
	}
}

void cleanProject(QString modelPath)
{
	// suppression des répertoires debug et release
	qDebug() << "    delete debug";
	deleteDirectory(modelPath + "/debug");
	qDebug() << "    delete release";
	deleteDirectory(modelPath + "/release");
	
	// suppression des makefiles
	QDir dir{modelPath};
	QStringList makefiles = dir.entryList({"Makefile*"},QDir::Files);
	qDebug() << "    delete makefiles";
	for (const QString &makefileName : makefiles)
	{
		QFile makefile{modelPath + "/" + makefileName};
		makefile.remove();
	}
	
	// suppression des fichiers qobjects
	QStringList qObjectsFiles = dir.entryList({"object_*"},QDir::Files);
	qDebug() << "    delete qobjects files";
	for (const QString &qObjectsFileName : qObjectsFiles)
	{
		QFile qObjectsFile{modelPath + "/" + qObjectsFileName};
		qObjectsFile.remove();
	}
	
	// suppression du .qmake.stash
	QFile stashFile{modelPath + "/.qmake.stash"};
	stashFile.remove();
}

bool deleteDirectory(QString dirPath)
{
	QDir dirToDelete{dirPath};
	if (!dirToDelete.exists()) {return false;}
	
	QString shortDirName = dirToDelete.dirName();
	QFileInfoList infoList = dirToDelete.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
	
	for (const QFileInfo &info : infoList)
	{
		if (info.isFile())
		{
			QFile file{info.absoluteFilePath()};
			if (!file.remove()) {return false;}
		}
		else if (info.isDir())
		{
			if (!deleteDirectory(info.absoluteFilePath()))
			{return false;}
		}
	}
	
	if (!dirToDelete.cdUp()) {return false;}
	if (!dirToDelete.rmdir(shortDirName)) {return false;}
	
	return true;
}

