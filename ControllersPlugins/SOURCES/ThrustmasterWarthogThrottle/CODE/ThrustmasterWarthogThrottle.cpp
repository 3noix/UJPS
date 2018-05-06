#include "ThrustmasterWarthogThrottle.h"
#include "qgamecontroller.h"
#include "Lim.h"
#include "HidDevice.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  SLOT GAME CONTROLLER BUTTON EVENT
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
//  SET DATA
//  FLUSH
//  BIT CHAR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
ThrustmasterWarthogThrottle::ThrustmasterWarthogThrottle(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "SC" << "MSP" << "MSU" << "MSR" << "MSD" << "MSL" << "SPDF" << "SPDB" << "BSF" << "BSB";
	m_buttonsNames << "CHF" << "CHB" << "PSF" << "PSB" << "LTB" << "EFLNORM" << "EFRNORM" << "EOLMOTOR" << "EORMOTOR";
	m_buttonsNames << "APUON" << "LDGH" << "FLAPU" << "FLAPD" << "EACON" << "RDRNRM" << "APENG" << "APATT" << "APALT";
	m_buttonsNames << "IDLERON" << "IDLELON" << "EOLIGN" << "EORIGN";
	
	m_buttonsNames << "CSU" << "CSR" << "CSD" << "CSL" << "EFLOVER" << "EFROVER" << "APUOFF" << "EACOFF";
	m_buttonsNames << "RDRDIS" << "APDIS" << "IDLEROFF" << "IDLELOFF" << "EOLNORM" << "EORNORM";
	m_buttonsNames << "FLAPM" << "SPDM" << "BSM" << "CHM" << "PSM" << "APAH";
	
	m_axesNames << "THR_LEFT" << "THR_RIGHT" << "THR_FC" << "SCX" << "SCY";
	
	m_oldAxis0Value = 0.0f;
	m_oldAxis1Value = 0.0f;
	
	// led support
	m_outputData[0] = 1;
	m_outputData[1] = 6;
	m_outputData[2] = 0;
	m_outputData[3] = 0;
	m_dataModified = false;
	m_bLed1 = false;
	m_bLed2 = false;
	m_bLed3 = false;
	m_bLed4 = false;
	m_bLed5 = false;
	m_bBackLit = false;
	m_brightness = 0;
	// initialize all shut down
	m_hidDevice = new HidDevice(0x044F,0x0404);
	m_hidDevice->openHidDevice();
	//m_hidDevice->writeData(m_outputData,4);
}

// DESTRUCTEUR ////////////////////////////////////////////////////////////////
ThrustmasterWarthogThrottle::~ThrustmasterWarthogThrottle()
{
	if (m_hidDevice)
		delete m_hidDevice;
}





// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void ThrustmasterWarthogThrottle::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	
	uint button = event->button();
	bool bPressed = event->pressed();
	
	if (button == ThrustmasterWarthogThrottle::SC || 
		button == ThrustmasterWarthogThrottle::MSP ||
		button == ThrustmasterWarthogThrottle::MSU ||
		button == ThrustmasterWarthogThrottle::MSR ||
		button == ThrustmasterWarthogThrottle::MSD ||
		button == ThrustmasterWarthogThrottle::MSL ||
		button == ThrustmasterWarthogThrottle::LTB ||
		button == ThrustmasterWarthogThrottle::LDGH ||
		button == ThrustmasterWarthogThrottle::CSU ||
		button == ThrustmasterWarthogThrottle::CSR ||
		button == ThrustmasterWarthogThrottle::CSD ||
		button == ThrustmasterWarthogThrottle::CSL)
	{
		m_changes << JoystickChange{this,ControlType::Button,button,bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::SPDF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::SPDF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::SPDM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::SPDB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::SPDB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::SPDM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::BSF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::BSF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::BSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::BSB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::BSB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::BSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::CHF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::CHF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::CHM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::CHB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::CHB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::CHM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::PSF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::PSF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::PSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::PSB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::PSB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::PSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EFLNORM)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EFLNORM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EFLOVER,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EFRNORM)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EFRNORM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EFROVER,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EOLMOTOR)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EOLMOTOR,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EOLNORM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EORMOTOR)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EORMOTOR,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EORNORM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::APUON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APUON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APUOFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::FLAPU)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::FLAPU,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::FLAPM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::FLAPD)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::FLAPD,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::FLAPM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EACON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EACON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EACOFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::RDRNRM)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::RDRNRM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::RDRDIS,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::APENG)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APENG,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APDIS,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::APATT)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APATT,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APAH,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::APALT)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APALT,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::APAH,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::IDLERON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::IDLERON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::IDLEROFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::IDLELON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::IDLELON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::IDLELOFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EOLIGN)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EOLIGN,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EOLNORM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle::EORIGN)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EORIGN,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle::EORNORM,!bPressed,0.0};
	}
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterWarthogThrottle::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 0)      {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle::SCX,       false, event->value()};}
	else if (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle::SCY,       false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle::THR_FC,    false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle::THR_RIGHT, false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle::THR_LEFT,  false, event->value()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogThrottle::description() const
{
	return "Throttle - HOTAS Warthog";
}




// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint ThrustmasterWarthogThrottle::buttonsCount() const
{
	return 52;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool ThrustmasterWarthogThrottle::buttonPressed(uint button) const
{
	// normal buttons and POV virtual buttons
	if (button < 36)
	{
		return this->RealJoystick::buttonPressed(button);
	}
	// other virtual buttons
	else if (button == ThrustmasterWarthogThrottle::EFLOVER)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EFLNORM));}
	else if (button == ThrustmasterWarthogThrottle::EFROVER)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EFRNORM));}
	else if (button == ThrustmasterWarthogThrottle::APUOFF)   {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::APUON));}
	else if (button == ThrustmasterWarthogThrottle::EACOFF)   {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EACON));}
	else if (button == ThrustmasterWarthogThrottle::RDRDIS)   {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::RDRNRM));}
	else if (button == ThrustmasterWarthogThrottle::APDIS)    {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::APENG));}
	else if (button == ThrustmasterWarthogThrottle::IDLEROFF) {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::IDLERON));}
	else if (button == ThrustmasterWarthogThrottle::IDLELOFF) {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::IDLELON));}
	else if (button == ThrustmasterWarthogThrottle::EOLNORM)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EOLMOTOR)) && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EOLIGN));}
	else if (button == ThrustmasterWarthogThrottle::EORNORM)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EORMOTOR)) && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::EORIGN));}
	else if (button == ThrustmasterWarthogThrottle::FLAPM)    {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::FLAPD))    && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::FLAPD));}
	else if (button == ThrustmasterWarthogThrottle::SPDM)     {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::SPDF))     && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::SPDB));}
	else if (button == ThrustmasterWarthogThrottle::BSM)      {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::BSF))      && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::BSB));}
	else if (button == ThrustmasterWarthogThrottle::CHM)      {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::CHF))      && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::CHB));}
	else if (button == ThrustmasterWarthogThrottle::PSM)      {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::PSF))      && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::PSB));}
	else if (button == ThrustmasterWarthogThrottle::APAH)     {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::APATT))    && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle::APALT));}
	
	return false;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogThrottle::buttonName(uint button) const
{
	if (button < 52)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogThrottle::buttonsNames() const
{
	return m_buttonsNames;
}





// AXES COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterWarthogThrottle::axesCount() const
{
	return 5;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float ThrustmasterWarthogThrottle::axisValue(uint axis) const
{
	if (axis == ThrustmasterWarthogThrottle::THR_LEFT)  {return this->RealJoystick::axisValue(4);}
	if (axis == ThrustmasterWarthogThrottle::THR_RIGHT) {return this->RealJoystick::axisValue(3);}
	if (axis == ThrustmasterWarthogThrottle::THR_FC)    {return this->RealJoystick::axisValue(2);}
	if (axis == ThrustmasterWarthogThrottle::SCX)       {return this->RealJoystick::axisValue(0);}
	if (axis == ThrustmasterWarthogThrottle::SCY)       {return this->RealJoystick::axisValue(1);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogThrottle::axisName(uint axis) const
{
	if (axis < 5)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogThrottle::axesNames() const
{
	return m_axesNames;
}






// SET DATA ///////////////////////////////////////////////////////////////////
void ThrustmasterWarthogThrottle::setData(const QString &str, QVariant v)
{
	if (str == "BRIGHTNESS")
	{
		int i = v.toInt();
		quint8 j = lim<int>(i,0,5);
		if (j == m_brightness) {return;}
		m_brightness = j;
		m_dataModified = true;
		m_outputData[3] = m_brightness;
	}
	else if (str == "BACKLIT")
	{
		bool bBacklit = v.toBool();
		if (bBacklit == m_bBackLit) {return;}
		m_bBackLit = bBacklit;
		m_dataModified = true;
		
		if (m_bBackLit)
			m_outputData[2] |= bitChar(3);
		else
			m_outputData[2] &= ~bitChar(3);
	}
	else if (str == "LED1")
	{
		bool bLed1 = v.toBool();
		if (bLed1 == m_bLed1) {return;}
		m_bLed1 = bLed1;
		m_dataModified = true;
		
		if (m_bLed1)
			m_outputData[2] |= bitChar(6);
		else
			m_outputData[2] &= ~bitChar(6);
	}
	else if (str == "LED2")
	{
		bool bLed2 = v.toBool();
		if (bLed2 == m_bLed2) {return;}
		m_bLed2 = bLed2;
		m_dataModified = true;
		
		if (m_bLed2)
			m_outputData[2] |= bitChar(0);
		else
			m_outputData[2] &= ~bitChar(0);
	}
	else if (str == "LED3")
	{
		bool bLed3 = v.toBool();
		if (bLed3 == m_bLed3) {return;}
		m_bLed3 = bLed3;
		m_dataModified = true;
		
		if (m_bLed3)
			m_outputData[2] |= bitChar(4);
		else
			m_outputData[2] &= ~bitChar(4);
	}
	else if (str == "LED4")
	{
		bool bLed4 = v.toBool();
		if (bLed4 == m_bLed4) {return;}
		m_bLed4 = bLed4;
		m_dataModified = true;
		
		if (m_bLed4)
			m_outputData[2] |= bitChar(1);
		else
			m_outputData[2] &= ~bitChar(1);
	}
	else if (str == "LED5")
	{
		bool bLed5 = v.toBool();
		if (bLed5 == m_bLed5) {return;}
		m_bLed5 = bLed5;
		m_dataModified = true;
		
		if (m_bLed5)
			m_outputData[2] |= bitChar(2);
		else
			m_outputData[2] &= ~bitChar(2);
	}
}

// FLUSH //////////////////////////////////////////////////////////////////////
void ThrustmasterWarthogThrottle::flush()
{
	if (!m_dataModified) {return;}
	m_hidDevice->writeData(m_outputData,4);
	m_dataModified = false;
}

// BIT CHAR ///////////////////////////////////////////////////////////////////
quint8 ThrustmasterWarthogThrottle::bitChar(uint i)
{
	quint8 one = 1;
	return (one << i%8);
}



