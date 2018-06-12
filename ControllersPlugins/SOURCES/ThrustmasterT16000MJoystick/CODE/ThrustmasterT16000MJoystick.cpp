#include "ThrustmasterT16000MJoystick.h"
#include "qgamecontroller.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  SLOT GAME CONTROLLER AXIS EVENT
//
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
ThrustmasterT16000MJoystick::ThrustmasterT16000MJoystick(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TS1" << "TS2" << "TS3" << "TS4";
	m_buttonsNames << "B5" << "B6" << "B7" << "B8" << "B9" << "B10";
	m_buttonsNames << "B11" << "B12" << "B13" << "B14" << "B15" << "B16";
	m_buttonsNames << "H1U" << "H1R" << "H1D" << "H1L";
	
	m_axesNames << "JOYX" << "JOYY" << "RUDDER" << "THR";
	
	m_povsNames << "HAT1";
}





// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterT16000MJoystick::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 0)      {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterT16000MJoystick_::JOYX,   false, event->value()};}
	else if (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterT16000MJoystick_::JOYY,   false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterT16000MJoystick_::RUDDER, false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterT16000MJoystick_::THR,    false, event->value()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterT16000MJoystick::description() const
{
	return ThrustmasterT16000MJoystick_::Description;
}




// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint ThrustmasterT16000MJoystick::buttonsCount() const
{
	return 20;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString ThrustmasterT16000MJoystick::buttonName(uint button) const
{
	if (button < 20)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList ThrustmasterT16000MJoystick::buttonsNames() const
{
	return m_buttonsNames;
}





// AXES COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterT16000MJoystick::axesCount() const
{
	return 4;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float ThrustmasterT16000MJoystick::axisValue(uint axis) const
{
	if (axis == ThrustmasterT16000MJoystick_::JOYX)   {return this->RealJoystick::axisValue(0);}
	if (axis == ThrustmasterT16000MJoystick_::JOYY)   {return this->RealJoystick::axisValue(1);}
	if (axis == ThrustmasterT16000MJoystick_::RUDDER) {return this->RealJoystick::axisValue(3);}
	if (axis == ThrustmasterT16000MJoystick_::THR)    {return this->RealJoystick::axisValue(2);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString ThrustmasterT16000MJoystick::axisName(uint axis) const
{
	if (axis < 4)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterT16000MJoystick::axesNames() const
{
	return m_axesNames;
}




// POVS COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterT16000MJoystick::povsCount() const
{
	return 1;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString ThrustmasterT16000MJoystick::povName(uint pov) const
{
	if (pov < 1)
		return m_povsNames[pov];
	else
		return QString();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterT16000MJoystick::povsNames() const
{
	return m_povsNames;
}

