#include "ThrustmasterWarthogThrottle.h"
#include "qgamecontroller.h"
#include "Lim.h"
#include "WriteToHidThread.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
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
//  POVS COUNT
//  POV NAME
//  POVS NAMES
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
	
	m_povsNames << "CS" << "MS";
	
	this->addVirtualPov(ThrustmasterWarthogThrottle_::MSU,
						ThrustmasterWarthogThrottle_::MSR,
						ThrustmasterWarthogThrottle_::MSD,
						ThrustmasterWarthogThrottle_::MSL,
						"MS");
	
	// led support
	m_thread = new WriteToHidThread(this);
	m_flags = 0;
	m_brightness = 0;
	m_dataModified = false;
	m_bLed1 = false;
	m_bLed2 = false;
	m_bLed3 = false;
	m_bLed4 = false;
	m_bLed5 = false;
	m_bBackLit = false;
}





// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void ThrustmasterWarthogThrottle::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	
	uint button = event->button();
	bool bPressed = event->pressed();
	
	if (button == ThrustmasterWarthogThrottle_::SC || 
		button == ThrustmasterWarthogThrottle_::MSP ||
		button == ThrustmasterWarthogThrottle_::MSU ||
		button == ThrustmasterWarthogThrottle_::MSR ||
		button == ThrustmasterWarthogThrottle_::MSD ||
		button == ThrustmasterWarthogThrottle_::MSL ||
		button == ThrustmasterWarthogThrottle_::LTB ||
		button == ThrustmasterWarthogThrottle_::LDGH ||
		button == ThrustmasterWarthogThrottle_::CSU ||
		button == ThrustmasterWarthogThrottle_::CSR ||
		button == ThrustmasterWarthogThrottle_::CSD ||
		button == ThrustmasterWarthogThrottle_::CSL)
	{
		m_changes << JoystickChange{this,ControlType::Button,button,bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::SPDF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::SPDF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::SPDM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::SPDB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::SPDB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::SPDM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::BSF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::BSF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::BSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::BSB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::BSB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::BSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::CHF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::CHF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::CHM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::CHB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::CHB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::CHM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::PSF)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::PSF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::PSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::PSB)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::PSB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::PSM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EFLNORM)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EFLNORM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EFLOVER,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EFRNORM)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EFRNORM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EFROVER,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EOLMOTOR)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EOLMOTOR,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EOLNORM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EORMOTOR)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EORMOTOR,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EORNORM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::APUON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APUON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APUOFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::FLAPU)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::FLAPU,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::FLAPM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::FLAPD)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::FLAPD,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::FLAPM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EACON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EACON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EACOFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::RDRNRM)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::RDRNRM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::RDRDIS,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::APENG)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APENG,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APDIS,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::APATT)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APATT,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APAH,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::APALT)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APALT,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::APAH,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::IDLERON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::IDLERON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::IDLEROFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::IDLELON)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::IDLELON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::IDLELOFF,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EOLIGN)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EOLIGN,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EOLNORM,!bPressed,0.0};
	}
	else if (button == ThrustmasterWarthogThrottle_::EORIGN)
	{
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EORIGN,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,ThrustmasterWarthogThrottle_::EORNORM,!bPressed,0.0};
	}
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void ThrustmasterWarthogThrottle::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	uint axis = event->axis();
	
	if (axis == 0)      {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle_::SCX,       false, event->value()};}
	else if (axis == 1) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle_::SCY,       false, event->value()};}
	else if (axis == 2) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle_::THR_FC,    false, event->value()};}
	else if (axis == 3) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle_::THR_RIGHT, false, event->value()};}
	else if (axis == 4) {m_changes << JoystickChange{this, ControlType::Axis, ThrustmasterWarthogThrottle_::THR_LEFT,  false, event->value()};}
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogThrottle::description() const
{
	return ThrustmasterWarthogThrottle_::Description;
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
	else if (button == ThrustmasterWarthogThrottle_::EFLOVER)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EFLNORM));}
	else if (button == ThrustmasterWarthogThrottle_::EFROVER)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EFRNORM));}
	else if (button == ThrustmasterWarthogThrottle_::APUOFF)   {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::APUON));}
	else if (button == ThrustmasterWarthogThrottle_::EACOFF)   {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EACON));}
	else if (button == ThrustmasterWarthogThrottle_::RDRDIS)   {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::RDRNRM));}
	else if (button == ThrustmasterWarthogThrottle_::APDIS)    {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::APENG));}
	else if (button == ThrustmasterWarthogThrottle_::IDLEROFF) {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::IDLERON));}
	else if (button == ThrustmasterWarthogThrottle_::IDLELOFF) {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::IDLELON));}
	else if (button == ThrustmasterWarthogThrottle_::EOLNORM)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EOLMOTOR)) && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EOLIGN));}
	else if (button == ThrustmasterWarthogThrottle_::EORNORM)  {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EORMOTOR)) && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::EORIGN));}
	else if (button == ThrustmasterWarthogThrottle_::FLAPM)    {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::FLAPD))    && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::FLAPD));}
	else if (button == ThrustmasterWarthogThrottle_::SPDM)     {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::SPDF))     && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::SPDB));}
	else if (button == ThrustmasterWarthogThrottle_::BSM)      {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::BSF))      && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::BSB));}
	else if (button == ThrustmasterWarthogThrottle_::CHM)      {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::CHF))      && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::CHB));}
	else if (button == ThrustmasterWarthogThrottle_::PSM)      {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::PSF))      && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::PSB));}
	else if (button == ThrustmasterWarthogThrottle_::APAH)     {return !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::APATT))    && !(this->RealJoystick::buttonPressed(ThrustmasterWarthogThrottle_::APALT));}
	
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
	if (axis == ThrustmasterWarthogThrottle_::THR_LEFT)  {return this->RealJoystick::axisValue(4);}
	if (axis == ThrustmasterWarthogThrottle_::THR_RIGHT) {return this->RealJoystick::axisValue(3);}
	if (axis == ThrustmasterWarthogThrottle_::THR_FC)    {return this->RealJoystick::axisValue(2);}
	if (axis == ThrustmasterWarthogThrottle_::SCX)       {return this->RealJoystick::axisValue(0);}
	if (axis == ThrustmasterWarthogThrottle_::SCY)       {return this->RealJoystick::axisValue(1);}
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




// POVS COUNT /////////////////////////////////////////////////////////////////
uint ThrustmasterWarthogThrottle::povsCount() const
{
	return 2;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString ThrustmasterWarthogThrottle::povName(uint pov) const
{
	if (pov < 2)
		return m_povsNames[pov];
	else
		return QString();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList ThrustmasterWarthogThrottle::povsNames() const
{
	return m_povsNames;
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
	}
	else if (str == "BACKLIT")
	{
		bool bBacklit = v.toBool();
		if (bBacklit == m_bBackLit) {return;}
		m_bBackLit = bBacklit;
		m_dataModified = true;
		
		if (m_bBackLit)
			m_flags |= bitChar(3);
		else
			m_flags &= ~bitChar(3);
	}
	else if (str == "LED1")
	{
		bool bLed1 = v.toBool();
		if (bLed1 == m_bLed1) {return;}
		m_bLed1 = bLed1;
		m_dataModified = true;
		
		if (m_bLed1)
			m_flags |= bitChar(6);
		else
			m_flags &= ~bitChar(6);
	}
	else if (str == "LED2")
	{
		bool bLed2 = v.toBool();
		if (bLed2 == m_bLed2) {return;}
		m_bLed2 = bLed2;
		m_dataModified = true;
		
		if (m_bLed2)
			m_flags |= bitChar(0);
		else
			m_flags &= ~bitChar(0);
	}
	else if (str == "LED3")
	{
		bool bLed3 = v.toBool();
		if (bLed3 == m_bLed3) {return;}
		m_bLed3 = bLed3;
		m_dataModified = true;
		
		if (m_bLed3)
			m_flags |= bitChar(4);
		else
			m_flags &= ~bitChar(4);
	}
	else if (str == "LED4")
	{
		bool bLed4 = v.toBool();
		if (bLed4 == m_bLed4) {return;}
		m_bLed4 = bLed4;
		m_dataModified = true;
		
		if (m_bLed4)
			m_flags |= bitChar(1);
		else
			m_flags &= ~bitChar(1);
	}
	else if (str == "LED5")
	{
		bool bLed5 = v.toBool();
		if (bLed5 == m_bLed5) {return;}
		m_bLed5 = bLed5;
		m_dataModified = true;
		
		if (m_bLed5)
			m_flags |= bitChar(2);
		else
			m_flags &= ~bitChar(2);
	}
}

// FLUSH //////////////////////////////////////////////////////////////////////
void ThrustmasterWarthogThrottle::flush()
{
	if (!m_dataModified) {return;}
	m_thread->launchWriteData(m_flags,m_brightness);
	m_dataModified = false;
}

// BIT CHAR ///////////////////////////////////////////////////////////////////
quint8 ThrustmasterWarthogThrottle::bitChar(uint i)
{
	quint8 one = 1;
	return (one << i%8);
}



