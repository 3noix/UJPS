#include "MicrosoftXbox360Gamepad.h"
#include "GameController.h"
#include "Lim.h"
#include <XInput.h>
#include <windows.h>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  DESTRUCTEUR
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
//
//  SET DATA
//  FLUSH
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR/////////////////////////////////////////////////
MicrosoftXbox360Gamepad::MicrosoftXbox360Gamepad(GameController *c) : RealJoystick{c}
{
	m_leftMotorSpeed = 0;
	m_rightMotorSpeed = 0;
	m_bFirstWrite = true;
	m_dataModified = false;
	
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

MicrosoftXbox360Gamepad::~MicrosoftXbox360Gamepad()
{
	this->setData("LEFT_MOTOR_SPEED",0.0);
	this->setData("RIGHT_MOTOR_SPEED",0.0);
	this->flush();
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
		return {};
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
		return {};
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
		return {};
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXbox360Gamepad::povsNames() const
{
	return m_povsNames;
}






// SET DATA ///////////////////////////////////////////////////////////////////
void MicrosoftXbox360Gamepad::setData(const QString &str, QVariant v)
{
	if (str == "LEFT_MOTOR_SPEED") // double between 0 and 100% expected
	{
		double leftSpeed = v.toDouble();
		if (leftSpeed == m_leftMotorSpeed) {return;}
		m_leftMotorSpeed = leftSpeed;
		m_dataModified = true;
	}
	else if (str == "RIGHT_MOTOR_SPEED") // double between 0 and 100% expected
	{
		double rightSpeed = v.toDouble();
		if (rightSpeed == m_rightMotorSpeed) {return;}
		m_rightMotorSpeed = rightSpeed;
		m_dataModified = true;
	}
}

// FLUSH //////////////////////////////////////////////////////////////////////
void MicrosoftXbox360Gamepad::flush()
{
	if (!m_bFirstWrite && !m_dataModified) {return;}
	
	XINPUT_VIBRATION state;
	memset(&state,0,sizeof(XINPUT_VIBRATION));
	state.wLeftMotorSpeed = lim<double>(655.35*m_leftMotorSpeed,0.0,65535.0);
	state.wRightMotorSpeed = lim<double>(655.35*m_rightMotorSpeed,0.0,65535.0);
	XInputSetState(this->id()-100,&state);
	
	m_bFirstWrite = false;
	m_dataModified = false;
}

