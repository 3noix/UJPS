#include "MAPPINGS/MappingAxis1.h"
#include "ACTIONS/AbstractAction.h"
#include "AbstractRealJoystick.h"
#include "ExceptionBadMapAxis1.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  REACTS TO CHANGES
//  IS TRIGGERED
//  IS MAPPING BUTTON
//  IS MAPPING AXIS
//  PERFORM ACTION
//
//  ACTIVATE BY LAYER CHANGE
//  DEACTIVATE BY LAYER CHANGE
//  ABOUT TO BE DELETED
//
//  COMPUTE ZONE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MappingAxis1::MappingAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc,
	const std::vector<float> &points,
	AbstractAction *actionPlus,
	AbstractAction *actionMoins,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping(lc,eventsQueue)
{
	if (points.size() == 0) {throw ExceptionBadMapAxis1{};}
	
	m_disable = false;
	m_rj = rj;
	m_rAxis = rAxis;
	m_points = points;
	m_actionPlus = actionPlus;
	m_actionMoins = actionMoins;
	
	m_previousZone = this->computeZone(m_rj->axisValue(m_rAxis));
	m_useActionPlus = true;
}

MappingAxis1::~MappingAxis1()
{
	if (m_actionPlus)
	{
		delete m_actionPlus;
		m_actionPlus = nullptr;
	}
	if (m_actionMoins)
	{
		delete m_actionMoins;
		m_actionMoins = nullptr;
	}
}




// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingAxis1::reactsToChanges() const
{
	return true;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingAxis1::reactsToStates() const
{
	return false;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingAxis1::isTriggered()
{
	return false;
}

bool MappingAxis1::isTriggered(const JoystickChange &ch)
{
	bool b = (ch.joystick && m_rj &&
			ch.joystick->id() == m_rj->id() &&
			ch.type == ControlType::Axis &&
			ch.numButtonOrAxis == m_rAxis);
	
	if (!b) {return false;}
	
	bool bFirstZone = (m_previousZone == 0);
	bool bLastZone = (m_previousZone == m_points.size());
	bool bOtherZone = (!bFirstZone && !bLastZone);
	
	if ((bFirstZone && ch.axisValue >= m_points[0]) ||
		(bOtherZone && ch.axisValue >= m_points[m_previousZone]))
	{
		m_useActionPlus = true;
		return true;
	}
	
	if ((bLastZone  && ch.axisValue < m_points[m_points.size()-1]) ||
		(bOtherZone && ch.axisValue < m_points[m_previousZone-1]))
	{
		m_useActionPlus = false;
		return true;
	}
	
	return false;
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingAxis1::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rButton)
	return false;
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingAxis1::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	return (rj->id() == m_rj->id() && rAxis == m_rAxis);
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingAxis1::performAction()
{
	
}

void MappingAxis1::performAction(const JoystickChange &ch)
{
	if (m_disable) {return;}
	
	if (m_useActionPlus && m_actionPlus)
		this->postEvents(m_actionPlus->generateEvents());
	else if (!m_useActionPlus && m_actionMoins)
		this->postEvents(m_actionMoins->generateEvents());
		
	m_previousZone = this->computeZone(ch.axisValue);
}




// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingAxis1::activateByLayerChange()
{
	if (m_useActionPlus && m_actionPlus)
		this->postEvents(m_actionPlus->activateByLayerChange(m_rj, ControlType::Axis, m_rAxis));
	else if (!m_useActionPlus && m_actionMoins)
		this->postEvents(m_actionMoins->activateByLayerChange(m_rj, ControlType::Axis, m_rAxis));
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingAxis1::deactivateByLayerChange()
{
	if (m_useActionPlus && m_actionPlus)
		this->postEvents(m_actionPlus->deactivateByLayerChange());
	else if (!m_useActionPlus && m_actionMoins)
		this->postEvents(m_actionMoins->deactivateByLayerChange());
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingAxis1::aboutToBeDeleted()
{
	m_disable = true;
	
	if (m_useActionPlus && m_actionPlus)
		this->postEvents(m_actionPlus->aboutToBeDeleted());
	else if (!m_useActionPlus && m_actionMoins)
		this->postEvents(m_actionMoins->aboutToBeDeleted());
}





// COMPUTE ZONE ///////////////////////////////////////////////////////////////
uint MappingAxis1::computeZone(float axisValue)
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


