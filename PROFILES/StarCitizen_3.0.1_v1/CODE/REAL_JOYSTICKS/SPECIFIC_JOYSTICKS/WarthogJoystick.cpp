#include "WarthogJoystick.h"
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
WarthogJoystick::WarthogJoystick(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "TG1" << "S2" << "S3" << "S4" << "S1" << "TG2" << "H2U" << "H2R" << "H2D" << "H2L";
	m_buttonsNames << "H3U" << "H3R" << "H3D" << "H3L" << "H4U" << "H4R" << "H4D" << "H4L";
	m_buttonsNames << "H1U" << "H1R" << "H1D" << "H1L";
	m_axesNames << "JOYX" << "JOYY";
}


// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void WarthogJoystick::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Button,event->button(),event->pressed(),0.0};
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void WarthogJoystick::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	
	uint axis = event->axis();
	if (axis == 0 || axis == 1)
	{
		float h = this->RealJoystick::axisValue(0);
		float v = this->RealJoystick::axisValue(1);
		m_changes << JoystickChange{this,ControlType::Button, WarthogJoystick::H1U, h==0 && v>0, 0.0};
		m_changes << JoystickChange{this,ControlType::Button, WarthogJoystick::H1R, h>0 && v==0, 0.0};
		m_changes << JoystickChange{this,ControlType::Button, WarthogJoystick::H1D, h==0 && v<0, 0.0};
		m_changes << JoystickChange{this,ControlType::Button, WarthogJoystick::H1L, h<0 && v==0, 0.0};
	}
	else if (axis == 2) {m_changes << JoystickChange{this,ControlType::Axis,1,false,event->value()};} // Y-axis
	else if (axis == 3) {m_changes << JoystickChange{this,ControlType::Axis,0,false,event->value()};} // X-axis
}




// DESCRIPTION ////////////////////////////////////////////////////////////////
QString WarthogJoystick::description() const
{
	return "Joystick - HOTAS Warthog";
}





// BUTTON COUNT ///////////////////////////////////////////////////////////////
uint WarthogJoystick::buttonCount() const
{
	return 23;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool WarthogJoystick::buttonPressed(uint button) const
{
	if (button < 19)
	{
		return this->RealJoystick::buttonPressed(button);
	}
	else if (button < 23)
	{
		float h = this->RealJoystick::axisValue(0);
		float v = this->RealJoystick::axisValue(1);
		if (button == WarthogJoystick::H1U) {return (h == 0 && v >  0);}
		if (button == WarthogJoystick::H1R) {return (h >  0 && v == 0);}
		if (button == WarthogJoystick::H1D) {return (h == 0 && v <  0);}
		if (button == WarthogJoystick::H1L) {return (h <  0 && v == 0);}
	}
	
	return false;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString WarthogJoystick::buttonName(uint button) const
{
	if (button < 23)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList WarthogJoystick::buttonsNames() const
{
	return m_buttonsNames;
}




// AXIS COUNT /////////////////////////////////////////////////////////////////
uint WarthogJoystick::axisCount() const
{
	return 2;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float WarthogJoystick::axisValue(uint axis) const
{
	if (axis == WarthogJoystick::JOYX) {return this->RealJoystick::axisValue(3);}
	if (axis == WarthogJoystick::JOYY) {return this->RealJoystick::axisValue(2);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString WarthogJoystick::axisName(uint axis) const
{
	if (axis < 2)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList WarthogJoystick::axesNames() const
{
	return m_axesNames;
}

