#include "WarthogThrottle.h"
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
WarthogThrottle::WarthogThrottle(QGameController *c) : RealJoystick{c}
{
	m_buttonsNames << "SC" << "MSP" << "MSU" << "MSR" << "MSD" << "MSL" << "SPDF" << "SPDB" << "BSF" << "BSB";
	m_buttonsNames << "CHF" << "CHB" << "PSF" << "PSB" << "LTB" << "EFLNORM" << "EFRNORM" << "EOLMOTOR" << "EORMOTOR";
	m_buttonsNames << "APUON" << "LDGH" << "FLAPU" << "FLAPD" << "EACON" << "RDRNRM" << "APENG" << "APATT" << "APALT";
	m_buttonsNames << "IDLERON" << "IDLELON" << "EOLIGN" << "EORIGN";
	
	m_buttonsNames << "CSU" << "CSR" << "CSD" << "CSL" << "EFLOVER" << "EFROVER" << "APUOFF" << "EACOFF";
	m_buttonsNames << "RDRDIS" << "APDIS" << "IDLEROFF" << "IDLELOFF" << "EOLNORM" << "EORNORM";
	m_buttonsNames << "FLAPM" << "SPDM" << "BSM" << "CHM" << "PSM" << "APAH";
	
	m_axesNames << "THR_LEFT" << "THR_RIGHT" << "THR_FC" << "SCX" << "SCY";
}





// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void WarthogThrottle::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	
	uint button = event->button();
	bool bPressed = event->pressed();
	
	if (button == WarthogThrottle::SC || 
		button == WarthogThrottle::MSP ||
		button == WarthogThrottle::MSU ||
		button == WarthogThrottle::MSR ||
		button == WarthogThrottle::MSD ||
		button == WarthogThrottle::MSL ||
		button == WarthogThrottle::LTB ||
		button == WarthogThrottle::LDGH)
	{
		m_changes << JoystickChange{this,ControlType::Button,button,bPressed,0.0};
	}
	else if (button == WarthogThrottle::SPDF)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::SPDF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::SPDM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::SPDB)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::SPDB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::SPDM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::BSF)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::BSF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::BSM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::BSB)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::BSB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::BSM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::CHF)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::CHF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::CHM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::CHB)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::CHB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::CHM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::PSF)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::PSF,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::PSM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::PSB)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::PSB,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::PSM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EFLNORM)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EFLNORM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EFLOVER,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EFRNORM)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EFRNORM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EFROVER,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EOLMOTOR)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EOLMOTOR,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EOLNORM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EORMOTOR)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EORMOTOR,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EORNORM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::APUON)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APUON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APUOFF,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::FLAPU)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::FLAPU,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::FLAPM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::FLAPD)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::FLAPD,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::FLAPM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EACON)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EACON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EACOFF,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::RDRNRM)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::RDRNRM,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::RDRDIS,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::APENG)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APENG,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APDIS,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::APATT)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APATT,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APAH,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::APALT)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APALT,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::APAH,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::IDLERON)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::IDLERON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::IDLEROFF,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::IDLELON)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::IDLELON,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::IDLELOFF,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EOLIGN)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EOLIGN,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EOLNORM,!bPressed,0.0};
	}
	else if (button == WarthogThrottle::EORIGN)
	{
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EORIGN,bPressed,0.0};
		m_changes << JoystickChange{this,ControlType::Button,WarthogThrottle::EORNORM,!bPressed,0.0};
	}
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void WarthogThrottle::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	
	uint axis = event->axis();
	if (axis == 0 || axis == 1)
	{
		float h = this->RealJoystick::axisValue(0);
		float v = this->RealJoystick::axisValue(1);
		m_changes << JoystickChange{this,ControlType::Button, WarthogThrottle::CSU, h==0 && v>0, 0.0};
		m_changes << JoystickChange{this,ControlType::Button, WarthogThrottle::CSR, h>0 && v==0, 0.0};
		m_changes << JoystickChange{this,ControlType::Button, WarthogThrottle::CSD, h==0 && v<0, 0.0};
		m_changes << JoystickChange{this,ControlType::Button, WarthogThrottle::CSL, h<0 && v==0, 0.0};
	}
	else if (axis == 2) {m_changes << JoystickChange{this,ControlType::Axis,3,false,event->value()};} // SCX axis
	else if (axis == 3) {m_changes << JoystickChange{this,ControlType::Axis,4,false,event->value()};} // SCY axis
	else if (axis == 4) {m_changes << JoystickChange{this,ControlType::Axis,2,false,event->value()};} // SLIDER axis
	else if (axis == 5) {m_changes << JoystickChange{this,ControlType::Axis,1,false,event->value()};} // THR_RIGHT axis
	else if (axis == 6) {m_changes << JoystickChange{this,ControlType::Axis,0,false,event->value()};} // THR_LEFT axis
}





// DESCRIPTION ////////////////////////////////////////////////////////////////
QString WarthogThrottle::description() const
{
	return "Throttle - HOTAS Warthog";
}




// BUTTON COUNT ///////////////////////////////////////////////////////////////
uint WarthogThrottle::buttonCount() const
{
	return 52;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool WarthogThrottle::buttonPressed(uint button) const
{
	// normal buttons
	if (button < 32)
	{
		return this->RealJoystick::buttonPressed(button);
	}
	// POV
	else if (button <= 35)
	{
		float h = this->RealJoystick::axisValue(0);
		float v = this->RealJoystick::axisValue(1);
		if (button == WarthogThrottle::CSU) {return (h == 0 && v >  0);}
		if (button == WarthogThrottle::CSR) {return (h >  0 && v == 0);}
		if (button == WarthogThrottle::CSD) {return (h == 0 && v <  0);}
		if (button == WarthogThrottle::CSL) {return (h <  0 && v == 0);}
	}
	// other virtual buttons
	else if (button == WarthogThrottle::EFLOVER)  {return !(this->RealJoystick::buttonPressed(WarthogThrottle::EFLNORM));}
	else if (button == WarthogThrottle::EFROVER)  {return !(this->RealJoystick::buttonPressed(WarthogThrottle::EFRNORM));}
	else if (button == WarthogThrottle::APUOFF)   {return !(this->RealJoystick::buttonPressed(WarthogThrottle::APUON));}
	else if (button == WarthogThrottle::EACOFF)   {return !(this->RealJoystick::buttonPressed(WarthogThrottle::EACON));}
	else if (button == WarthogThrottle::RDRDIS)   {return !(this->RealJoystick::buttonPressed(WarthogThrottle::RDRNRM));}
	else if (button == WarthogThrottle::APDIS)    {return !(this->RealJoystick::buttonPressed(WarthogThrottle::APENG));}
	else if (button == WarthogThrottle::IDLEROFF) {return !(this->RealJoystick::buttonPressed(WarthogThrottle::IDLERON));}
	else if (button == WarthogThrottle::IDLELOFF) {return !(this->RealJoystick::buttonPressed(WarthogThrottle::IDLELON));}
	else if (button == WarthogThrottle::EOLNORM)  {return !(this->RealJoystick::buttonPressed(WarthogThrottle::EOLMOTOR)) && !(this->RealJoystick::buttonPressed(WarthogThrottle::EOLIGN));}
	else if (button == WarthogThrottle::EORNORM)  {return !(this->RealJoystick::buttonPressed(WarthogThrottle::EORMOTOR)) && !(this->RealJoystick::buttonPressed(WarthogThrottle::EORIGN));}
	else if (button == WarthogThrottle::FLAPM)    {return !(this->RealJoystick::buttonPressed(WarthogThrottle::FLAPD))    && !(this->RealJoystick::buttonPressed(WarthogThrottle::FLAPD));}
	else if (button == WarthogThrottle::SPDM)     {return !(this->RealJoystick::buttonPressed(WarthogThrottle::SPDF))     && !(this->RealJoystick::buttonPressed(WarthogThrottle::SPDB));}
	else if (button == WarthogThrottle::BSM)      {return !(this->RealJoystick::buttonPressed(WarthogThrottle::BSF))      && !(this->RealJoystick::buttonPressed(WarthogThrottle::BSB));}
	else if (button == WarthogThrottle::CHM)      {return !(this->RealJoystick::buttonPressed(WarthogThrottle::CHF))      && !(this->RealJoystick::buttonPressed(WarthogThrottle::CHB));}
	else if (button == WarthogThrottle::PSM)      {return !(this->RealJoystick::buttonPressed(WarthogThrottle::PSF))      && !(this->RealJoystick::buttonPressed(WarthogThrottle::PSB));}
	else if (button == WarthogThrottle::APAH)     {return !(this->RealJoystick::buttonPressed(WarthogThrottle::APATT))    && !(this->RealJoystick::buttonPressed(WarthogThrottle::APALT));}
	
	return false;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString WarthogThrottle::buttonName(uint button) const
{
	if (button < 52)
		return m_buttonsNames[button];
	else
		return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList WarthogThrottle::buttonsNames() const
{
	return m_buttonsNames;
}





// AXIS COUNT /////////////////////////////////////////////////////////////////
uint WarthogThrottle::axisCount() const
{
	return 5;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float WarthogThrottle::axisValue(uint axis) const
{
	if (axis == WarthogThrottle::THR_LEFT)  {return this->RealJoystick::axisValue(6);}
	if (axis == WarthogThrottle::THR_RIGHT) {return this->RealJoystick::axisValue(5);}
	if (axis == WarthogThrottle::THR_FC)    {return this->RealJoystick::axisValue(4);}
	if (axis == WarthogThrottle::SCX)       {return this->RealJoystick::axisValue(2);}
	if (axis == WarthogThrottle::SCY)       {return this->RealJoystick::axisValue(3);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString WarthogThrottle::axisName(uint axis) const
{
	if (axis < 5)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList WarthogThrottle::axesNames() const
{
	return m_axesNames;
}


