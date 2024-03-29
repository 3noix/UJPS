#ifndef JOYSTICK_CHANGE
#define JOYSTICK_CHANGE


#include "../../../../include/Other/ControlType.h"
class AbstractRealJoystick;
using uint = unsigned int;


// A structure that described an event (describing a change not a state) sent by a real controller.
// It replaces the Qt signal / slot mechanism that is used in the QtGameController library.
// Because we want to wait for retrieving all the events that occured during the last loop
// before processing these events.


struct JoystickChange
{
	AbstractRealJoystick* joystick;
	ControlType type; // button, axis or pov
	uint numButtonAxisPov;
	bool bButtonPressed;
	float axisOrPovValue;
};


#endif

