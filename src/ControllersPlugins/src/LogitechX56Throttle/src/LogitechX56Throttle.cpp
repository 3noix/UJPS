#include "LogitechX56Throttle.h"
#include "QtGameControllerModif/GameController.h"


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
LogitechX56Throttle::LogitechX56Throttle(GameController *c) : RealJoystick{c}
{
	m_buttonsNames << "E" << "F" << "G" << "I" << "H";
	m_buttonsNames << "SW1" << "SW2" << "SW3" << "SW4" << "SW5" << "SW6";
	m_buttonsNames << "T1U" << "T1D" << "T2U" << "T2D" << "T3U" << "T3D" << "T3U" << "T3D";
	m_buttonsNames << "H3U" << "H3R" << "H3D" << "H3L" << "H4U" << "H4R" << "H4D" << "H4L";
	m_buttonsNames << "K1U" << "K1D" << "SFWD" << "SBCK" << "STK" << "SLD";
	m_buttonsNames << "M1" << "M2" << "S1";
	
	m_axesNames << "THR_LEFT" << "THR_RIGHT" << "JOYROTX" << "JOYROTY" << "RTY1" <<  "RTY2" << "RTY3" << "RTY4";
	
	m_povsNames << "HAT1" << "HAT2";
	
	this->addVirtualPov(LogitechX56Throttle_::H3U,
						LogitechX56Throttle_::H3R,
						LogitechX56Throttle_::H3D,
						LogitechX56Throttle_::H3L,
						"HAT1");
	
	this->addVirtualPov(LogitechX56Throttle_::H4U,
						LogitechX56Throttle_::H4R,
						LogitechX56Throttle_::H4D,
						LogitechX56Throttle_::H4L,
						"HAT2");
}






// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void LogitechX56Throttle::slotGameControllerAxisEvent(GameControllerAxisEvent event)
{
	uint axis = event.axis;
	float f = event.value;
	
	if      (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::THR_LEFT,  false, f};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::THR_RIGHT, false, f};}
	else if (axis == 6) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::JOYROTX,   false, f};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::JOYROTY,   false, f};}
	else if (axis == 7) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::RTY1,      false, f};}
	else if (axis == 5) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::RTY2,      false, f};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::RTY3,      false, f};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, LogitechX56Throttle_::RTY4,      false, f};}
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString LogitechX56Throttle::description() const
{
	return LogitechX56Throttle_::Description;
}






// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint LogitechX56Throttle::buttonsCount() const
{
	return 36;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString LogitechX56Throttle::buttonName(uint button) const
{
	if (button < this->buttonsCount())
		return m_buttonsNames[button];
	else
		return {};
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList LogitechX56Throttle::buttonsNames() const
{
	return m_buttonsNames;
}






// AXES COUNT /////////////////////////////////////////////////////////////////
uint LogitechX56Throttle::axesCount() const
{
	return 8;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float LogitechX56Throttle::axisValue(uint axis) const
{
	if      (axis == LogitechX56Throttle_::THR_LEFT)  {return this->RealJoystick::axisValue(1);}
	else if (axis == LogitechX56Throttle_::THR_RIGHT) {return this->RealJoystick::axisValue(0);}
	else if (axis == LogitechX56Throttle_::JOYROTX)   {return this->RealJoystick::axisValue(6);}
	else if (axis == LogitechX56Throttle_::JOYROTY)   {return this->RealJoystick::axisValue(4);}
	else if (axis == LogitechX56Throttle_::RTY1)      {return this->RealJoystick::axisValue(7);}
	else if (axis == LogitechX56Throttle_::RTY2)      {return this->RealJoystick::axisValue(5);}
	else if (axis == LogitechX56Throttle_::RTY3)      {return this->RealJoystick::axisValue(2);}
	else if (axis == LogitechX56Throttle_::RTY4)      {return this->RealJoystick::axisValue(3);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString LogitechX56Throttle::axisName(uint axis) const
{
	if (axis < this->axesCount())
		return m_axesNames[axis];
	else
		return {};
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList LogitechX56Throttle::axesNames() const
{
	return m_axesNames;
}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint LogitechX56Throttle::povsCount() const
{
	return 2;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString LogitechX56Throttle::povName(uint pov) const
{
	if (pov < this->povsCount())
		return m_povsNames[pov];
	else
		return {};
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList LogitechX56Throttle::povsNames() const
{
	return m_povsNames;
}

