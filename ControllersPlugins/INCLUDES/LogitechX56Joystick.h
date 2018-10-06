#ifndef LOGITECH_X56_JOYSTICK_
#define LOGITECH_X56_JOYSTICK_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace LogitechX56Joystick
#else
namespace LogitechX56Joystick_
#endif
{
	const QString Description = "Saitek Pro Flight X-56 Rhino Stick";
	
	const uint TG1  = 0;	// Trigger
	const uint A    = 1;
	const uint B    = 2;
	const uint STK  = 3;	// Ministick Click
	const uint D    = 4;	// Pinky Button
	const uint LVR  = 5;	// Pinky Lever
	const uint H1U  = 6;	// Top-Right Hat
	const uint H1R  = 7;
	const uint H1D  = 8;
	const uint H1L  = 9;
	const uint H2U  = 10;	// Bottom-Right Hat
	const uint H2R  = 11;
	const uint H2D  = 12;
	const uint H2L  = 13;
	const uint M1   = 14;	// Mode Switch (Set by Throttle)
	const uint M2   = 15;
	const uint S1   = 16;
	const uint POVU = 17;	// Silver POV Hat
	const uint POVR = 18;
	const uint POVD = 19;
	const uint POVL = 20;
	
	const uint JOYX    = 0;
	const uint JOYY    = 1;
	const uint RUDDER  = 2;
	const uint JOYROTX = 3;
	const uint JOYROTY = 4;
	
	const uint HAT1 = 0;
	const uint HAT2 = 1;
	const uint HAT3 = 2;
};


#endif

