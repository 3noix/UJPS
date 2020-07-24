#ifndef CONTROLS
#define CONTROLS


#include "vJoyDevice.h"

namespace VJOY = vJoyDevice;
using uint = unsigned int;



namespace Controls
{
	// axes flight controls
	const uint AxisRoll     = VJOY::X;
	const uint AxisPitch    = VJOY::Y;
	const uint AxisYaw      = VJOY::Z;
	const uint AxisThrottle = VJOY::ROTX;
	
	// buttons flight controls
	const uint LandingGear = VJOY::DX1;
	const uint Spoilers    = VJOY::DX2;
	const uint Autothrust  = VJOY::DX3;
	const uint Autopilot   = VJOY::DX4;
}


#endif

