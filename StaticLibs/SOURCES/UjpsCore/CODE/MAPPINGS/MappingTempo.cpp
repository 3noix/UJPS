#include "MAPPINGS/MappingTempo.h"
#include "ACTIONS/AbstractAction.h"
#include "AbstractRealJoystick.h"


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
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MappingTempo::MappingTempo(AbstractRealJoystick *rj, uint rButton, LayersCombo lc,
	uint cycles,
	AbstractAction *action1,
	AbstractAction *action2,
	VirtualEventsQueue &eventsQueue)
		: AbstractMapping(lc,eventsQueue)
{
	m_disable = false;
	m_rj = rj;
	m_rButton = rButton;
	m_cycles  = cycles;
	m_action1 = action1;
	m_action2 = action2;
	
	m_isRunning = false;
	m_compteur = 0;
	m_useAction1 = true;
}

MappingTempo::~MappingTempo()
{
	if (m_action1)
	{
		delete m_action1;
		m_action1 = nullptr;
	}
	if (m_action2)
	{
		delete m_action2;
		m_action2 = nullptr;
	}
}




// REACTS TO CHANGES //////////////////////////////////////////////////////////
bool MappingTempo::reactsToChanges() const
{
	return !m_isRunning;
}

// REACTS TO STATES ///////////////////////////////////////////////////////////
bool MappingTempo::reactsToStates() const
{
	return m_isRunning;
}

// IS TRIGGERED ///////////////////////////////////////////////////////////////
bool MappingTempo::isTriggered()
{
	if (!m_isRunning) {return false;}
	++m_compteur;
	m_useAction1 = !m_rj->buttonPressed(m_rButton);
	return (m_useAction1 || m_compteur >= m_cycles);
}

bool MappingTempo::isTriggered(const JoystickChange &ch)
{
	return (!m_isRunning &&
			ch.joystick && m_rj &&
			ch.joystick->id() == m_rj->id() &&
			ch.type == ControlType::Button &&
			ch.numButtonOrAxis == m_rButton &&
			ch.bButtonPressed);
}

// IS MAPPING BUTTON //////////////////////////////////////////////////////////
bool MappingTempo::isMappingButton(AbstractRealJoystick *rj, uint rButton) const
{
	return (rj->id() == m_rj->id() && rButton == m_rButton);
}

// IS MAPPING AXIS ////////////////////////////////////////////////////////////
bool MappingTempo::isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const
{
	Q_UNUSED(rj)
	Q_UNUSED(rAxis)
	return false;
}

// PERFORM ACTION /////////////////////////////////////////////////////////////
void MappingTempo::performAction()
{
	if (m_disable) {return;}
	
	if (m_useAction1 && m_action1)
		this->postEvents(m_action1->generateEvents());
	else if (!m_useAction1 && m_action2)
		this->postEvents(m_action2->generateEvents());
	
	m_isRunning = false;
	m_compteur = 0;
}

void MappingTempo::performAction(const JoystickChange &ch)
{
	Q_UNUSED(ch)
	if (m_disable) {return;}
	m_isRunning = true;
	m_compteur = 0;
}






// ACTIVATE BY LAYER CHANGE ///////////////////////////////////////////////////
void MappingTempo::activateByLayerChange()
{
	// we do nothing, one must press again the button to reactivate the tempo
}

// DEACTIVATE BY LAYER CHANGE /////////////////////////////////////////////////
void MappingTempo::deactivateByLayerChange()
{
	if (!m_isRunning) {return;}
	
	m_isRunning = false;
	m_compteur = 0;
	
	if (m_useAction1 && m_action1)
		this->postEvents(m_action1->deactivateByLayerChange());
	else if (!m_useAction1 && m_action2)
		this->postEvents(m_action2->deactivateByLayerChange());
}

// ABOUT TO BE DELETED ////////////////////////////////////////////////////////
void MappingTempo::aboutToBeDeleted()
{
	m_disable = true;
	
	if (!m_isRunning) {return;}
	if (m_useAction1 && m_action1)
		this->postEvents(m_action1->aboutToBeDeleted());
	else if (!m_useAction1 && m_action2)
		this->postEvents(m_action2->aboutToBeDeleted());
}


