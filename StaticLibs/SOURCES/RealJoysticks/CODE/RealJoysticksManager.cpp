#include "RealJoysticksManager.h"
#include "RealJoystick.h"
#include "AbstractRealJoystickFactory.h"
#include "GameController.h"

#include <QPluginLoader>
#include <QDir>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  LOAD PLUGINS
//  UNLOAD PLUGINS
//
//  SEARCH FOR REAL JOYSTICKS
//  FROM GAME CONTROLLERS
//  CREATE JOYSTICK
//
//  NB JOYSTICKS
//  JOYSTICKS NAMES
//  JOYSTICK
//  RELEASE JOYSTICK
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
				m_loaders << loader;
				m_factories << factory;
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






// SEARCH FOR REAL JOYSTICKS //////////////////////////////////////////////////
void RealJoysticksManager::searchForRealJoysticks()
{
	// search for DirectInput and XInput controllers
	QVector<GameController*> joysticks = GameController::enumerateControllers();
	
	// upgrade them
	this->fromGameControllers(joysticks);
}

// FROM GAME CONTROLLERS //////////////////////////////////////////////////////
void RealJoysticksManager::fromGameControllers(QVector<GameController*> &gcv)
{
	// reset
	qDeleteAll(m_joysticks);
	m_joysticks.clear();
	
	// build RealJoysticks objects
	for (GameController *gc : gcv)
	{
		if (AbstractRealJoystick *j = this->createJoystick(gc)) {m_joysticks << j;}
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

// RELEASE ALL ////////////////////////////////////////////////////////////////
QVector<AbstractRealJoystick*> RealJoysticksManager::releaseAll()
{
	QVector<AbstractRealJoystick*> joys = m_joysticks;
	m_joysticks.clear();
	return joys;
}

