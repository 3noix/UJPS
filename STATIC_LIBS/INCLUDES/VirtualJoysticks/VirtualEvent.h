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
	VJoy,
	Keyboard,
	Callback
};

struct VJoyEvent
{
	VirtualJoystick* joystick;
	ControlType type; // button or axis
	uint numButtonOrAxis;
	bool bButtonPressed;
	float axisValue;
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


