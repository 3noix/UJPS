#ifndef THRUSTMASTER_T16000M_JOYSTICK_
#define THRUSTMASTER_T16000M_JOYSTICK_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace ThrustmasterT16000MJoystick
#else
namespace ThrustmasterT16000MJoystick_
#endif
{
	const QString Description = "T.16000M";
	
	const uint TS1   = 0;	// trigger button
	const uint TS2   = 1;	// stick top middle button
	const uint TS3   = 2;	// stick top left button
	const uint TS4   = 3;	// stick top right button
	
	const uint B5    = 4;	// base left top outer button
	const uint B6    = 5;	// base left top middle button
	const uint B7    = 6;	// base left top inner button
	const uint B8    = 7;	// base left bottom inner button
	const uint B9    = 8;	// base left bottom middle button
	const uint B10   = 9;	// base left bottom outer button
	
	const uint B11   = 10;	// base right top outer button
	const uint B12   = 11;	// base right top middle button
	const uint B13   = 12;	// base right top inner button
	const uint B14   = 13;	// base right bottom inner button
	const uint B15   = 14;	// base right bottom middle button
	const uint B16   = 15;	// base right bottom outer button
	
	const uint H1U   = 16;	// POV button up
	const uint H1R   = 17;	// POV button right
	const uint H1D   = 18;	// POV button down
	const uint H1L   = 19;	// POV button left
	
	const uint JOYX   = 0;	// X stick axis
	const uint JOYY   = 1;	// Y stick axis
	const uint RUDDER = 2;	// twist stick axis
	const uint THR    = 3;	// throttle slider axis
};

#endif
