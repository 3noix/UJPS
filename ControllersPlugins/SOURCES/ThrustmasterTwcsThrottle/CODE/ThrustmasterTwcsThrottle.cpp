#include "ThrustmasterTwcsThrottle.h"
#include "qgamecontroller.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  SLOT GAME CONTROLLER BUTTON EVENT
//  SLOT GAME CONTROLLER AXIS EVENT
//
//  DESCRIPTION
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
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
ThrustmasterTwcsThrottle::ThrustmasterTwcsThrottle(QGameController *c) : RealJoystick{c}
{
	m_oldAxis8Value = 0.0f;
	m_oldAxis9Value = 0.0f;
	
	m_buttonsNames << "TBTN1" << "TBTN2" << "TBTN3" << "TBTN4" << "TBTN5" << "TLOCK";
	m_buttonsNames << "THAT1U" << "THAT1R" << "THAT1D" << "THAT1L";
	m_buttonsNames << "THAT3U" << "THAT3R" << "THAT3D" << "THAT3L";
	m_buttonsNames << "THAT2U" << "THAT2R" << "THAT2D" << "THAT2L";
	
	m_axesNames << "TTHR" << "TRDR" << "TMSTX" << "TMSTY" << "TANT" << "TFRP1" << "TFRP2" << "TFRP3";
}





// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void ThrustmasterTwcsThrottle::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Button,event->button(),event->pressed(),0.0};
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterTwcsThrottle::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	
	uint axis = event->axis();
	float value = event->value();
	
	if (axis == 8)
	{
		if (value > 0)
		{
			if (m_oldAxis8Value < 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2L, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2R, true, 0.0};
		}
		else if (value == 0)
		{
			if (m_oldAxis8Value < 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2L, false, 0.0};}
			else if (m_oldAxis8Value > 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2R, false, 0.0};}
		}
		else
		{
			if (m_oldAxis8Value > 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2R, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2L, true, 0.0};
		}
		m_oldAxis8Value = value;
	}
	else if (axis == 9)
	{
		if (value > 0)
		{
			if (m_oldAxis9Value < 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2D, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2U, true, 0.0};
		}
		else if (value == 0)
		{
			if (m_oldAxis9Value < 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2D, false, 0.0};}
			else if (m_oldAxis9Value > 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2U, false, 0.0};}
		}
		else
		{
			if (m_oldAxis9Value > 0) {m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2U, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, ThrustmasterTwcsThrottle::THAT2D, true, 0.0};
		}
		m_oldAxis9Value = value;
	}
	else if (axis == 7) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TTHR,  false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TRDR,  false, event->value()};}
	else if (axis == 6) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TMSTX, false, event->value()};}
	else if (axis == 5) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TMSTY, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TANT,  false, event->value()};}
	else if (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TFRP1, false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TFRP2, false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterTwcsThrottle::TFRP3, false, event->value()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterTwcsThrottle::description() const
{
	return "TWCS Throttle";
}




// BUTTON COUNT ///////////////////////////////////////////////////////////////
uint ThrustmasterTwcsThrottle::buttonCount() const
{
	return 18;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool ThrustmasterTwcsThrottle::buttonPressed(uint button) const
{
	// normal buttons
	if (button < 14)
	{
		return this->RealJoystick::buttonPressed(button);
	}
	// POV
	else if (button < 18)
	{
		float h = this->RealJoystick::axisValue(8);
		float v = this->RealJoystick::axisValue(9);
		if (button == ThrustmasterTwcsThrottle::THAT2U) {return (h == 0 && v >  0);}
		if (button == ThrustmasterTwcsThrottle::THAT2R) {return (h >  0 && v == 0);}
		if (button == ThrustmasterTwcsThrottle::THAT2D) {return (h == 0 && v <  0);}
		if (button == ThrustmasterTwcsThrottle::THAT2L) {return (h <  0 && v == 0);}
	}
	
	return false;
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





// AXIS COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterTwcsThrottle::axisCount() const
{
	return 8;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float ThrustmasterTwcsThrottle::axisValue(uint axis) const
{
	if (axis == ThrustmasterTwcsThrottle::TTHR)  {return this->RealJoystick::axisValue(7);}
	if (axis == ThrustmasterTwcsThrottle::TRDR)  {return this->RealJoystick::axisValue(4);}
	if (axis == ThrustmasterTwcsThrottle::TMSTX) {return this->RealJoystick::axisValue(6);}
	if (axis == ThrustmasterTwcsThrottle::TMSTY) {return this->RealJoystick::axisValue(5);}
	if (axis == ThrustmasterTwcsThrottle::TANT)  {return this->RealJoystick::axisValue(0);}
	if (axis == ThrustmasterTwcsThrottle::TFRP1) {return this->RealJoystick::axisValue(1);}
	if (axis == ThrustmasterTwcsThrottle::TFRP2) {return this->RealJoystick::axisValue(2);}
	if (axis == ThrustmasterTwcsThrottle::TFRP3) {return this->RealJoystick::axisValue(3);}
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


