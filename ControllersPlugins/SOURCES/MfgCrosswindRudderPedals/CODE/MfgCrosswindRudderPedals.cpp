#include "MfgCrosswindRudderPedals.h"
#include "qgamecontroller.h"


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
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfgCrosswindRudderPedals::MfgCrosswindRudderPedals(QGameController *c) : RealJoystick{c}
{
	m_axesNames << "RUDDER" << "BRK_LEFT" << "BRK_RIGHT";
}






// SLOT GAME CONTROLLER BUTTON EVENT //////////////////////////////////////////
void MfgCrosswindRudderPedals::slotGameControllerButtonEvent(QGameControllerButtonEvent *event)
{
	Q_UNUSED(event)
}

// SLOT GAME CONTROLLER AXIS EVENT ////////////////////////////////////////////
void MfgCrosswindRudderPedals::slotGameControllerAxisEvent(QGameControllerAxisEvent *event)
{
	Q_ASSERT(event);
	
	uint axis = event->axis();
	if (axis == MfgCrosswindRudderPedals_::RUDDER)         {m_changes << JoystickChange{this,ControlType::Axis,0,false,event->value()};}
	else if (axis == MfgCrosswindRudderPedals_::BRK_LEFT)  {m_changes << JoystickChange{this,ControlType::Axis,2,false,event->value()};}
	else if (axis == MfgCrosswindRudderPedals_::BRK_RIGHT) {m_changes << JoystickChange{this,ControlType::Axis,1,false,event->value()};}
}




// DESCRIPTION ////////////////////////////////////////////////////////////////
QString MfgCrosswindRudderPedals::description() const
{
	return MfgCrosswindRudderPedals_::Description;
}




// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint MfgCrosswindRudderPedals::buttonsCount() const
{
	return 0;
}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool MfgCrosswindRudderPedals::buttonPressed(uint button) const
{
	Q_UNUSED(button)
	return false;
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString MfgCrosswindRudderPedals::buttonName(uint button) const
{
	Q_UNUSED(button)
	return QString();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList MfgCrosswindRudderPedals::buttonsNames() const
{
	return QStringList();
}




// AXES COUNT /////////////////////////////////////////////////////////////////
uint MfgCrosswindRudderPedals::axesCount() const
{
	return 3;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float MfgCrosswindRudderPedals::axisValue(uint axis) const
{
	if (axis == MfgCrosswindRudderPedals_::RUDDER)    {return this->RealJoystick::axisValue(0);}
	if (axis == MfgCrosswindRudderPedals_::BRK_LEFT)  {return this->RealJoystick::axisValue(2);}
	if (axis == MfgCrosswindRudderPedals_::BRK_RIGHT) {return this->RealJoystick::axisValue(1);}
	return 0.0;
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString MfgCrosswindRudderPedals::axisName(uint axis) const
{
	if (axis < 3)
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList MfgCrosswindRudderPedals::axesNames() const
{
	return m_axesNames;
}


