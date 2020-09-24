#ifndef APPLICATION_SETTINGS
#define APPLICATION_SETTINGS


#include <QJsonObject>


namespace ApplicationSettings
{
	QJsonObject& getSettings();
	bool readFile();
	bool writeFile();
};


#endif

