#include "ApplicationSettings.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QFile>

QJsonObject settings;


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  GET SETTINGS
//  READ FILE
//  WRITE FILE
///////////////////////////////////////////////////////////////////////////////


namespace ApplicationSettings {
// GET SETTINGS ///////////////////////////////////////////////////////////////
QJsonObject& getSettings()
{
	return settings;
}

// READ FILE //////////////////////////////////////////////////////////////////
bool readFile()
{
	QString filePath = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + "Settings.json";
	QFile file{filePath};
	if (!file.open(QIODevice::ReadOnly)) {return false;}
	QByteArray data = file.readAll();
	file.close();
	
	QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
	if (!jsonDoc.isObject()) {return false;}
	settings = jsonDoc.object();
	return true;
}

// WRITE FILE /////////////////////////////////////////////////////////////////
bool writeFile()
{
	QJsonDocument jsonDoc{settings};
	QString filePath = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + "Settings.json";
	QFile file{filePath};
	if (!file.open(QIODevice::WriteOnly)) {return false;}
	qint64 bytesWritten = file.write(jsonDoc.toJson());
	file.close();
	return (bytesWritten > 0);
}
}

