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
	const uint F    = 1;
	const uint G    = 2;
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
	const uint H3U  = 19;
	const uint H3R  = 20;
	const uint H3D  = 21;
	const uint H3L  = 22;
	const uint H4U  = 23;
	const uint H4R  = 24;
	const uint H4D  = 25;
	const uint H4L  = 26;
	const uint K1U  = 27;
	const uint K1D  = 28;
	const uint SFWD = 29;
	const uint SBCK = 30;
	const uint STK  = 31;
	const uint SLD  = 32;
	const uint M1   = 33;
	const uint M2   = 34;
	const uint S1   = 35;
		
	const uint THR_RIGHT = 0;	// Thrust Right Half
	const uint THR_LEFT  = 1;	// Thrust Left Half
	const uint RTY3      = 2;	// Rotary Dial 3
	const uint RTY4      = 3;	// Rotary Dial 4
	const uint JOYROTY   = 4;	// Ministick Y-Axis
	const uint RTY2      = 5;	// Bottom Rotary Dial
	const uint JOYROTX   = 6;	// Ministick X-Axis
	const uint RTY1      = 7;	// Top Rotary Dial
	
	const uint HAT1      = 0;	// Upper 4-way Hat
	const uint HAT2      = 1;	// Lower 4-way Hat
};

#endif
