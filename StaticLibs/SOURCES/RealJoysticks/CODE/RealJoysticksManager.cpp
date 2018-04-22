#include "RealJoysticksManager.h"
#include "RealJoystick.h"
#include "AbstractRealJoystickFactory.h"

#include "qgamecontroller.h"
#include <QPluginLoader>
#include <QDir>
const int NB_JOYSTICKS_MAX = 16;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  LOAD PLUGINS
//  SEARCH FOR CONTROLLERS
//  CREATE JOYSTICK
//
//  NB JOYSTICKS
//  JOYSTICKS NAMES
//  JOYSTICK
//  RELEASE JOYSTICK
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
RealJoysticksManager::RealJoysticksManager() : QObject{}
{
	
}

RealJoysticksManager::~RealJoysticksManager()
{
	qDeleteAll(m_joysticks);
	qDeleteAll(m_loaders);
}

// LOAD PLUGINS ///////////////////////////////////////////////////////////////
void RealJoysticksManager::loadPlugins(const QString &path)
{
	QStringList dllNames = QDir{path}.entryList({"*.dll"},QDir::Files);
	for (const QString &name : dllNames)
	{
		QPluginLoader *loader = new QPluginLoader(path + "/" + name);
		if (QObject *plugin = loader->instance())
		{
			AbstractRealJoystickFactory* factory = qobject_cast<AbstractRealJoystickFactory*>(plugin);
			if (factory)
			{
				m_loaders << loader;
				m_factories << factory;
				continue;
			}
		}
		delete loader;
	}
}

// SEARCH FOR CONTROLLERS /////////////////////////////////////////////////////
void RealJoysticksManager::searchForControllers()
{
	for (int i=0; i<NB_JOYSTICKS_MAX; ++i)
	{
		QGameController *gameController = new QGameController(i);
		if (gameController->isValid())
		{
			
			if (AbstractRealJoystick *j = this->createJoystick(gameController))
				m_joysticks << j;
		}
		else
		{
			delete gameController;
			break;
		}
	}
}

// CREATE JOYSTICK ////////////////////////////////////////////////////////////
AbstractRealJoystick* RealJoysticksManager::createJoystick(QGameController *c)
{
	if (!c) {return nullptr;}
	QString d = c->description();
	
	for (AbstractRealJoystickFactory* factory : m_factories)
	{
		if (factory->supportedJoystick() == d)
			return factory->createRealJoystick(c);
	}
	
	emit message("Warning: no plugin found for controller: " + d, QColor{255,127,0});
	return new RealJoystick{c};
}





// NB JOYSTICKS ///////////////////////////////////////////////////////////////
int RealJoysticksManager::nbJoysticks() const
{
	return m_joysticks.size();
}

// JOYSTICKS NAMES ////////////////////////////////////////////////////////////
QStringList RealJoysticksManager::joysticksNames() const
{
	QStringList list;
	for (AbstractRealJoystick *j : m_joysticks) {list << j->description();}
	return list;
}

// JOYSTICK ///////////////////////////////////////////////////////////////////
AbstractRealJoystick* RealJoysticksManager::joystick(int id) const
{
	if (id <0 || id >= m_joysticks.size()) {return nullptr;}
	return m_joysticks[id];
}

AbstractRealJoystick* RealJoysticksManager::joystick(const QString &joystickName) const
{
	for (AbstractRealJoystick *j : m_joysticks)
	{
		if (j->description() == joystickName)
		{return j;}
	}
	
	return nullptr;
}

// RELEASE JOYSTICK ///////////////////////////////////////////////////////////
AbstractRealJoystick* RealJoysticksManager::releaseJoystick(int id)
{
	if (id <0 || id >= m_joysticks.size()) {return nullptr;}
	return m_joysticks.takeAt(id);
}

AbstractRealJoystick* RealJoysticksManager::releaseJoystick(const QString &joystickName)
{
	for (int i=0; i<m_joysticks.size(); ++i)
	{
		if (m_joysticks[i]->description() == joystickName)
		{return m_joysticks.takeAt(i);}
	}
	
	return nullptr;
}

