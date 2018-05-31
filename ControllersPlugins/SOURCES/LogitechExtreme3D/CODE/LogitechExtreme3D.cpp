#include "LogitechExtreme3D.h"
#include "qgamecontroller.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  SLOT GAME CONTROLLER BUTTON EVENT
//  SLOT GAME CONTROLLER AXIS EVENT
//
//  DESCRIPTION
//
//  BUTTONS COUNT
//  BUTTON PRESSED
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXES COUNT
//  AXIS VALUE
//  AXIS NAME
//  AXES NAMES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
LogitechExtreme3D::LogitechExtreme3D(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TG" << "THMB";
	m_buttonsNames << "SBDL" << "SBDR" << "SBUL" << "SBUR";
	m_buttonsNames << "BBUL" << "BBUR" << "BBML" << "BBMR" << "BBDL" << "BBDR";
	m_buttonsNames << "POVU" << "POVR" << "POVD" << "POVL";
	
	m_axesNames << "JOYX" << "JOYY" << "JOYZ" << "THR";
}





// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void LogitechExtreme3D::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Button,event->button(),event->pressed(),0.0};
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void LogitechExtreme3D::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 1)      {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D_::JOYX, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D_::JOYY, false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D_::JOYZ, false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D_::THR,  false, event->value()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString LogitechExtreme3D::description() const
{
	return "Logitech Extreme 3D";
}




// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint LogitechExtreme3D::buttonsCount() const
{
	return 16;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool LogitechExtreme3D::buttonPressed(uint button) const
{
	// normal buttons and POV virtual buttons
	return this->RealJoystick::buttonPressed(button);
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString LogitechExtreme3D::buttonName(uint button) const
{
	if (button < 16)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList LogitechExtreme3D::buttonsNames() const
{
	return m_buttonsNames;
}





// AXES COUNT /////////////////////////////////////////////////////////////////
uint LogitechExtreme3D::axesCount() const
{
	return 4;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float LogitechExtreme3D::axisValue(uint axis) const
{
	if (axis == LogitechExtreme3D_::JOYX) {return this->RealJoystick::axisValue(1);}
	if (axis == LogitechExtreme3D_::JOYY) {return this->RealJoystick::axisValue(0);}
	if (axis == LogitechExtreme3D_::JOYZ) {return this->RealJoystick::axisValue(2);}
	if (axis == LogitechExtreme3D_::THR)  {return this->RealJoystick::axisValue(3);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString LogitechExtreme3D::axisName(uint axis) const
{
	if (axis < 4)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList LogitechExtreme3D::axesNames() const
{
	return m_axesNames;
}


