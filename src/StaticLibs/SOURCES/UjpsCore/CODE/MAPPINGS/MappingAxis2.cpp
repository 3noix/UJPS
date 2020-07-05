#include "MappingAxis2.h"
#include "ACTIONS/AbstractAction.h"
#include "AbstractRealJoystick.h"
#include "ExceptionBadMapAxis2.h"
#include "Lim.h"


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
//
//  COMPUTE ZONE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MappingAxis2::MappingAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc,
	const std::vector<float> &points,
	const std::vector<AbstractAction*> &actions,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping{lc,eventsQueue}
{
	if (points.size() == 0 || actions.size() != points.size()+1) {throw ExceptionBadMapAxis2{};}
	
	m_disable = false;
	m_rj = rj;
	m_rAxis = rAxis;
	m_points = points;
	m_actions = actions;
	
	m_previousZone = this->computeZone(m_rj->axisValue(m_rAxis));
	m_newZone = m_previousZone;
}

MappingAxis2::~MappingAxis2()
{
	for (AbstractAction *action : m_actions)
	{
		if (action)
			delete action;
	}
}






// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingAxis2::reactsToChanges() const
{
	return true;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingAxis2::reactsToStates() const
{
	return false;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingAxis2::isTriggered()
{
	return false;
}

bool MappingAxis2::isTriggered(const JoystickChange &ch)
{
	bool b = (ch.joystick && m_rj &&
			ch.joystick->id() == m_rj->id() &&
			ch.type == ControlType::Axis &&
			ch.numButtonAxisPov == m_rAxis);
	
	if (!b) {return false;}
	
	bool bFirstZone = (m_previousZone == 0);
	bool bLastZone = (m_previousZone == m_points.size());
	bool bOtherZone = (!bFirstZone && !bLastZone);
	
	if ((bFirstZone && ch.axisOrPovValue >= m_points[0]) ||
		(bOtherZone && ch.axisOrPovValue >= m_points[m_previousZone]))
	{
		m_newZone = lim<uint>(m_previousZone+1,0,m_points.size());
		return true;
	}
	
	if ((bLastZone  && ch.axisOrPovValue < m_points[m_points.size()-1]) ||
		(bOtherZone && ch.axisOrPovValue < m_points[m_previousZone-1]))
	{
		m_newZone = lim<uint>(m_previousZone-1,0,m_points.size());
		return true;
	}
	
	return false;
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingAxis2::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rButton)
	return false;
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingAxis2::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	return (rj->id() == m_rj->id() && rAxis == m_rAxis);
}

// IS MAPPING POV /////////////////////////////////////////////////////////////
bool MappingAxis2::isMappingPov(AbstractRealJoystick *rj, uint rPov) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rPov)
	return false;
}

// IS MAPPING REXEC ///////////////////////////////////////////////////////////
bool MappingAxis2::isMappingRexec(uint id) const
{
	Q_UNUSED(id)
	return false;
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingAxis2::performAction()
{
	
}

void MappingAxis2::performAction(const JoystickChange &ch)
{
	if (m_disable) {return;}
	
	if (m_actions[m_newZone])
		this->postEvents(m_actions[m_newZone]->generateEvents());
		
	m_previousZone = this->computeZone(ch.axisOrPovValue);
}






// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingAxis2::activateByLayerChange()
{
	if (m_actions[m_previousZone])
		this->postEvents(m_actions[m_previousZone]->activateByLayerChange(m_rj, ControlType::Axis, m_rAxis));
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingAxis2::deactivateByLayerChange()
{
	if (m_actions[m_previousZone])
		this->postEvents(m_actions[m_previousZone]->deactivateByLayerChange());
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingAxis2::aboutToBeDeleted()
{
	m_disable = true;
	
	if (m_actions[m_previousZone])
		this->postEvents(m_actions[m_previousZone]->aboutToBeDeleted());
}






// COMPUTE ZONE ///////////////////////////////////////////////////////////////
uint MappingAxis2::computeZone(float axisValue)
{
	if (axisValue <= m_points[0]) {return 0;}
	else if (axisValue >= m_points[m_points.size()-1]) {return m_points.size();}
	else
	{
		int max = m_points.size() - 1;
		int min = 0;
		int cour = 0;
		
		do
		{
			cour = (min + max) / 2;
			if (axisValue < m_points[cour]) {max = cour;}
			else {min = cour;}
		} while (max != (min+1));
		
		return max;
	}
}

