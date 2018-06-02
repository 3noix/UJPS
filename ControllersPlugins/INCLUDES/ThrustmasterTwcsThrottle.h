#ifndef THRUSTMASTER_TWCS_THROTTLE_
#define THRUSTMASTER_TWCS_THROTTLE_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace ThrustmasterTwcsThrottle
#else
namespace ThrustmasterTwcsThrottle_
#endif
{
	const QString Description = "TWCS Throttle";
	
	const uint TBTN1  = 0;	// instinctive disconnect
	const uint TBTN2  = 1;	// pinky button left
	const uint TBTN3  = 2;	// pinky button right
	const uint TBTN4  = 3;	// slider up
	const uint TBTN5  = 4;	// slider down
	const uint TLOCK  = 5;	// mini-stick pressed
	const uint THAT1U = 6;	// central HAT up
	const uint THAT1R = 7;	// central HAT right
	const uint THAT1D = 8;	// central HAT down
	const uint THAT1L = 9;	// central HAT left
	const uint THAT3U = 10;	// lower HAT 3 up
	const uint THAT3R = 11;	// lower HAT 3 right
	const uint THAT3D = 12;	// lower HAT 3 down
	const uint THAT3L = 13;	// lower HAT 3 left
	const uint THAT2U = 14;	// upper HAT (POV) up
	const uint THAT2R = 15;	// upper HAT (POV) right
	const uint THAT2D = 16;	// upper HAT (POV) down
	const uint THAT2L = 17;	// upper HAT (POV) left
		
	const uint TTHR  = 0;	// throttle axis
	const uint TRDR  = 1;	// rocker axis
	const uint TMSTX = 2;	// mini-stick horizontal axis
	const uint TMSTY = 3;	// mini-stick vertical axis
	const uint TANT  = 4;	// antenna axis
	const uint TFRP1 = 5;	// TFRP unknown axis 1 (TCSRUDDER?)
	const uint TFRP2 = 6;	// TFRP unknown axis 2 (TCSLEFT?)
	const uint TFRP3 = 7;	// TFRP unknown axis 3 (TCSRIGHT?)
};

#endif
