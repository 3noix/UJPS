#ifndef MICROSOFT_XBOX360_GAMEPAD_
#define MICROSOFT_XBOX360_GAMEPAD_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace MicrosoftXbox360Gamepad
#else
namespace MicrosoftXbox360Gamepad_
#endif
{
	const QString Description = "Controller (XBOX 360 For Windows)";
	
	const uint DPADU = 0;		// D-Pad up (POV up)
	const uint DPADR = 1;		// D-Pad right (POV right)
	const uint DPADD = 2;		// D-Pad down (POV down)
	const uint DPADL = 3;		// D-Pad left (POV left)
	const uint START = 4;		// start button
	const uint BACK  = 5;		// back button
	const uint THUMBL = 6;		// left stick button
	const uint THUMBR = 7;		// right stick button
	const uint SHOULDERL = 8;	// left shoulder button
	const uint SHOULDERR = 9;	// right shoulder button
	const uint BA = 10;			// button A
	const uint BB = 11;			// button B
	const uint BX = 12;			// button X
	const uint BY = 13;			// button Y

	const uint TRIGGERL = 0;		// left trigger axis
	const uint TRIGGERR = 1;		// right trigger axis
	const uint THUMBLX  = 2;		// left stick X axis
	const uint THUMBLY  = 3;		// left stick Y axis
	const uint THUMBRX  = 4;		// right stick X axis
	const uint THUMBRY  = 5;		// right stick Y axis
	
	const uint DPAD = 0;		// the only pov (and virtual... for XInput)
};


#endif

