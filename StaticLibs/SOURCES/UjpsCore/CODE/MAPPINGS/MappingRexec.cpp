#include "MAPPINGS/MappingRexec.h"
#include "ACTIONS/AbstractAction.h"


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
MappingRexec::MappingRexec(uint id, uint cycles, AbstractAction *action, VirtualEventsQueue &eventsQueue)
	: AbstractMapping(LayersCombo{},eventsQueue)
{
	m_disable = false;
	
	m_id = id;
	m_cycles = cycles;
	m_compteur = 0;
	m_action = action;
}

MappingRexec::~MappingRexec()
{
	// this mapping is deleted when stopRexec is called
	// but the action must not be deleted here, otherwise it will be impossible to recall startRexec with the same action in argument
	// so the user (profile programmer) must be careful to delete it in his profile to avoid memory leaks
}




// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingRexec::reactsToChanges() const
{
	return false;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingRexec::reactsToStates() const
{
	return true;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingRexec::isTriggered()
{
	return true;
}

bool MappingRexec::isTriggered(const JoystickChange &ch)
{
	Q_UNUSED(ch)
	return false;
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingRexec::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rButton)
	return false;
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingRexec::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rAxis)
	return false;
}

// IS MAPPING POV /////////////////////////////////////////////////////////////
bool MappingRexec::isMappingPov(AbstractRealJoystick *rj, uint rPov) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rPov)
	return false;
}

// IS MAPPING REXEC ///////////////////////////////////////////////////////////
bool MappingRexec::isMappingRexec(uint id) const
{
	if (id == -1u) {return true;}
	return (id == m_id);
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingRexec::performAction()
{
	if (m_disable) {return;}
	if (!m_action) {return;}
	
	if (m_compteur == 0) {this->postEvents(m_action->generateEvents());}
	m_compteur = (m_compteur + 1) % m_cycles;
}

void MappingRexec::performAction(const JoystickChange &ch)
{
	Q_UNUSED(ch)
}




// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingRexec::activateByLayerChange()
{
	// this mapping is not dependent to layers => never called
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingRexec::deactivateByLayerChange()
{
	// this mapping is not dependent to layers => never called
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingRexec::aboutToBeDeleted()
{
	m_disable = true;
	
	//if (m_action)
	//	this->postEvents(m_action->aboutToBeDeleted());
}

