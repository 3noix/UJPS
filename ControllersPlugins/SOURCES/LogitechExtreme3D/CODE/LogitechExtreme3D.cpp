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
LogitechExtreme3D::LogitechExtreme3D(QGameController *c) : RealJoystick{c}
{
	m_oldAxis2Value = 0.0f;
	m_oldAxis3Value = 0.0f;
	
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
	float value = event->value();
	
	if (axis == 2)
	{
		if (value > 0)
		{
			if (m_oldAxis2Value < 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVL, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVR, true, 0.0};
		}
		else if (value == 0)
		{
			if (m_oldAxis2Value < 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVL, false, 0.0};}
			else if (m_oldAxis2Value > 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVR, false, 0.0};}
		}
		else
		{
			if (m_oldAxis2Value > 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVR, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVL, true, 0.0};
		}
		m_oldAxis2Value = value;
	}
	else if (axis == 3)
	{
		if (value > 0)
		{
			if (m_oldAxis3Value < 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVD, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVU, true, 0.0};
		}
		else if (value == 0)
		{
			if (m_oldAxis3Value < 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVD, false, 0.0};}
			else if (m_oldAxis3Value > 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVU, false, 0.0};}
		}
		else
		{
			if (m_oldAxis3Value > 0) {m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVU, false, 0.0};}
			m_changes << JoystickChange{this,ControlType::Button, LogitechExtreme3D::POVD, true, 0.0};
		}
		m_oldAxis3Value = value;
	}
	else if (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D::JOYX, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D::JOYY, false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D::JOYZ, false, event->value()};}
	else if (axis == 5) {m_changes << JoystickChange{this, ControlType::Axis, LogitechExtreme3D::THR,  false, event->value()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString LogitechExtreme3D::description() const
{
	return "Logitech Extreme 3D";
}




// BUTTON COUNT ///////////////////////////////////////////////////////////////
uint LogitechExtreme3D::buttonCount() const
{
	return 16;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool LogitechExtreme3D::buttonPressed(uint button) const
{
	// normal buttons
	if (button < 12)
	{
		return this->RealJoystick::buttonPressed(button);
	}
	// POV virtual buttons
	else if (button < 16)
	{
		float h = this->RealJoystick::axisValue(2);
		float v = this->RealJoystick::axisValue(3);
		if (button == LogitechExtreme3D::POVU) {return (h == 0 && v >  0);}
		if (button == LogitechExtreme3D::POVR) {return (h >  0 && v == 0);}
		if (button == LogitechExtreme3D::POVD) {return (h == 0 && v <  0);}
		if (button == LogitechExtreme3D::POVL) {return (h <  0 && v == 0);}
	}
	
	return false;
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





// AXIS COUNT /////////////////////////////////////////////////////////////////
uint LogitechExtreme3D::axisCount() const
{
	return 4;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float LogitechExtreme3D::axisValue(uint axis) const
{
	if (axis == LogitechExtreme3D::JOYX) {return this->RealJoystick::axisValue(1);}
	if (axis == LogitechExtreme3D::JOYY) {return this->RealJoystick::axisValue(0);}
	if (axis == LogitechExtreme3D::JOYZ) {return this->RealJoystick::axisValue(4);}
	if (axis == LogitechExtreme3D::THR)  {return this->RealJoystick::axisValue(5);}
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


