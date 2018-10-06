#include "ThrustmasterWarthogJoystick.h"
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
ThrustmasterWarthogJoystick::ThrustmasterWarthogJoystick(GameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TG1" << "S2" << "S3" << "S4" << "S1" << "TG2" << "H2U" << "H2R" << "H2D" << "H2L";
	m_buttonsNames << "H3U" << "H3R" << "H3D" << "H3L" << "H4U" << "H4R" << "H4D" << "H4L" << "H4P";
	m_buttonsNames << "H1U" << "H1R" << "H1D" << "H1L";
	
	m_axesNames << "JOYX" << "JOYY";
	
	m_povsNames << "HAT1" << "HAT2" << "HAT3" << "HAT4";
	
	this->addVirtualPov(ThrustmasterWarthogJoystick_::H2U,
						ThrustmasterWarthogJoystick_::H2R,
						ThrustmasterWarthogJoystick_::H2D,
						ThrustmasterWarthogJoystick_::H2L,
						"HAT2");
	
	this->addVirtualPov(ThrustmasterWarthogJoystick_::H3U,
						ThrustmasterWarthogJoystick_::H3R,
						ThrustmasterWarthogJoystick_::H3D,
						ThrustmasterWarthogJoystick_::H3L,
						"HAT3");
	
	this->addVirtualPov(ThrustmasterWarthogJoystick_::H4U,
						ThrustmasterWarthogJoystick_::H4R,
						ThrustmasterWarthogJoystick_::H4D,
						ThrustmasterWarthogJoystick_::H4L,
						"HAT4");
}






// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterWarthogJoystick::slotGameControllerAxisEvent(GameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 1)      {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogJoystick_::JOYX, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogJoystick_::JOYY, false, event->value()};}
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::description() const
{
	return ThrustmasterWarthogJoystick_::Description;
}






// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint ThrustmasterWarthogJoystick::buttonsCount() const
{
	return 23;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::buttonName(uint button) const
{
	if (button < 23)
		return m_buttonsNames[button];
	else
		return {};
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
	if (axis == ThrustmasterWarthogJoystick_::JOYX) {return this->RealJoystick::axisValue(1);}
	if (axis == ThrustmasterWarthogJoystick_::JOYY) {return this->RealJoystick::axisValue(0);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::axisName(uint axis) const
{
	if (axis < 2)
		return m_axesNames[axis];
	else
		return {};
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogJoystick::axesNames() const
{
	return m_axesNames;
}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterWarthogJoystick::povsCount() const
{
	return 4;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogJoystick::povName(uint pov) const
{
	if (pov < 4)
		return m_povsNames[pov];
	else
		return {};
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogJoystick::povsNames() const
{
	return m_povsNames;
}

