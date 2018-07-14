#include "RealJoysticksManager.h"
#include "RealJoystick.h"
#include "AbstractRealJoystickFactory.h"

#include "GameControllerDirectInput.h"
#include "GameControllerXInput.h"
#include <QPluginLoader>
#include <QDir>
const int NB_JOYSTICKS_MAX_DIRECTINPUT = 16;
const int NB_JOYSTICKS_MAX_XINPUT = 4;


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
	// search for DirectInput controllers
	for (int i=0; i<NB_JOYSTICKS_MAX_DIRECTINPUT; ++i)
	{
		GameController *gameController = new GameControllerDirectInput(i);
		if (gameController->isValid() && gameController->description() != "Controller (XBOX 360 For Windows)")
		{
			
			if (AbstractRealJoystick *j = this->createJoystick(gameController))
				m_joysticks << j;
		}
		else {delete gameController;}
	}
	
	// search for XInput controllers
	for (int i=0; i<NB_JOYSTICKS_MAX_XINPUT; ++i)
	{
		GameController *gameController = new GameControllerXInput(i);
		if (gameController->isValid())
		{
			
			if (AbstractRealJoystick *j = this->createJoystick(gameController))
				m_joysticks << j;
		}
		else {delete gameController;}
	}
}

// CREATE JOYSTICK ////////////////////////////////////////////////////////////
AbstractRealJoystick* RealJoysticksManager::createJoystick(GameController *c)
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

AbstractRealJoystick* RealJoysticksManager::joystick(const QString &joystickName, int num) const
{
	int compteur = 0;
	for (AbstractRealJoystick *j : m_joysticks)
	{
		if (j->description() == joystickName)
		{
			if (compteur == num)
				return j;
			else
				++compteur;
		}
	}
	
	return nullptr;
}

// RELEASE JOYSTICK ///////////////////////////////////////////////////////////
AbstractRealJoystick* RealJoysticksManager::releaseJoystick(int id)
{
	if (id <0 || id >= m_joysticks.size()) {return nullptr;}
	return m_joysticks.takeAt(id);
}

AbstractRealJoystick* RealJoysticksManager::releaseJoystick(const QString &joystickName, int num)
{
	int compteur = 0;
	for (int i=0; i<m_joysticks.size(); ++i)
	{
		if (m_joysticks[i]->description() == joystickName)
		{
			if (compteur == num)
				return m_joysticks.takeAt(i);
			else
				++compteur;
		}
	}
	
	return nullptr;
}

