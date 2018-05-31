#ifndef MFG_CROSSWIND_RUDDER_PEDALS_
#define MFG_CROSSWIND_RUDDER_PEDALS_


using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace MfgCrosswindRudderPedals
#else
namespace MfgCrosswindRudderPedals_
#endif
{
	const uint RUDDER    = 0;
	const uint BRK_LEFT  = 1;
	const uint BRK_RIGHT = 2;
};

#endif
