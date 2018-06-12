#include "MicrosoftXbox360Controller.h"
#include "qgamecontroller.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
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
//
//  POVS COUNT
//  POV NAME
//  POVS NAMES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MicrosoftXbox360Controller::MicrosoftXbox360Controller(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "BA" << "BB" << "BX" << "BY";
	m_buttonsNames << "SHOULDERL" << "SHOULDERR" << "BACK" << "START" << "THUMBL" << "THUMBR";
	m_buttonsNames << "DPADU" << "DPADR" << "DPADD" << "DPADL";
	
	m_axesNames << "THUMBLX" << "THUMBLY" << "THUMBRX" << "THUMBRY" << "TRIGGER";
	
	m_povsNames << "DPAD";
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void MicrosoftXbox360Controller::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 1)      {m_changes << JoystickChange{this, ControlType::Axis, MicrosoftXbox360Controller_::THUMBLX, false, event->value()};}
	else if (axis == 0) {m_changes << JoystickChange{this, ControlType::Axis, MicrosoftXbox360Controller_::THUMBLY, false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, MicrosoftXbox360Controller_::THUMBRX, false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, MicrosoftXbox360Controller_::THUMBRY, false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, MicrosoftXbox360Controller_::TRIGGER, false, event->value()};}
}




// DESCRIPTION ////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Controller::description() const
{
	return MicrosoftXbox360Controller_::Description;
}





// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint MicrosoftXbox360Controller::buttonsCount() const
{
	return 14;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Controller::buttonName(uint button) const
{
	if (button < 14)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Controller::buttonsNames() const
{
	return m_buttonsNames;
}




// AXES COUNT /////////////////////////////////////////////////////////////////
uint MicrosoftXbox360Controller::axesCount() const
{
	return 5;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float MicrosoftXbox360Controller::axisValue(uint axis) const
{
	if (axis == MicrosoftXbox360Controller_::THUMBLX) {return this->RealJoystick::axisValue(1);}
	if (axis == MicrosoftXbox360Controller_::THUMBLY) {return this->RealJoystick::axisValue(0);}
	if (axis == MicrosoftXbox360Controller_::THUMBRX) {return this->RealJoystick::axisValue(3);}
	if (axis == MicrosoftXbox360Controller_::THUMBRY) {return this->RealJoystick::axisValue(2);}
	if (axis == MicrosoftXbox360Controller_::TRIGGER) {return this->RealJoystick::axisValue(4);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Controller::axisName(uint axis) const
{
	if (axis < 5)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Controller::axesNames() const
{
	return m_axesNames;
}




// POVS COUNT /////////////////////////////////////////////////////////////////
uint MicrosoftXbox360Controller::povsCount() const
{
	return 1;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Controller::povName(uint pov) const
{
	if (pov < 1)
		return m_povsNames[pov];
	else
		return QString();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Controller::povsNames() const
{
	return m_povsNames;
}

