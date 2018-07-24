#ifndef VIRTUAL_EVENT
#define VIRTUAL_EVENT


#include <functional>
#include "../OTHER/ControlType.h"
class VirtualJoystick;
using uint = unsigned int;


// a structure that describe keyboard or virtual joysticks events
// such structures are sent to the VirtualEventsQueue that performs the events

enum class EventType
{
	Unused,
	VJoy,
	Keyboard,
	Callback
};


struct VJoyEvent
{
	VirtualJoystick* joystick;
	ControlType type; // button, axis or pov
	uint numButtonAxisPov;
	bool bButtonPressed;
	float axisOrPovValue;
};


struct KeyboardEvent
{
	bool bPress;
	uint key;
	uint modifier;
};


struct VirtualEvent
{
	EventType type;
	VJoyEvent vjev;
	KeyboardEvent vkev;
	std::function<void()> callback;
	uint delay;
};


#endif


