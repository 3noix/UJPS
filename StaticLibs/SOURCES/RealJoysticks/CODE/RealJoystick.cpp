#include "RealJoystick.h"
#include "qgamecontroller.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  ID
//  DESCRIPTION
//  HARDWARE ID
//  READ GAME CONTROLLER
//  CHANGES
//  SLOT GAME CONTROLLER BUTTON EVENT
//  SLOT GAME CONTROLLER AXIS EVENT
//
//  BUTTON COUNT
//  BUTTON PRESSED
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXIS COUNT
//  AXIS VALUE
//  AXIS NAME
//  AXES NAMES
//
//  SET DATA
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
RealJoystick::RealJoystick(QGameController *c) : QObject{}, AbstractRealJoystick{}
{
	Q_ASSERT(c);
	m_controller = c;
	
	QObject::connect(c,&QGameController::gameControllerButtonEvent,this,&RealJoystick::slotGameControllerButtonEvent);
	QObject::connect(c,&QGameController::gameControllerAxisEvent,this,&RealJoystick::slotGameControllerAxisEvent);
}

RealJoystick::~RealJoystick()
{
	if (m_controller)
	{
		delete m_controller;
		m_controller = nullptr;
	}
}




// ID /////////////////////////////////////////////////////////////////////////
uint RealJoystick::id() const
{
	return m_controller->id();
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString RealJoystick::description() const
{
	return m_controller->description();
}

// HARDWARE ID ////////////////////////////////////////////////////////////////
QString RealJoystick::hardwareId() const
{
	return m_controller->hardwareId();
}

// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void RealJoystick::readGameController()
{
	m_changes.clear();
	m_controller->readGameController();
}

// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> RealJoystick::changes()
{
	return m_changes;
}

// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void RealJoystick::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Button,event->button(),event->pressed(),0.0};
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void RealJoystick::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Axis,event->axis(),false,event->value()};
}




// BUTTON COUNT ///////////////////////////////////////////////////////////////
uint RealJoystick::buttonCount() const {return m_controller->buttonCount();}
// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool RealJoystick::buttonPressed(uint button) const {return m_controller->buttonValue(button);}
// BUTTON NAME ////////////////////////////////////////////////////////////////
QString RealJoystick::buttonName(uint button) const {return "Button " + QString::number(button);}
// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList RealJoystick::buttonsNames() const
{
	QStringList list;
	for (uint i=0; i<this->buttonCount(); ++i) {list << this->buttonName(i);}
	return list;
}


// AXIS COUNT /////////////////////////////////////////////////////////////////
uint RealJoystick::axisCount() const {return m_controller->axisCount();}
// AXIS VALUE /////////////////////////////////////////////////////////////////
float RealJoystick::axisValue(uint axis) const {return m_controller->axisValue(axis);}
// AXIS NAME //////////////////////////////////////////////////////////////////
QString RealJoystick::axisName(uint axis) const {return "Axis " + QString::number(axis);}
// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList RealJoystick::axesNames() const
{
	QStringList list;
	for (uint i=0; i<this->axisCount(); ++i) {list << this->axisName(i);}
	return list;
}


// SET DATA ///////////////////////////////////////////////////////////////////
void RealJoystick::setData(const QString &str, QVariant v)
{
	Q_UNUSED(str)
	Q_UNUSED(v)
}




