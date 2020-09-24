#include "MyFileDialog.h"
#include "ApplicationSettings.h"
#include "otherFunctions.h"
#include <QCoreApplication>
#include <QJsonArray>


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
	QJsonObject& settings = ApplicationSettings::getSettings();
	
	if (!settings.contains(dirProp) || !settings[dirProp].isArray())
		return QFileDialog::getExistingDirectory(parent,caption,appDir,options);
	
	QJsonArray array = settings[dirProp].toArray();
	if (array.size() != 2)
		return QFileDialog::getExistingDirectory(parent,caption,appDir,options);
	
	if (!array[0].isString() || !array[1].isString())
		return QFileDialog::getExistingDirectory(parent,caption,appDir,options);
	
	QString mode = array[0].toString();
	QString path = array[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QString str = QFileDialog::getExistingDirectory(parent,caption,path,options);
	if (mode == "Previous") {settings[dirProp] = QJsonArray{"Previous",str};}
	return str;
}

// GET OPEN FILE NAME /////////////////////////////////////////////////////////
QString MyFileDialog::getOpenFileName(QWidget *parent, const QString &caption, const QString &dirProp, const QString &filter, QString *selectedFilter, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	QJsonObject& settings = ApplicationSettings::getSettings();
	
	if (!settings.contains(dirProp) || !settings[dirProp].isArray())
		return QFileDialog::getOpenFileName(parent,caption,appDir,filter,selectedFilter,options);
	
	QJsonArray array = settings[dirProp].toArray();
	if (array.size() != 2)
		return QFileDialog::getOpenFileName(parent,caption,appDir,filter,selectedFilter,options);
	
	QString mode = array[0].toString();
	QString path = array[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QString str = QFileDialog::getOpenFileName(parent,caption,path,filter,selectedFilter,options);
	if (mode == "Previous") {settings[dirProp] = QJsonArray{"Previous",dirName(str)};}
	return str;
}

// GET OPEN FILE NAMES ////////////////////////////////////////////////////////
QStringList MyFileDialog::getOpenFileNames(QWidget *parent, const QString &caption, const QString &dirProp, const QString &filter, QString *selectedFilter, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	QJsonObject& settings = ApplicationSettings::getSettings();
	
	if (!settings.contains(dirProp) || !settings[dirProp].isArray())
		return QFileDialog::getOpenFileNames(parent,caption,appDir,filter,selectedFilter,options);
	
	QJsonArray array = settings[dirProp].toArray();
	if (array.size() != 2)
		return QFileDialog::getOpenFileNames(parent,caption,appDir,filter,selectedFilter,options);
	
	QString mode = array[0].toString();
	QString path = array[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QStringList list = QFileDialog::getOpenFileNames(parent,caption,path,filter,selectedFilter,options);
	if (list.size() == 0) {return {};}
	if (mode == "Previous") {settings[dirProp] = QJsonArray{"Previous",dirName(list[0])};}
	return list;
}

// GET SAVE FILE NAME /////////////////////////////////////////////////////////
QString MyFileDialog::getSaveFileName(QWidget *parent, const QString &caption, const QString &dirProp, const QString &filter, QString *selectedFilter, QFileDialog::Options options)
{
	QString appDir = QCoreApplication::applicationDirPath();
	QJsonObject& settings = ApplicationSettings::getSettings();
	
	if (!settings.contains(dirProp) || !settings[dirProp].isArray())
		return QFileDialog::getSaveFileName(parent,caption,appDir,filter,selectedFilter,options);
	
	QJsonArray array = settings[dirProp].toArray();
	if (array.size() != 2)
		return QFileDialog::getSaveFileName(parent,caption,appDir,filter,selectedFilter,options);
	
	QString mode = array[0].toString();
	QString path = array[1].toString();
	path.replace("$APPDIR",appDir);
	path.replace("//","/");
	
	QString str = QFileDialog::getSaveFileName(parent,caption,path,filter,selectedFilter,options);
	if (mode == "Previous") {settings[dirProp] = QJsonArray{"Previous",dirName(str)};}
	return str;
}

