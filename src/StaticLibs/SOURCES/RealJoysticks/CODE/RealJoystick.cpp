#include "RealJoystick.h"
#include "GameController.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  ID
//  DESCRIPTION
//  HARDWARE ID
//  READ GAME CONTROLLER
//  CHANGES
//
//  SLOT GAME CONTROLLER AXIS EVENT
//  SLOT GAME CONTROLLER BUTTON EVENT
//  SLOT GAME CONTROLLER POV EVENT
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
//  POV VALUE
//  POV NAME
//  POVS NAMES
//
//  SET DATA
//  FLUSH
//
//  ADD VIRTUAL POV
//  BUTTONS TO POV
//  BUTTON MAPS POV
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
RealJoystick::RealJoystick(GameController *c) : QObject{}, AbstractRealJoystick{}
{
	Q_ASSERT(c);
	m_controller = c;
	m_controller->readGameController();
	
	QObject::connect(c, SIGNAL(gameControllerAxisEvent(GameControllerAxisEvent)),     this, SLOT(slotGameControllerAxisEvent(GameControllerAxisEvent)));
	QObject::connect(c, SIGNAL(gameControllerButtonEvent(GameControllerButtonEvent)), this, SLOT(slotGameControllerButtonEvent(GameControllerButtonEvent)));
	QObject::connect(c, SIGNAL(gameControllerPovEvent(GameControllerPovEvent)),       this, SLOT(slotGameControllerPovEvent(GameControllerPovEvent)));
	
	m_bTransformPovInto4Buttons = (m_controller->description() != "vJoy Device");
	m_bTransform4ButtonsIntoPov = (m_controller->description() != "vJoy Device");
	if (m_bTransformPovInto4Buttons) {m_realPovsAngles = QVector<float>(m_controller->povsCount(),-1.0f);}
}

RealJoystick::~RealJoystick()
{
	if (m_controller)
	{
		delete m_controller;
		m_controller = nullptr;
	}
}






// ID /////////////////////////////////////////////////////////////////////////
uint RealJoystick::id() const
{
	return m_controller->id();
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString RealJoystick::description() const
{
	return m_controller->description();
}

// HARDWARE ID ////////////////////////////////////////////////////////////////
QString RealJoystick::hardwareId() const
{
	return m_controller->hardwareId();
}

// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void RealJoystick::readGameController()
{
	m_changes.clear();
	m_controller->readGameController();
}

// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> RealJoystick::changes()
{
	if (!m_bTransform4ButtonsIntoPov || m_virtualPovsDef.size() == 0) {return m_changes;}
	
	// we add virtual pov events to the changes
	// first we make the list of impacted povs
	QVector<uint> povsImpacted;
	for (const JoystickChange &ch : m_changes)
	{
		if (ch.type == ControlType::Button)
		{
			uint index = this->buttonMapsPov(ch.numButtonAxisPov);
			if (index != -1u && !povsImpacted.contains(index)) {povsImpacted << index;}
		}
	}
	std::sort(povsImpacted.begin(),povsImpacted.end());
	
	// we create one change per impacted pov
	for (uint index : povsImpacted)
	{
		const VirtualPovDefinition &vpd = m_virtualPovsDef[index];
		bool bUp    = m_controller->buttonValue(vpd.buttonUp);
		bool bRight = m_controller->buttonValue(vpd.buttonRight);
		bool bDown  = m_controller->buttonValue(vpd.buttonDown);
		bool bLeft  = m_controller->buttonValue(vpd.buttonLeft);
		
		float f = RealJoystick::buttonsToPov(bUp,bRight,bDown,bLeft);
		uint pov = m_controller->povsCount() + index;
		m_changes << JoystickChange{this,ControlType::Pov,pov,false,f};
	}
	
	// end
	return m_changes;
}






// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void RealJoystick::slotGameControllerAxisEvent(GameControllerAxisEvent event)
{
	m_changes << JoystickChange{this,ControlType::Axis,event.axis,false,event.value};
	// for axes we do things simple!
}

// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void RealJoystick::slotGameControllerButtonEvent(GameControllerButtonEvent event)
{
	m_changes << JoystickChange{this,ControlType::Button,event.button,event.pressed,0.0};
	
	// if the button is a part of a virtual pov, we cannot compute the new virtual pov position now,
	// as another button of this virtual pov may not have reported his new position yet. That is
	// why the computation is done "at the end", i.e. in RealJoystick::changes
}

// SLOT GAME CONTROLLER POV EVENT /////////////////////////////////////////////
void RealJoystick::slotGameControllerPovEvent(GameControllerPovEvent event)
{
	m_changes << JoystickChange{this,ControlType::Pov,event.pov,false,event.angle};
	if (!m_bTransformPovInto4Buttons) {return;}
	
	// now, using the new pov value, we determine the value of the 4 virtual buttons
	uint pov = event.pov;
	float angle = event.angle;
	float oldAngle = m_realPovsAngles[pov];
	m_realPovsAngles[pov] = angle;
	
	bool bCenter = (angle == -1.0f);
	bool bUp     = (!bCenter && (angle < 60.0f  || angle > 300.0f));
	bool bRight  = (!bCenter && angle > 30.0f  && angle < 150.0f);
	bool bDown   = (!bCenter && angle > 120.0f && angle < 240.0f);
	bool bLeft   = (!bCenter && angle > 210.0f && angle < 330.0f);
	
	bool bWasCenter = (oldAngle == -1.0f);
	bool bWasUp     = (!bWasCenter && (oldAngle < 60.0f  || oldAngle > 300.0f));
	bool bWasRight  = (!bWasCenter && oldAngle > 30.0f  && oldAngle < 150.0f);
	bool bWasDown   = (!bWasCenter && oldAngle > 120.0f && oldAngle < 240.0f);
	bool bWasLeft   = (!bWasCenter && oldAngle > 210.0f && oldAngle < 330.0f);
	
	uint buttonUp = m_controller->buttonsCount() + 4 * pov;
	if (bUp    != bWasUp)    {m_changes << JoystickChange{this, ControlType::Button, buttonUp,   bUp,   0.0};}
	if (bRight != bWasRight) {m_changes << JoystickChange{this, ControlType::Button, buttonUp+1, bRight,0.0};}
	if (bDown  != bWasDown)  {m_changes << JoystickChange{this, ControlType::Button, buttonUp+2, bDown, 0.0};}
	if (bLeft  != bWasLeft)  {m_changes << JoystickChange{this, ControlType::Button, buttonUp+3, bLeft, 0.0};}
}






// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint RealJoystick::buttonsCount() const
{
	if (m_bTransformPovInto4Buttons)
		return m_controller->buttonsCount() + 4 * m_controller->povsCount();
	else
		return m_controller->buttonsCount();
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool RealJoystick::buttonPressed(uint button) const
{
	if (button < m_controller->buttonsCount())
	{
		return m_controller->buttonValue(button);
	}
	else if (m_bTransformPovInto4Buttons && button < this->buttonsCount())
	{
		uint pov = (button-m_controller->buttonsCount()) / 4;
		uint num = (button-m_controller->buttonsCount()) % 4;
		float angle = m_controller->povValue(pov);
		
		if (num == 0)      {return (angle != -1.0f && (angle < 60.0f || angle > 300.0f));}
		else if (num == 1) {return (angle != -1.0f && angle >  30.0f && angle < 150.0f);}
		else if (num == 2) {return (angle != -1.0f && angle > 120.0f && angle < 240.0f);}
		else if (num == 3) {return (angle != -1.0f && angle > 210.0f && angle < 330.0f);}
	}
	
	return false;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString RealJoystick::buttonName(uint button) const
{
	if (button < m_controller->buttonsCount())
	{
		return "Button " + QString::number(button+1);
	}
	else if (m_bTransformPovInto4Buttons && button < this->buttonsCount())
	{
		uint pov = (button-m_controller->buttonsCount()) / 4;
		uint num = (button-m_controller->buttonsCount()) % 4;
		
		QString directionStr = "up";
		if (num == 1)      {directionStr = "right";}
		else if (num == 2) {directionStr = "down";}
		else if (num == 3) {directionStr = "left";}
		return "POV " + QString::number(pov+1) + " (" + directionStr + ")";
	}
	
	return {};
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList RealJoystick::buttonsNames() const
{
	QStringList list;
	for (uint i=0; i<this->buttonsCount(); ++i) {list << this->buttonName(i);}
	return list;
}






// AXES COUNT /////////////////////////////////////////////////////////////////
uint RealJoystick::axesCount() const {return m_controller->axesCount();}
// AXIS VALUE /////////////////////////////////////////////////////////////////
float RealJoystick::axisValue(uint axis) const {return m_controller->axisValue(axis);}
// AXIS NAME //////////////////////////////////////////////////////////////////
QString RealJoystick::axisName(uint axis) const {return "Axis " + QString::number(axis+1);}
// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList RealJoystick::axesNames() const
{
	QStringList list;
	for (uint i=0; i<this->axesCount(); ++i) {list << this->axisName(i);}
	return list;
}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint RealJoystick::povsCount() const
{
	if (m_bTransform4ButtonsIntoPov)
		return m_controller->povsCount() + m_virtualPovsDef.size();
	else
		return m_controller->povsCount();
}

// POV VALUE //////////////////////////////////////////////////////////////////
float RealJoystick::povValue(uint pov) const
{
	if (pov < m_controller->povsCount())
	{
		return m_controller->povValue(pov);
	}
	else if (m_bTransform4ButtonsIntoPov && pov < this->povsCount())
	{
		uint index = pov - m_controller->povsCount();
		const VirtualPovDefinition &vpd = m_virtualPovsDef[index];
		bool bUp    = m_controller->buttonValue(vpd.buttonUp);
		bool bRight = m_controller->buttonValue(vpd.buttonRight);
		bool bDown  = m_controller->buttonValue(vpd.buttonDown);
		bool bLeft  = m_controller->buttonValue(vpd.buttonLeft);
		
		return RealJoystick::buttonsToPov(bUp,bRight,bDown,bLeft);
	}
	
	return false;
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString RealJoystick::povName(uint pov) const
{
	if (pov < m_controller->povsCount())
	{
		return "POV " + QString::number(pov+1);
	}
	else if (m_bTransform4ButtonsIntoPov && pov < this->povsCount())
	{
		uint index = pov - m_controller->povsCount();
		return m_virtualPovsDef[index].povName;
	}
	
	return {};
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList RealJoystick::povsNames() const
{
	QStringList list;
	for (uint i=0; i<this->povsCount(); ++i) {list << this->povName(i);}
	return list;
}






// SET DATA ///////////////////////////////////////////////////////////////////
void RealJoystick::setData(const QString &str, QVariant v)
{
	Q_UNUSED(str)
	Q_UNUSED(v)
	// nothing by default
}

// FLUSH //////////////////////////////////////////////////////////////////////
void RealJoystick::flush()
{
	// nothing by default
}






// ADD VIRTUAL POV ////////////////////////////////////////////////////////////
void RealJoystick::addVirtualPov(uint nUp, uint nRight, uint nDown, uint nLeft, const QString &povName)
{
	m_virtualPovsDef << VirtualPovDefinition{nUp,nRight,nDown,nLeft,povName};
}

// BUTTONS TO POV /////////////////////////////////////////////////////////////
float RealJoystick::buttonsToPov(bool bUp, bool bRight, bool bDown, bool bLeft)
{
	if (bUp)
	{
		if (bLeft)       {return 315.0f;}
		else if (bRight) {return 45.0f;}
		else             {return 0.0f;}
	}
	else if (bDown)
	{
		if (bLeft)       {return 225.0f;}
		else if (bRight) {return 135.0f;}
		else             {return 180.0f;}
	}
	else
	{
		if (bLeft)       {return 270.0f;}
		else if (bRight) {return 90.0f;}
		else             {return -1.0f;}
	}
}

// BUTTON MAPS POV ////////////////////////////////////////////////////////////
uint RealJoystick::buttonMapsPov(uint button) const
{
	uint i = 0;
	for (const VirtualPovDefinition &vpd : m_virtualPovsDef)
	{
		if (button == vpd.buttonUp    ||
			button == vpd.buttonRight ||
			button == vpd.buttonDown  ||
			button == vpd.buttonLeft)
			{
				return i;
			}
		++i;
	}
	
	return -1u;
}

