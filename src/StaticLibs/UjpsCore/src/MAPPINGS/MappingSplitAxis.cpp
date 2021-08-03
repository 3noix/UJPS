#include "MappingSplitAxis.h"
#include "../../../RealJoysticks/src/AbstractRealJoystick.h"
#include "../../../../../include/Other/Lim.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  REACTS TO CHANGES
//  REACTS TO STATES
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
MappingSplitAxis::MappingSplitAxis(AbstractRealJoystick *rj, uint rAxis,
	LayersCombo lc,
	VirtualJoystick *vj1, uint vAxis1,
	VirtualJoystick *vj2, uint vAxis2,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping{lc,eventsQueue}
{
	m_disable = false;
	m_rj = rj;
	m_vj1 = vj1;
	m_vj2 = vj2;
	m_rAxis = rAxis;
	m_vAxis1 = vAxis1;
	m_vAxis2 = vAxis2;
}

MappingSplitAxis::~MappingSplitAxis()
{
	
}






// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingSplitAxis::reactsToChanges() const
{
	return true;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingSplitAxis::reactsToStates() const
{
	return false;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingSplitAxis::isTriggered()
{
	return false;
}

bool MappingSplitAxis::isTriggered(const JoystickChange &ch)
{
	return (ch.joystick != nullptr && m_rj != nullptr &&
		ch.joystick->id() == m_rj->id() &&
		ch.numButtonAxisPov == m_rAxis &&
		ch.type == ControlType::Axis);
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingSplitAxis::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rButton)
	
	return false;
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingSplitAxis::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	return (rj->id() == m_rj->id() && rAxis == m_rAxis);
}

// IS MAPPING POV /////////////////////////////////////////////////////////////
bool MappingSplitAxis::isMappingPov(AbstractRealJoystick *rj, uint rPov) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rPov)
	return false;
}

// IS MAPPING REXEC ///////////////////////////////////////////////////////////
bool MappingSplitAxis::isMappingRexec(uint id) const
{
	Q_UNUSED(id)
	return false;
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingSplitAxis::performAction()
{
	
}

void MappingSplitAxis::performAction(const JoystickChange &ch)
{
	Q_UNUSED(ch)
	if (m_disable) {return;}
	
	if (ch.axisOrPovValue < 0)
	{
		float value = -2.0f * ch.axisOrPovValue - 1.0f;
		value = lim<float>(value,-1.0f,1.0f);
		VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_vj1,ControlType::Axis,m_vAxis1,false,value},{},{},0};
		VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_vj2,ControlType::Axis,m_vAxis2,false,-1.0f},{},{},0};
		this->postEvents({ev1,ev2});
	}
	else
	{
		float value = 2.0f * ch.axisOrPovValue - 1.0f;
		value = lim<float>(value,-1.0f,1.0f);
		VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_vj1,ControlType::Axis,m_vAxis1,false,-1.0f},{},{},0};
		VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_vj2,ControlType::Axis,m_vAxis2,false,value},{},{},0};
		this->postEvents({ev1,ev2});
	}
}






// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingSplitAxis::activateByLayerChange()
{
	// we don't wait for a change in the real joystick position to update the virtual joystick position
	float value = m_rj->axisValue(m_rAxis);
	if (value < 0)
	{
		value = -2.0f * value - 1.0f;
		value = lim<float>(value,-1.0f,1.0f);
		VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_vj1,ControlType::Axis,m_vAxis1,false,value},{},{},0};
		VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_vj2,ControlType::Axis,m_vAxis2,false,-1.0f},{},{},0};
		this->postEvents({ev1,ev2});
	}
	else
	{
		value = 2.0f * value - 1.0f;
		value = lim<float>(value,-1.0f,1.0f);
		VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_vj1,ControlType::Axis,m_vAxis1,false,-1.0f},{},{},0};
		VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_vj2,ControlType::Axis,m_vAxis2,false,value},{},{},0};
		this->postEvents({ev1,ev2});
	}
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingSplitAxis::deactivateByLayerChange()
{
	// we do nothing, the axis stays at its value
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingSplitAxis::aboutToBeDeleted()
{
	m_disable = true;
}

