#include "MAPPINGS/MappingMergeAxes.h"
#include "AbstractRealJoystick.h"
#include "Lim.h"
#include "CURVES/AbstractAxisCurve.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  REACTS TO CHANGES
//  REACTS TO STATES
//  IS TRIGGERED
//  IS MAPPING BUTTON
//  IS MAPPING AXIS
//  IS MAPPING POV
//  PERFORM ACTION
//
//  ACTIVATE BY LAYER CHANGE
//  DEACTIVATE BY LAYER CHANGE
//  ABOUT TO BE DELETED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MappingMergeAxes::MappingMergeAxes(AbstractRealJoystick *rj1, uint rAxis1, float k1,
	AbstractRealJoystick *rj2, uint rAxis2, float k2,
	LayersCombo lc,
	VirtualJoystick *vj, uint vAxis,
	AbstractAxisCurve *curve,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping(lc,eventsQueue)
{
	m_disable = false;
	m_rj1 = rj1;
	m_rj2 = rj2;
	m_k1 = k1;
	m_k2 = k2;
	m_vj = vj;
	m_rAxis1 = rAxis1;
	m_rAxis2 = rAxis2;
	m_vAxis = vAxis;
	m_curve = curve;
}

MappingMergeAxes::~MappingMergeAxes()
{
	if (m_curve) {delete m_curve;}
}




// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingMergeAxes::reactsToChanges() const
{
	return true;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingMergeAxes::reactsToStates() const
{
	return false;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingMergeAxes::isTriggered()
{
	return false;
}

bool MappingMergeAxes::isTriggered(const JoystickChange &ch)
{
	return (ch.joystick != nullptr && m_rj1 != nullptr && m_rj2 != nullptr &&
		((ch.joystick->id() == m_rj1->id() && ch.numButtonAxisPov == m_rAxis1)
			|| (ch.joystick->id() == m_rj2->id() && ch.numButtonAxisPov == m_rAxis2)) &&
		ch.type == ControlType::Axis);
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingMergeAxes::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rButton)
	
	return false;
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingMergeAxes::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	return ((rj->id() == m_rj1->id() && rAxis == m_rAxis1)
			|| (rj->id() == m_rj2->id() && rAxis == m_rAxis2));
}

// IS MAPPING POV /////////////////////////////////////////////////////////////
bool MappingMergeAxes::isMappingPov(AbstractRealJoystick *rj, uint rPov) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rPov)
	return false;
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingMergeAxes::performAction()
{
	
}

void MappingMergeAxes::performAction(const JoystickChange &ch)
{
	Q_UNUSED(ch)
	if (m_disable) {return;}
	
	float value = m_k1 * m_rj1->axisValue(m_rAxis1) + m_k2 * m_rj2->axisValue(m_rAxis2);
	if (m_curve) {value = m_curve->run(value);}
	value = lim<float>(value,-1.0f,1.0f);
	VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,value},{},{},0};
	this->postEvent(ev);
}




// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingMergeAxes::activateByLayerChange()
{
	// we don't wait for a change in the real joystick position to update the virtual joystick position
	float value = m_k1 * m_rj1->axisValue(m_rAxis1) + m_k2 * m_rj2->axisValue(m_rAxis2);
	if (m_curve) {value = m_curve->run(value);}
	value = lim<float>(value,-1.0f,1.0f);
	VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,value},{},{},0};
	this->postEvent(ev);
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingMergeAxes::deactivateByLayerChange()
{
	// we do nothing, the axis stays at its value
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingMergeAxes::aboutToBeDeleted()
{
	m_disable = true;
}


