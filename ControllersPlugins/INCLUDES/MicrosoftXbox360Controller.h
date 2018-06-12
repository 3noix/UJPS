#ifndef MICROSOFT_XBOX360_CONTROLLER_
#define MICROSOFT_XBOX360_CONTROLLER_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace MicrosoftXbox360Controller
#else
namespace MicrosoftXbox360Controller_
#endif
{
	const QString Description = "Controller (XBOX 360 For Windows)";
	
	const uint BA = 0;			// button A
	const uint BB = 1;			// button B
	const uint BX = 2;			// button X
	const uint BY = 3;			// button Y
	const uint SHOULDERL = 4;	// left shoulder button
	const uint SHOULDERR = 5;	// right shoulder button
	const uint BACK  = 6;		// back button
	const uint START = 7;		// start button
	const uint THUMBL = 8;		// left stick button
	const uint THUMBR = 9;		// right stick button
	const uint DPADU = 10;		// D-Pad up (POV up)
	const uint DPADR = 11;		// D-Pad right (POV right)
	const uint DPADD = 12;		// D-Pad down (POV down)
	const uint DPADL = 13;		// D-Pad left (POV left)

	const uint THUMBLX = 0;		// left stick X axis
	const uint THUMBLY = 1;		// left stick Y axis
	const uint THUMBRX = 2;		// right stick X axis
	const uint THUMBRY = 3;		// right stick Y axis
	const uint TRIGGER = 4;		// left and right trigger axes (merged in one)
	
	const uint DPAD = 0;		// the only pov
};

#endif
