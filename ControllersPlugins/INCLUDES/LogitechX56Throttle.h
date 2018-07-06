#ifndef LOGITECH_X56_THROTTLE_
#define LOGITECH_X56_THROTTLE_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace LogitechX56Throttle
#else
namespace LogitechX56Throttle_
#endif
{
	const QString Description = "Saitek Pro Flight X-56 Rhino Throttle";
	
	const uint E    = 0;
	const uint F    = 1;	// Top Rotary Dial Push
	const uint G    = 2;	// Bottom Rotary Dial Push
	const uint I    = 3;
	const uint H    = 4;
	const uint SW1  = 5;
	const uint SW2  = 6;
	const uint SW3  = 7;
	const uint SW4  = 8;
	const uint SW5  = 9;
	const uint SW6  = 10;
	const uint T1U  = 11;
	const uint T1D  = 12;
	const uint T2U  = 13;
	const uint T2D  = 14;
	const uint T3U  = 15;
	const uint T3D  = 16;
	const uint T4U  = 17;
	const uint T4D  = 18;
	const uint H3U  = 19;	// Upper 4-way Hat
	const uint H3R  = 20;
	const uint H3D  = 21;
	const uint H3L  = 22;
	const uint H4U  = 23;	// Lower 4-way Hat
	const uint H4R  = 24;
	const uint H4D  = 25;
	const uint H4L  = 26;
	const uint K1U  = 27;
	const uint K1D  = 28;
	const uint SFWD = 29;	// Left Side Scroll Wheel
	const uint SBCK = 30;
	const uint STK  = 31;	// Ministick Click
	const uint SLD  = 32;	// Slider
	const uint M1   = 33;	// Throttle Modes
	const uint M2   = 34;
	const uint S1   = 35;
	
	const uint THR_LEFT  = 0;	// Thrust Left Half
	const uint THR_RIGHT = 1;	// Thrust Right Half
	const uint JOYROTX   = 2;	// Ministick X-Axis
	const uint JOYROTY   = 3;	// Ministick Y-Axis
	const uint RTY1      = 4;	// Top Rotary Dial
	const uint RTY2      = 5;	// Bottom Rotary Dial
	const uint RTY3      = 6;	// Rotary Dial 3
	const uint RTY4      = 7;	// Rotary Dial 4
	
	const uint HAT1 = 0;		// Upper 4-way Hat
	const uint HAT2 = 1;		// Lower 4-way Hat
};

#endif
