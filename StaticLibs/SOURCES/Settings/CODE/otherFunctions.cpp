#include "otherFunctions.h"
#include <QCoreApplication>
#include <QStringList>


// DEBUG OR RELEASE ///////////////////////////////////////////////////////////
QString debugOrRelease()
{
	QStringList list = QCoreApplication::applicationDirPath().split('/',QString::SkipEmptyParts);
	if (list.size() == 0) {return "release";}
	
	QString s = list.last();
	if (s == "debug") {return "debug";}
	return s;
}

// SHORT NAME /////////////////////////////////////////////////////////////////
QString shortName(QString path)
{
	path = path.replace('\\','/');
	QStringList list = path.split('/',QString::SkipEmptyParts);
	if (list.size() == 0) {return {};}
	return list.last();
}

// DIR NAME ///////////////////////////////////////////////////////////////////
QString dirName(QString path)
{
	path = path.replace('\\','/');
	QStringList list = path.split('/',QString::SkipEmptyParts);
	if (list.size() == 0) {return {};}
	list.removeLast();
	return list.join("/");
}

