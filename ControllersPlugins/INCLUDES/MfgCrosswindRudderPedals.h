#ifndef MFG_CROSSWIND_RUDDER_PEDALS_
#define MFG_CROSSWIND_RUDDER_PEDALS_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace MfgCrosswindRudderPedals
#else
namespace MfgCrosswindRudderPedals_
#endif
{
	const QString Description = "MFG Crosswind V2";
	
	const uint RUDDER    = 0;
	const uint BRK_LEFT  = 1;
	const uint BRK_RIGHT = 2;
};


#endif

