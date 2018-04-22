#include "MyFileDialog.h"
#include "ApplicationSettings.h"
#include "../otherFunctions.h"
#include <QCoreApplication>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  GET EXISTING DIRECTORY
//  GET OPEN FILE NAME
//  GET OPEN FILE NAMES
//  GET SAVE FILE NAME
///////////////////////////////////////////////////////////////////////////////




// GET EXISTING DIRECTORY /////////////////////////////////////////////////////
QString MyFileDialog::getExistingDirectory(QWidget *parent, const QString &caption, const QString &dirProp, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	if (!settings.contains(dirProp)) {return QFileDialog::getExistingDirectory(parent,caption,appDir,options);}
	
	QList<QVariant> vlist = settings.property(dirProp).toList();
	if (vlist.size() != 2) {return QFileDialog::getExistingDirectory(parent,caption,appDir,options);}
	
	QString mode = vlist[0].toString();
	QString path = vlist[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QString str = QFileDialog::getExistingDirectory(parent,caption,path,options);
	if (mode == "Previous")
	{
		vlist[1] = QVariant(str);
		settings.setProperty(dirProp,vlist);
	}
	
	return str;
}

// GET OPEN FILE NAME /////////////////////////////////////////////////////////
QString MyFileDialog::getOpenFileName(QWidget *parent, const QString &caption, const QString &dirProp, const QString &filter, QString *selectedFilter, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	if (!settings.contains(dirProp)) {return QFileDialog::getOpenFileName(parent,caption,appDir,filter,selectedFilter,options);}
	
	QList<QVariant> vlist = settings.property(dirProp).toList();
	if (vlist.size() != 2) {return QFileDialog::getOpenFileName(parent,caption,appDir,filter,selectedFilter,options);}
	
	QString mode = vlist[0].toString();
	QString path = vlist[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QString str = QFileDialog::getOpenFileName(parent,caption,path,filter,selectedFilter,options);
	if (mode == "Previous")
	{
		vlist[1] = QVariant(dirName(str));
		settings.setProperty(dirProp,vlist);
	}
	
	return str;
}

// GET OPEN FILE NAMES ////////////////////////////////////////////////////////
QStringList MyFileDialog::getOpenFileNames(QWidget *parent, const QString &caption, const QString &dirProp, const QString &filter, QString *selectedFilter, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	if (!settings.contains(dirProp)) {return QFileDialog::getOpenFileNames(parent,caption,appDir,filter,selectedFilter,options);}
	
	QList<QVariant> vlist = settings.property(dirProp).toList();
	if (vlist.size() != 2) {return QFileDialog::getOpenFileNames(parent,caption,appDir,filter,selectedFilter,options);}
	
	QString mode = vlist[0].toString();
	QString path = vlist[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QStringList list = QFileDialog::getOpenFileNames(parent,caption,path,filter,selectedFilter,options);
	QStringList list2;
	for (const QString &str : list) {list2 << dirName(str);}
	if (mode == "Previous")
	{
		vlist[1] = QVariant(list2);
		settings.setProperty(dirProp,vlist);
	}
	
	return list;
}

// GET SAVE FILE NAME /////////////////////////////////////////////////////////
QString MyFileDialog::getSaveFileName(QWidget *parent, const QString &caption, const QString &dirProp, const QString &filter, QString *selectedFilter, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	if (!settings.contains(dirProp)) {return QFileDialog::getSaveFileName(parent,caption,appDir,filter,selectedFilter,options);}
	
	QList<QVariant> vlist = settings.property(dirProp).toList();
	if (vlist.size() != 2) {return QFileDialog::getSaveFileName(parent,caption,appDir,filter,selectedFilter,options);}
	
	QString mode = vlist[0].toString();
	QString path = vlist[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QString str = QFileDialog::getSaveFileName(parent,caption,path,filter,selectedFilter,options);
	if (mode == "Previous")
	{
		vlist[1] = QVariant(dirName(str));
		settings.setProperty(dirProp,vlist);
	}
	
	return str;
}




