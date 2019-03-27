#include "ApplicationSettings.h"
#include <QCoreApplication>
ApplicationSettings ApplicationSettings::m_instance;


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  INSTANCE
//  READ FILE
//  WRITE FILE
//  PROPERTY
//  SET PROPERTY
//  CONTAINS
//  IS EMPTY
///////////////////////////////////////////////////////////////////////////////


// INSTANCE ///////////////////////////////////////////////////////////////////
ApplicationSettings& ApplicationSettings::instance()
{
	return m_instance;
}

// READ FILE //////////////////////////////////////////////////////////////////
bool ApplicationSettings::readFile()
{
	return m_settings.readFile(QCoreApplication::applicationDirPath() + "/../SETTINGS/ApplicationSettings.xml");
}

// WRITE FILE /////////////////////////////////////////////////////////////////
bool ApplicationSettings::writeFile()
{
	return m_settings.writeFile(QCoreApplication::applicationDirPath() + "/../SETTINGS/ApplicationSettings.xml");
}

// PROPERTY ///////////////////////////////////////////////////////////////////
QVariant ApplicationSettings::property(const QString &name)
{
	return m_settings.property(name);
}

// SET PROPERTY ///////////////////////////////////////////////////////////////
bool ApplicationSettings::setProperty(const QString &name, const QVariant &value)
{
	//if (!m_settings.contains(name)) {return false;}
	m_settings.addProperty(name,value);
	return true;
}

// CONTAINS ///////////////////////////////////////////////////////////////////
bool ApplicationSettings::contains(const QString &name)
{
	return m_settings.contains(name);
}

// IS EMPTY ///////////////////////////////////////////////////////////////////
bool ApplicationSettings::isEmpty() const
{
	return m_settings.isEmpty();
}

