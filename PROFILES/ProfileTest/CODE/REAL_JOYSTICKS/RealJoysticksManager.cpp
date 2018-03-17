#include "RealJoysticksManager.h"
#include "qgamecontroller.h"
#include "SPECIFIC_JOYSTICKS/WarthogJoystick.h"
#include "SPECIFIC_JOYSTICKS/WarthogThrottle.h"
#include "SPECIFIC_JOYSTICKS/MfgCrosswindRudderPedals.h"
const int NB_JOYSTICKS_MAX = 16;


RealJoysticksManager::RealJoysticksManager()
{
	for (int i=0; i<NB_JOYSTICKS_MAX; ++i)
	{
		QGameController *gameController = new QGameController(i);
		if (gameController->isValid())
		{
			m_joysticks << this->createJoystick(gameController);
		}
		else
		{
			delete gameController;
			break;
		}
	}
}

RealJoysticksManager::~RealJoysticksManager()
{
	qDeleteAll(m_joysticks);
	m_joysticks.clear();
}



AbstractRealJoystick* RealJoysticksManager::createJoystick(QGameController *c)
{
	Q_ASSERT(c);
	if (c->description() == "Joystick - HOTAS Warthog") {return new WarthogJoystick(c);}
	else if (c->description() == "Throttle - HOTAS Warthog") {return new WarthogThrottle(c);}
	else if (c->description() == "MFG Crosswind V2") {return new MfgCrosswindRudderPedals(c);}
	else {return new RealJoystick(c);}
}

int RealJoysticksManager::nbJoysticks() const
{
	return m_joysticks.size();
}

QStringList RealJoysticksManager::joysticksNames() const
{
	QStringList list;
	for (AbstractRealJoystick *j : m_joysticks) {list << j->description();}
	return list;
}

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

