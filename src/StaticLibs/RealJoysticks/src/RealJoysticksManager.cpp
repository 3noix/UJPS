#include "RealJoysticksManager.h"
#include "RealJoystick.h"
#include "AbstractRealJoystickFactory.h"
#include "../../QtGameControllerModif/src/GameController.h"

#include <QPluginLoader>
#include <QDir>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  LOAD PLUGINS
//  UNLOAD PLUGINS
//
//  FROM GAME CONTROLLERS
//  CREATE JOYSTICK
//
//  NB JOYSTICKS
//  JOYSTICKS NAMES
//  JOYSTICK
//  RELEASE ALL
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
			if (AbstractRealJoystickFactory* factory = qobject_cast<AbstractRealJoystickFactory*>(plugin))
			{
				m_loaders.push_back(loader);
				m_factories.push_back(factory);
				continue;
			}
		}
		delete loader;
	}
}

// UNLOAD PLUGINS /////////////////////////////////////////////////////////////
void RealJoysticksManager::unloadPlugins()
{
	qDeleteAll(m_loaders);
	m_loaders.clear();
	m_factories.clear();
}






// FROM GAME CONTROLLERS //////////////////////////////////////////////////////
void RealJoysticksManager::fromGameControllers(std::vector<GameController*> &gcv)
{
	// reset
	qDeleteAll(m_joysticks);
	m_joysticks.clear();
	
	// build RealJoysticks objects
	for (GameController *gc : gcv)
	{
		if (AbstractRealJoystick *j = this->createJoystick(gc)) {m_joysticks.push_back(j);}
		else {delete gc;}
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
AbstractRealJoystick* RealJoysticksManager::joystick(uint id) const
{
	if (id >= m_joysticks.size()) {return nullptr;}
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

// RELEASE ALL ////////////////////////////////////////////////////////////////
std::vector<AbstractRealJoystick*> RealJoysticksManager::releaseAll()
{
	std::vector<AbstractRealJoystick*> joys = m_joysticks;
	m_joysticks.clear();
	return joys;
}

