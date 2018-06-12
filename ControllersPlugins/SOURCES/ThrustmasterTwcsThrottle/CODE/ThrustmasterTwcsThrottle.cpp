#include "ThrustmasterTwcsThrottle.h"
#include "qgamecontroller.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  SLOT GAME CONTROLLER AXIS EVENT
//  SLOT GAME CONTROLLER POV EVENT
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
//  POV VALUE
//  POV NAME
//  POVS NAMES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
ThrustmasterTwcsThrottle::ThrustmasterTwcsThrottle(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TBTN1" << "TBTN2" << "TBTN3" << "TBTN4" << "TBTN5" << "TLOCK";
	m_buttonsNames << "THAT1U" << "THAT1R" << "THAT1D" << "THAT1L";
	m_buttonsNames << "THAT3U" << "THAT3R" << "THAT3D" << "THAT3L";
	m_buttonsNames << "THAT2U" << "THAT2R" << "THAT2D" << "THAT2L";
	
	m_axesNames << "TTHR" << "TRDR" << "TMSTX" << "TMSTY" << "TANT" << "TFRP1" << "TFRP2" << "TFRP3";
	
	m_povsNames << "HAT1" << "HAT2" << "HAT3";
	
	this->addVirtualPov(ThrustmasterTwcsThrottle_::THAT1U,
						ThrustmasterTwcsThrottle_::THAT1R,
						ThrustmasterTwcsThrottle_::THAT1D,
						ThrustmasterTwcsThrottle_::THAT1L,
						"HAT1");
	
	this->addVirtualPov(ThrustmasterTwcsThrottle_::THAT3U,
						ThrustmasterTwcsThrottle_::THAT3R,
						ThrustmasterTwcsThrottle_::THAT3D,
						ThrustmasterTwcsThrottle_::THAT3L,
						"HAT3");
}





// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterTwcsThrottle::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 7)      {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TTHR,  false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TRDR,  false, event->value()};}
	else if (axis == 6) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TMSTX, false, event->value()};}
	else if (axis == 5) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TMSTY, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TANT,  false, event->value()};}
	else if (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TFRP1, false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TFRP2, false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle_::TFRP3, false, event->value()};}
}

// SLOT GAME CONTROLLER POV EVENT /////////////////////////////////////////////
void ThrustmasterTwcsThrottle::slotGameControllerPovEvent(QGameControllerPovEvent *event)
{
	Q_ASSERT(event);
	uint pov = event->pov();
	
	if (pov == 1)      {m_changes << JoystickChange{this, ControlType::Pov, ThrustmasterTwcsThrottle_::HAT1, false, event->angle()};}
	else if (pov == 0) {m_changes << JoystickChange{this, ControlType::Pov, ThrustmasterTwcsThrottle_::HAT2, false, event->angle()};}
	else if (pov == 2) {m_changes << JoystickChange{this, ControlType::Pov, ThrustmasterTwcsThrottle_::HAT3, false, event->angle()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterTwcsThrottle::description() const
{
	return ThrustmasterTwcsThrottle_::Description;
}




// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint ThrustmasterTwcsThrottle::buttonsCount() const
{
	return 18;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString ThrustmasterTwcsThrottle::buttonName(uint button) const
{
	if (button < 18)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList ThrustmasterTwcsThrottle::buttonsNames() const
{
	return m_buttonsNames;
}





// AXES COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterTwcsThrottle::axesCount() const
{
	return 8;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float ThrustmasterTwcsThrottle::axisValue(uint axis) const
{
	if (axis == ThrustmasterTwcsThrottle_::TTHR)  {return this->RealJoystick::axisValue(7);}
	if (axis == ThrustmasterTwcsThrottle_::TRDR)  {return this->RealJoystick::axisValue(4);}
	if (axis == ThrustmasterTwcsThrottle_::TMSTX) {return this->RealJoystick::axisValue(6);}
	if (axis == ThrustmasterTwcsThrottle_::TMSTY) {return this->RealJoystick::axisValue(5);}
	if (axis == ThrustmasterTwcsThrottle_::TANT)  {return this->RealJoystick::axisValue(0);}
	if (axis == ThrustmasterTwcsThrottle_::TFRP1) {return this->RealJoystick::axisValue(1);}
	if (axis == ThrustmasterTwcsThrottle_::TFRP2) {return this->RealJoystick::axisValue(2);}
	if (axis == ThrustmasterTwcsThrottle_::TFRP3) {return this->RealJoystick::axisValue(3);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString ThrustmasterTwcsThrottle::axisName(uint axis) const
{
	if (axis < 8)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterTwcsThrottle::axesNames() const
{
	return m_axesNames;
}




// POVS COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterTwcsThrottle::povsCount() const
{
	return 3;
}

// POV VALUE //////////////////////////////////////////////////////////////////
float ThrustmasterTwcsThrottle::povValue(uint pov) const
{
	if (pov == ThrustmasterTwcsThrottle_::HAT1)      {return this->RealJoystick::povValue(1);}
	else if (pov == ThrustmasterTwcsThrottle_::HAT2) {return this->RealJoystick::povValue(0);}
	else if (pov == ThrustmasterTwcsThrottle_::HAT3) {return this->RealJoystick::povValue(2);}
	return -1.0f;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString ThrustmasterTwcsThrottle::povName(uint pov) const
{
	if (pov < 3)
		return m_povsNames[pov];
	else
		return QString();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterTwcsThrottle::povsNames() const
{
	return m_povsNames;
}


