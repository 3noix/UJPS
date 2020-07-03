#include "GameControllerEvents.h"


///////////////////////////////////////////////////////////////////////////////
//  GAME CONTROLLER AXIS EVENT
//  GAME CONTROLLER BUTTON EVENT
//  GAME CONTROLLER POV EVENT
///////////////////////////////////////////////////////////////////////////////


// GAME CONTROLLER AXIS EVENT /////////////////////////////////////////////////
GameControllerAxisEvent::GameControllerAxisEvent(uint controllerId, uint axis, float value) :
	m_id{controllerId},
	m_axis{axis},
	m_value{value}
{
}

uint GameControllerAxisEvent::controllerId() const {return m_id;}
uint GameControllerAxisEvent::axis() const {return m_axis;}
float GameControllerAxisEvent::value() const {return m_value;}




// GAME CONTROLLER BUTTON EVENT ///////////////////////////////////////////////
GameControllerButtonEvent::GameControllerButtonEvent(uint controllerId, uint button, bool pressed) :
	m_id{controllerId},
	m_button{button},
	m_pressed{pressed}
{
}

uint GameControllerButtonEvent::controllerId() const {return m_id;}
uint GameControllerButtonEvent::button() const {return m_button;}
bool GameControllerButtonEvent::pressed() const {return m_pressed;}




// GAME CONTROLLER POV EVENT //////////////////////////////////////////////////
GameControllerPovEvent::GameControllerPovEvent(uint controllerId, uint pov, float angle) :
	m_id{controllerId},
	m_pov{pov},
	m_angle{angle}
{
}

uint GameControllerPovEvent::controllerId() const {return m_id;}
uint GameControllerPovEvent::pov() const {return m_pov;}
float GameControllerPovEvent::angle() const {return m_angle;}

