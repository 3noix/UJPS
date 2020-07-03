#include "LogitechX56Joystick.h"
#include "GameController.h"
#include "GameControllerEvents.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  SLOT GAME CONTROLLER AXIS EVENT
//  DESCRIPTION
//
//  BUTTONS COUNT
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXES COUNT
//  AXIS VALUE
//  AXIS NAME
//  AXES NAMES
//
//  POVS COUNT
//  POV NAME
//  POVS NAMES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
LogitechX56Joystick::LogitechX56Joystick(GameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TG1" << "A" << "B" << "STK" << "D" << "LVR" << "H1U" << "H1R" << "H1D" << "H1L";
	m_buttonsNames << "H2U" << "H2R" << "H2D" << "H2L" << "M1" << "M2" << "S1" << "POVU" << "POVR";
	m_buttonsNames << "POVD" << "POVL";
	
	m_axesNames << "JOYX" << "JOYY" << "RUDDER" << "JOYROTX" << "JOYROTY";
	
	m_povsNames << "HAT1" << "HAT2" << "HAT3";
	
	this->addVirtualPov(LogitechX56Joystick_::H1U,
						LogitechX56Joystick_::H1R,
						LogitechX56Joystick_::H1D,
						LogitechX56Joystick_::H1L,
						"HAT2");
	
	this->addVirtualPov(LogitechX56Joystick_::H2U,
						LogitechX56Joystick_::H2R,
						LogitechX56Joystick_::H2D,
						LogitechX56Joystick_::H2L,
						"HAT3");
}






// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void LogitechX56Joystick::slotGameControllerAxisEvent(GameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if      (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Joystick_::JOYX,    false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Joystick_::JOYY,    false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Joystick_::RUDDER,  false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Joystick_::JOYROTX, false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Joystick_::JOYROTY, false, event->value()};}
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString LogitechX56Joystick::description() const
{
	return LogitechX56Joystick_::Description;
}






// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint LogitechX56Joystick::buttonsCount() const
{
	return 21;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString LogitechX56Joystick::buttonName(uint button) const
{
	if (button < this->buttonsCount())
		return m_buttonsNames[button];
	else
		return {};
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList LogitechX56Joystick::buttonsNames() const
{
	return m_buttonsNames;
}






// AXES COUNT /////////////////////////////////////////////////////////////////
uint LogitechX56Joystick::axesCount() const
{
	return 5;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float LogitechX56Joystick::axisValue(uint axis) const
{
	if      (axis == LogitechX56Joystick_::JOYX)    {return this->RealJoystick::axisValue(1);}
	else if (axis == LogitechX56Joystick_::JOYY)    {return this->RealJoystick::axisValue(0);}
	else if (axis == LogitechX56Joystick_::RUDDER)  {return this->RealJoystick::axisValue(2);}
	else if (axis == LogitechX56Joystick_::JOYROTX) {return this->RealJoystick::axisValue(4);}
	else if (axis == LogitechX56Joystick_::JOYROTY) {return this->RealJoystick::axisValue(3);}
	
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString LogitechX56Joystick::axisName(uint axis) const
{
	if (axis < this->axesCount())
		return m_axesNames[axis];
	else
		return {};
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList LogitechX56Joystick::axesNames() const
{
	return m_axesNames;
}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint LogitechX56Joystick::povsCount() const
{
	return 3;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString LogitechX56Joystick::povName(uint pov) const
{
	if (pov < this->povsCount())
		return m_povsNames[pov];
	else
		return {};
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList LogitechX56Joystick::povsNames() const
{
	return m_povsNames;
}

