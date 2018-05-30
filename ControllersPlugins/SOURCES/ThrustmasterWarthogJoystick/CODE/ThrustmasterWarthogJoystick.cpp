#include "ThrustmasterWarthogJoystick.h"
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
ThrustmasterWarthogJoystick::ThrustmasterWarthogJoystick(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TG1" << "S2" << "S3" << "S4" << "S1" << "TG2" << "H2U" << "H2R" << "H2D" << "H2L";
	m_buttonsNames << "H3U" << "H3R" << "H3D" << "H3L" << "H4U" << "H4R" << "H4D" << "H4L";
	m_buttonsNames << "H1U" << "H1R" << "H1D" << "H1L";
	
	m_axesNames << "JOYX" << "JOYY";
}


// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void ThrustmasterWarthogJoystick::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Button,event->button(),event->pressed(),0.0};
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterWarthogJoystick::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 1)      {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogJoystick::JOYX, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogJoystick::JOYY, false, event->value()};}
}




// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::description() const
{
	return "Joystick - HOTAS Warthog";
}





// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint ThrustmasterWarthogJoystick::buttonsCount() const
{
	return 23;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool ThrustmasterWarthogJoystick::buttonPressed(uint button) const
{
	// normal buttons and POV virtual buttons
	return this->RealJoystick::buttonPressed(button);
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::buttonName(uint button) const
{
	if (button < 23)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogJoystick::buttonsNames() const
{
	return m_buttonsNames;
}




// AXES COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterWarthogJoystick::axesCount() const
{
	return 2;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float ThrustmasterWarthogJoystick::axisValue(uint axis) const
{
	if (axis == ThrustmasterWarthogJoystick::JOYX) {return this->RealJoystick::axisValue(1);}
	if (axis == ThrustmasterWarthogJoystick::JOYY) {return this->RealJoystick::axisValue(0);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::axisName(uint axis) const
{
	if (axis < 2)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogJoystick::axesNames() const
{
	return m_axesNames;
}

