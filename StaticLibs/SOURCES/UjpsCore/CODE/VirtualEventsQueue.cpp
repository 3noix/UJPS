#include "VirtualEventsQueue.h"
#include "VirtualJoystick.h"
#include <windows.h>



// POST EVENT /////////////////////////////////////////////////////////////////
void VirtualEventsQueue::postEvent(const VirtualEvent &event)
{
	m_events << event;
}

// POST EVENTS ////////////////////////////////////////////////////////////////
void VirtualEventsQueue::postEvents(const QVector<VirtualEvent> &events)
{
	m_events << events;
}


// PROCESS EVENTS /////////////////////////////////////////////////////////////
void VirtualEventsQueue::processEvents()
{
	int nbEvents = m_events.size();
	
	for (VirtualEvent &e : m_events)
	{
		if (e.delay == 0) // we process the event whose delay elapsed
		{
			if (e.type == EventType::VJoy) // it is a VJoyEvent
			{
				if (e.vjev.joystick) // and there is a VirtualJoystick specified
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
			}
			else if (e.type == EventType::Keyboard) // it is a keyboard event
			{
				if (e.vkev.modifier) // with a modifier
				{
					INPUT ips[2];
					ips[0].type = INPUT_KEYBOARD;
					ips[1].type = INPUT_KEYBOARD;
					ips[0].ki.wScan = 0;
					ips[1].ki.wScan = 0;
					ips[0].ki.time = 0;
					ips[1].ki.time = 0;
					ips[0].ki.dwExtraInfo = 0;
					ips[1].ki.dwExtraInfo = 0;
					
					if (e.vkev.bPress)
					{
						// a press event
						ips[0].ki.wVk = e.vkev.modifier;
						ips[1].ki.wVk = e.vkev.key;
						ips[0].ki.dwFlags = 0;
						ips[1].ki.dwFlags = 0;
					}
					else
					{
						// a release event
						ips[0].ki.wVk = e.vkev.key;
						ips[1].ki.wVk = e.vkev.modifier;
						ips[0].ki.dwFlags = KEYEVENTF_KEYUP;
						ips[1].ki.dwFlags = KEYEVENTF_KEYUP;
					}
					SendInput(2, ips, sizeof(INPUT));
				}
				else // with no modifier
				{
					INPUT ip;
					ip.type = INPUT_KEYBOARD;
					ip.ki.wScan = 0;
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;
					
					if (e.vkev.bPress)
					{
						// a press event
						ip.ki.wVk = e.vkev.key;
						ip.ki.dwFlags = 0;
					}
					else
					{
						// a release event
						ip.ki.wVk = e.vkev.key;
						ip.ki.dwFlags = KEYEVENTF_KEYUP;
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
	
	for (int i=nbEvents-1; i>=0; --i)
	{
		if (m_events[i].delay == 0)
		{
			// we remove processed events
			m_events.removeAt(i);
		}
		else
		{
			// we decrement the counter of other ones
			m_events[i].delay--;
		}
	}
}


