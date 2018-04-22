#include "MAPPINGS/MappingStandard.h"
#include "TRIGGERS/AbstractTrigger.h"
#include "ACTIONS/AbstractAction.h"
#include "AbstractRealJoystick.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  REACTS TO CHANGES
//  REACTS TO STATES
//  IS TRIGGERED
//  IS MAPPING BUTTON
//  IS MAPPING AXIS
//  PERFORM ACTION
//
//  ACTIVATE BY LAYER CHANGE
//  DEACTIVATE BY LAYER CHANGE
//  ABOUT TO BE DELETED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MappingStandard::MappingStandard(AbstractRealJoystick *rj, ControlType t, uint rnum, LayersCombo lc,
	AbstractTrigger *trigger,
	AbstractAction *action,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping(lc,eventsQueue)
{
	m_disable = false;
	m_rj = rj;
	m_type = t;
	m_rnum = rnum;
	
	m_trigger = trigger;
	m_action = action;
}

MappingStandard::~MappingStandard()
{
	if (m_trigger)
	{
		delete m_trigger;
		m_trigger = nullptr;
	}
	if (m_action)
	{
		delete m_action;
		m_action = nullptr;
	}
}




// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingStandard::reactsToChanges() const
{
	return m_trigger->reactsToChanges();
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingStandard::reactsToStates() const
{
	return m_trigger->reactsToStates();
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingStandard::isTriggered()
{
	if (!m_trigger) {return false;}
	return m_trigger->isTriggered(m_rj,m_type,m_rnum);
}

bool MappingStandard::isTriggered(const JoystickChange &ch)
{
	if (!m_trigger) {return false;}
	return m_trigger->isTriggered(m_rj,m_type,m_rnum,ch);
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingStandard::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	if (!m_trigger) {return false;}
	return (rj->id() == m_rj->id() && m_type == ControlType::Button && m_rnum == rButton);
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingStandard::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	if (!m_trigger) {return false;}
	return (rj->id() == m_rj->id() && m_type == ControlType::Axis && m_rnum == rAxis);
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingStandard::performAction()
{
	if (m_disable) {return;}
	if (!m_action) {return;}
	this->postEvents(m_action->generateEvents());
}

void MappingStandard::performAction(const JoystickChange &ch)
{
	if (m_disable) {return;}
	if (!m_action) {return;}
	this->postEvents(m_action->generateEvents(ch));
}




// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingStandard::activateByLayerChange()
{
	if (!m_action) {return;}
	this->postEvents(m_action->activateByLayerChange(m_rj,m_type,m_rnum));
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingStandard::deactivateByLayerChange()
{
	if (!m_action) {return;}
	this->postEvents(m_action->deactivateByLayerChange());
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingStandard::aboutToBeDeleted()
{
	m_disable = true;
	
	if (m_action)
		this->postEvents(m_action->aboutToBeDeleted());
}


