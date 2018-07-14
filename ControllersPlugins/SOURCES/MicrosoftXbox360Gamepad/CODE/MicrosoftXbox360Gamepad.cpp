#include "MicrosoftXbox360Gamepad.h"
#include "GameController.h"
#include "GameControllerEvents.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  DESCRIPTION
//
//  BUTTONS COUNT
//  BUTTON PRESSED
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXES COUNT
//  AXIS NAME
//  AXES NAMES
//
//  POVS COUNT
//  POV NAME
//  POVS NAMES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MicrosoftXbox360Gamepad::MicrosoftXbox360Gamepad(GameController *c) : RealJoystick{c}
{
	m_buttonsNames << "DPADU" << "DPADR" << "DPADD" << "DPADL";
	m_buttonsNames << "START" << "BACK" << "THUMBL" << "THUMBR" << "SHOULDERL" << "SHOULDERR";
	m_buttonsNames << "BA" << "BB" << "BX" << "BY";
	
	m_axesNames << "TRIGGERL" << "TRIGGERR" << "THUMBLX" << "THUMBLY" << "THUMBRX" << "THUMBRY";
	
	m_povsNames << "DPAD";
	
	this->addVirtualPov(MicrosoftXbox360Gamepad_::DPADU,
						MicrosoftXbox360Gamepad_::DPADR,
						MicrosoftXbox360Gamepad_::DPADD,
						MicrosoftXbox360Gamepad_::DPADL,
						"DPAD");
}




// DESCRIPTION ////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Gamepad::description() const
{
	return MicrosoftXbox360Gamepad_::Description;
}





// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint MicrosoftXbox360Gamepad::buttonsCount() const
{
	return 14;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Gamepad::buttonName(uint button) const
{
	if (button < 14)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Gamepad::buttonsNames() const
{
	return m_buttonsNames;
}




// AXES COUNT /////////////////////////////////////////////////////////////////
uint MicrosoftXbox360Gamepad::axesCount() const
{
	return 6;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Gamepad::axisName(uint axis) const
{
	if (axis < 6)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Gamepad::axesNames() const
{
	return m_axesNames;
}




// POVS COUNT /////////////////////////////////////////////////////////////////
uint MicrosoftXbox360Gamepad::povsCount() const
{
	return 1;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString MicrosoftXbox360Gamepad::povName(uint pov) const
{
	if (pov < 1)
		return m_povsNames[pov];
	else
		return QString();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Gamepad::povsNames() const
{
	return m_povsNames;
}

