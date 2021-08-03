#include "MappingAxisRelative.h"
#include "../../../RealJoysticks/src/AbstractRealJoystick.h"
#include "../../../VirtualJoysticks/src/VirtualJoystick.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  REACTS TO CHANGES
//  IS TRIGGERED
//  IS MAPPING BUTTON
//  IS MAPPING AXIS
//  IS MAPPING POV
//  IS MAPPING REXEC
//  PERFORM ACTION
//
//  ACTIVATE BY LAYER CHANGE
//  DEACTIVATE BY LAYER CHANGE
//  ABOUT TO BE DELETED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MappingAxisRelative::MappingAxisRelative(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc,
	VirtualJoystick *vj, uint vAxis, float factor,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping{lc,eventsQueue}
{
	m_disable = false;
	
	m_rj = rj;
	m_rAxis = rAxis;
	m_vj = vj;
	m_vAxis = vAxis;
	m_factor = factor;
}

MappingAxisRelative::~MappingAxisRelative()
{
	
}






// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingAxisRelative::reactsToChanges() const
{
	return false;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingAxisRelative::reactsToStates() const
{
	return true;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingAxisRelative::isTriggered()
{
	return true;
}

bool MappingAxisRelative::isTriggered(const JoystickChange &ch)
{
	Q_UNUSED(ch)
	return false;
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingAxisRelative::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rButton)
	return false;
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingAxisRelative::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	return (rj->id() == m_rj->id() && rAxis == m_rAxis);
}

// IS MAPPING POV /////////////////////////////////////////////////////////////
bool MappingAxisRelative::isMappingPov(AbstractRealJoystick *rj, uint rPov) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rPov)
	return false;
}

// IS MAPPING REXEC ///////////////////////////////////////////////////////////
bool MappingAxisRelative::isMappingRexec(uint id) const
{
	Q_UNUSED(id)
	return false;
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingAxisRelative::performAction()
{
	if (m_disable) {return;}
	
	float f = m_rj->axisValue(m_rAxis);
	if (f == 0) {return;}
	
	float newValue = m_vj->getAxis(m_vAxis) + m_factor * f;
	this->postEvent(VirtualEvent{EventType::VJoy,{m_vj,ControlType::Axis,m_vAxis,false,newValue},{},{},0});
}

void MappingAxisRelative::performAction(const JoystickChange &ch)
{
	Q_UNUSED(ch)
}






// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingAxisRelative::activateByLayerChange()
{
	float f = m_rj->axisValue(m_rAxis);
	if (f == 0) {return;}
	
	float newValue = m_vj->getAxis(m_vAxis) + m_factor * f;
	this->postEvent(VirtualEvent{EventType::VJoy,{m_vj,ControlType::Axis,m_vAxis,false,newValue},{},{},0});
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingAxisRelative::deactivateByLayerChange()
{
	// we do nothing, the axis stays at its value
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingAxisRelative::aboutToBeDeleted()
{
	// we do nothing, the axis stays at its value
}

