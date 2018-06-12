#ifndef LOGITECH_EXTREME_3D_
#define LOGITECH_EXTREME_3D_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace LogitechExtreme3D
#else
namespace LogitechExtreme3D_
#endif
{
	const QString Description = "Logitech Extreme 3D";
	
	const uint TG    = 0;	// trigger
	const uint THMB  = 1;	// thumb button
	const uint SBDL  = 2;	// stick button down left
	const uint SBDR  = 3;	// stick button down right
	const uint SBUL  = 4;	// stick button up left
	const uint SBUR  = 5;	// stick button up right
	const uint BBUL  = 6;	// base button up left
	const uint BBUR  = 7;	// base button up right
	const uint BBML  = 8;	// base button middle left
	const uint BBMR  = 9;	// base button middle right
	const uint BBDL  = 10;	// base button down left
	const uint BBDR  = 11;	// base button down right
	const uint POVU  = 12;	// POV button up
	const uint POVR  = 13;	// POV button right
	const uint POVD  = 14;	// POV button down
	const uint POVL  = 15;	// POV button left
		
	const uint JOYX = 0;	// X stick axis
	const uint JOYY = 1;	// Y stick axis
	const uint JOYZ = 2;	// Z stick axis
	const uint THR  = 3;	// throttle axis
	
	const uint POV1 = 0;	// the only pov
};

#endif
