#include "RealJoystick.h"
#include "qgamecontroller.h"


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
//  SET DATA
//  FLUSH
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
RealJoystick::RealJoystick(QGameController *c) : QObject{}, AbstractRealJoystick{}
{
	Q_ASSERT(c);
	m_controller = c;
	m_controller->readGameController();
	
	QObject::connect(c,&QGameController::gameControllerAxisEvent,this,&RealJoystick::slotGameControllerAxisEvent);
	QObject::connect(c,&QGameController::gameControllerButtonEvent,this,&RealJoystick::slotGameControllerButtonEvent);
	QObject::connect(c,&QGameController::gameControllerPovEvent,this,&RealJoystick::slotGameControllerPovEvent);
	
	m_povsAngles = QVector<float>(m_controller->povsCount(),-1.0f);
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
	return m_changes;
}





// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void RealJoystick::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Axis,event->axis(),false,event->value()};
}

// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void RealJoystick::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_ASSERT(event);
	m_changes << JoystickChange{this,ControlType::Button,event->button(),event->pressed(),0.0};
}

// SLOT GAME CONTROLLER POV EVENT /////////////////////////////////////////////
void RealJoystick::slotGameControllerPovEvent(QGameControllerPovEvent *event)
{
	Q_ASSERT(event);
	
	uint pov = event->pov();
	float angle = event->angle();
	float oldAngle = m_povsAngles[pov];
	
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
	
	m_povsAngles[pov] = angle;
}





// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint RealJoystick::buttonsCount() const
{
	return m_controller->buttonsCount() + 4 * m_controller->povsCount();
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool RealJoystick::buttonPressed(uint button) const
{
	if (button < m_controller->buttonsCount())
	{
		return m_controller->buttonValue(button);
	}
	else if (button < m_controller->buttonsCount() + 4 * m_controller->povsCount())
	{
		uint pov = (button-m_controller->buttonsCount()) / 4;
		uint num = (button-m_controller->buttonsCount()) % 4;
		float angle = m_povsAngles[pov];
		
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
	else if (button < m_controller->buttonsCount() + 4 * m_controller->povsCount())
	{
		uint pov = (button-m_controller->buttonsCount()) / 4;
		uint num = (button-m_controller->buttonsCount()) % 4;
		
		QString directionStr = "up";
		if (num == 1)      {directionStr = "right";}
		else if (num == 2) {directionStr = "down";}
		else if (num == 3) {directionStr = "left";}
		return "POV " + QString::number(pov+1) + " (" + directionStr + ")";
	}
	
	return QString();
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
QString RealJoystick::axisName(uint axis) const {return "Axis " + QString::number(axis);}
// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList RealJoystick::axesNames() const
{
	QStringList list;
	for (uint i=0; i<this->axesCount(); ++i) {list << this->axisName(i);}
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




