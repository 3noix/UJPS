#include "MicrosoftXboxController.h"
#include "QtGameControllerModif/GameController.h"
#include "Other/Lim.h"
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
MicrosoftXboxController::MicrosoftXboxController(GameController *c) : RealJoystick{c}
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
	
	this->addVirtualPov(MicrosoftXboxController_::DPADU,
						MicrosoftXboxController_::DPADR,
						MicrosoftXboxController_::DPADD,
						MicrosoftXboxController_::DPADL,
						"DPAD");
}

MicrosoftXboxController::~MicrosoftXboxController()
{
	this->setData("LEFT_MOTOR_SPEED",0.0);
	this->setData("RIGHT_MOTOR_SPEED",0.0);
	this->flush();
}






// DESCRIPTION ////////////////////////////////////////////////////////////////
QString MicrosoftXboxController::description() const
{
	return MicrosoftXboxController_::Description;
}






// BUTTONS COUNT ///////////////////////////////////////////////////////////////
uint MicrosoftXboxController::buttonsCount() const
{
	return 14;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString MicrosoftXboxController::buttonName(uint button) const
{
	if (button < 14)
		return m_buttonsNames[button];
	else
		return {};
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList MicrosoftXboxController::buttonsNames() const
{
	return m_buttonsNames;
}






// AXES COUNT /////////////////////////////////////////////////////////////////
uint MicrosoftXboxController::axesCount() const
{
	return 6;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString MicrosoftXboxController::axisName(uint axis) const
{
	if (axis < 6)
		return m_axesNames[axis];
	else
		return {};
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXboxController::axesNames() const
{
	return m_axesNames;
}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint MicrosoftXboxController::povsCount() const
{
	return 1;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString MicrosoftXboxController::povName(uint pov) const
{
	if (pov < 1)
		return m_povsNames[pov];
	else
		return {};
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList MicrosoftXboxController::povsNames() const
{
	return m_povsNames;
}






// SET DATA ///////////////////////////////////////////////////////////////////
void MicrosoftXboxController::setData(const QString &str, QVariant v)
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
void MicrosoftXboxController::flush()
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

