#include "VirtualEventsQueue.h"
#include "../../VirtualJoysticks/src/VirtualJoystick.h"
#include "AbstractProfile.h"
#include "ACTIONS/Actions.h"
#include <windows.h>

bool VirtualEventsQueue::bInputRepeaterEnabled = false;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  POST EVENT
//  POST EVENTS
//  PROCESS EVENTS
//
//  SET INPUT REPEATER ENABLED
//  IS INPUT REPEATER ENABLED
//  SET INPUT REPEATER EVENT
//  UPDATE INPUT REPEATER EVENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
VirtualEventsQueue::VirtualEventsQueue(AbstractProfile *p) : m_profile{p}
{
	m_inputRepeaterDuration = 5000;
	m_inputRepeaterDtms = 0;
	m_inputRepeaterDtmsTotal = 0;
	m_bUseInputRepeaterEvent = false;
	m_inputRepeaterOriginalAxisValue = 0.0f;
}






// POST EVENT /////////////////////////////////////////////////////////////////
void VirtualEventsQueue::postEvent(const VirtualEvent &event)
{
	m_events.push_back(event);
	
	if (bInputRepeaterEnabled)
		this->setInputRepeaterEvent(event);
}

// POST EVENTS ////////////////////////////////////////////////////////////////
void VirtualEventsQueue::postEvents(const std::vector<VirtualEvent> &events)
{
	m_events.reserve(m_events.size()+events.size());
	m_events.insert(m_events.end(), events.begin(), events.end());
	
	if (bInputRepeaterEnabled)
		this->setInputRepeaterEvent(events.back());
}

// PROCESS EVENTS /////////////////////////////////////////////////////////////
void VirtualEventsQueue::processEvents()
{
	if (bInputRepeaterEnabled) {this->updateInputRepeaterEvent();}
	
	for (uint i=0; i<m_events.size(); ++i) // important to do like that because some callback called below can add events to run right away
	{
		VirtualEvent &e = m_events[i];
		if (e.delay == 0) // we process the event whose delay elapsed
		{
			if (e.type == EventType::VJoy && e.vjev.joystick) // it is a VJoyEvent and there is a VirtualJoystick specified
			{
				if (e.vjev.type == ControlType::Button)
				{
					e.vjev.joystick->setButton(e.vjev.numButtonAxisPov, e.vjev.bButtonPressed, Priority::Low);
				}
				else if (e.vjev.type == ControlType::Axis)
				{
					e.vjev.joystick->setAxis(e.vjev.numButtonAxisPov, e.vjev.axisOrPovValue, Priority::Low, TrimOrNot::UseTrim);
				}
				else if (e.vjev.type == ControlType::Pov)
				{
					e.vjev.joystick->setPov(e.vjev.numButtonAxisPov, e.vjev.axisOrPovValue, Priority::Low);
				}
			}
			else if (e.type == EventType::Keyboard) // it is a keyboard event
			{
				if (e.vkev.modifier) // with a modifier
				{
					INPUT ips[2];
					ips[0].type = INPUT_KEYBOARD;
					ips[1].type = INPUT_KEYBOARD;
					ips[0].ki.wVk = 0;
					ips[1].ki.wVk = 0;
					ips[0].ki.time = 0;
					ips[1].ki.time = 0;
					ips[0].ki.dwExtraInfo = 0;
					ips[1].ki.dwExtraInfo = 0;
					
					if (e.vkev.bPress)
					{
						// a press event
						ips[0].ki.wScan = MapVirtualKey(e.vkev.modifier,MAPVK_VK_TO_VSC);
						ips[1].ki.wScan = MapVirtualKey(e.vkev.key,MAPVK_VK_TO_VSC);
						ips[0].ki.dwFlags = KEYEVENTF_SCANCODE;
						ips[1].ki.dwFlags = KEYEVENTF_SCANCODE;
					}
					else
					{
						// a release event
						ips[0].ki.wScan = MapVirtualKey(e.vkev.key,MAPVK_VK_TO_VSC);
						ips[1].ki.wScan = MapVirtualKey(e.vkev.modifier,MAPVK_VK_TO_VSC);
						ips[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
						ips[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					}
					SendInput(2, ips, sizeof(INPUT));
				}
				else // with no modifier
				{
					INPUT ip;
					ip.type = INPUT_KEYBOARD;
					ip.ki.wVk = 0;
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;
					
					if (e.vkev.bPress)
					{
						// a press event
						ip.ki.wScan = MapVirtualKey(e.vkev.key,MAPVK_VK_TO_VSC);
						ip.ki.dwFlags = KEYEVENTF_SCANCODE;
					}
					else
					{
						// a release event
						ip.ki.wScan = MapVirtualKey(e.vkev.key,MAPVK_VK_TO_VSC);
						ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
					}
					SendInput(1, &ip, sizeof(INPUT));
				}
			}
			else if (e.type == EventType::Callback) // it is a callback
			{
				e.callback();
			}
		}
	}
	
	// we remove processed events
	auto wasProcessed = [] (const VirtualEvent &e) {return e.delay == 0;};
	auto newEnd = std::remove_if(m_events.begin(),m_events.end(),wasProcessed);
	m_events.erase(newEnd,m_events.end());
	
	// we decrement the counter of the other ones
	for (VirtualEvent &e : m_events) {e.delay--;}
}






// SET INPUT REPEATER ENABLED /////////////////////////////////////////////////
void VirtualEventsQueue::setInputRepeaterEnabled(bool b)
{
	bInputRepeaterEnabled = b;
}

// IS INPUT REPEATER ENABLED //////////////////////////////////////////////////
bool VirtualEventsQueue::isInputRepeaterEnabled()
{
	return bInputRepeaterEnabled;
}

// SET INPUT REPEATER EVENT ///////////////////////////////////////////////////
void VirtualEventsQueue::setInputRepeaterEvent(const VirtualEvent &event)
{
	bool noRepeaterEvent1 = event.type != EventType::VJoy;
	bool noRepeaterEvent2 = (event.vjev.type == ControlType::Pov && event.vjev.axisOrPovValue == -1.0f);
	if (noRepeaterEvent1 || noRepeaterEvent2) {return;}
	
	m_inputRepeaterDtms = 0;
	m_inputRepeaterDtmsTotal = 0;
	m_inputRepeaterEvent = event;
	m_bUseInputRepeaterEvent = true;
	
	if (m_inputRepeaterEvent.vjev.type == ControlType::Axis)
		m_inputRepeaterOriginalAxisValue = m_inputRepeaterEvent.vjev.axisOrPovValue;
}

// UPDATE INPUT REPEATER EVENT ////////////////////////////////////////////////
void VirtualEventsQueue::updateInputRepeaterEvent()
{
	if (!m_bUseInputRepeaterEvent) {return;}
	if (m_inputRepeaterEvent.type != EventType::VJoy) {return;}
	
	m_inputRepeaterDtms += m_profile->timeStep();
	m_inputRepeaterDtmsTotal += m_profile->timeStep();
	
	if (m_inputRepeaterDtms >= 500)
	{
		if (m_inputRepeaterEvent.vjev.type == ControlType::Button)
		{
			ActionButtonPulse action{m_inputRepeaterEvent.vjev.joystick, m_inputRepeaterEvent.vjev.numButtonAxisPov, m_profile->ms2cycles(50)};
			for (const VirtualEvent &event : action.generateEvents()) {m_events.push_back(event);}
		}
		else if (m_inputRepeaterEvent.vjev.type == ControlType::Axis)
		{
			m_inputRepeaterEvent.vjev.axisOrPovValue = (m_inputRepeaterEvent.vjev.axisOrPovValue >= 0) ? -0.5f : 0.5f;
			ActionAxisSetValue action{m_inputRepeaterEvent.vjev.joystick, m_inputRepeaterEvent.vjev.numButtonAxisPov, m_inputRepeaterEvent.vjev.axisOrPovValue};
			for (const VirtualEvent &event : action.generateEvents()) {m_events.push_back(event);}
		}
		else if (m_inputRepeaterEvent.vjev.type == ControlType::Pov)
		{
			VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_inputRepeaterEvent.vjev.joystick, ControlType::Pov, m_inputRepeaterEvent.vjev.numButtonAxisPov, false, m_inputRepeaterEvent.vjev.axisOrPovValue}, {}, {}, 0};
			VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_inputRepeaterEvent.vjev.joystick, ControlType::Pov, m_inputRepeaterEvent.vjev.numButtonAxisPov, false, -1.0f}, {}, {}, m_profile->ms2cycles(50)};
			m_events.push_back(ev1);
			m_events.push_back(ev2);
		}
		
		m_inputRepeaterDtms = 0;
	}
	
	if (m_inputRepeaterDtmsTotal >= m_inputRepeaterDuration)
	{
		// Return axis to its original value before the repeater started
		if (m_inputRepeaterEvent.vjev.type == ControlType::Axis)
		{
			ActionAxisSetValue action{m_inputRepeaterEvent.vjev.joystick, m_inputRepeaterEvent.vjev.numButtonAxisPov, m_inputRepeaterOriginalAxisValue};
			for (const VirtualEvent &event : action.generateEvents()) {m_events.push_back(event);}
		}
		
		m_inputRepeaterDtms = 0;
		m_inputRepeaterDtmsTotal = 0;
		m_bUseInputRepeaterEvent = false;
	}
}

