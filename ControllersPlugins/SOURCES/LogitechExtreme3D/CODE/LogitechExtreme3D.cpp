#include "LogitechExtreme3D.h"
#include "GameController.h"
#include "GameControllerEvents.h"


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
LogitechExtreme3D::LogitechExtreme3D(GameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TG" << "THMB";
	m_buttonsNames << "SBDL" << "SBDR" << "SBUL" << "SBUR";
	m_buttonsNames << "BBUL" << "BBUR" << "BBML" << "BBMR" << "BBDL" << "BBDR";
	m_buttonsNames << "POVU" << "POVR" << "POVD" << "POVL";
	
	m_axesNames << "JOYX" << "JOYY" << "JOYZ" << "THR";
	
	m_povsNames << "POV1";
}





// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void LogitechExtreme3D::slotGameControllerAxisEvent(GameControllerAxisEvent *event)
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
	return LogitechExtreme3D_::Description;
}




// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint LogitechExtreme3D::buttonsCount() const
{
	return 16;
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




// POVS COUNT /////////////////////////////////////////////////////////////////
uint LogitechExtreme3D::povsCount() const
{
	return 1;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString LogitechExtreme3D::povName(uint pov) const
{
	if (pov < 1)
		return m_povsNames[pov];
	else
		return QString();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList LogitechExtreme3D::povsNames() const
{
	return m_povsNames;
}


