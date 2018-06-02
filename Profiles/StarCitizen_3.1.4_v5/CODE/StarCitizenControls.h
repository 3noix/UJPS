#ifndef STAR_CITIZEN_CONTROLS
#define STAR_CITIZEN_CONTROLS


#include "vJoyDevice.h"
namespace VJOY = vJoyDevice;
using uint = unsigned int;


namespace StarCitizenControls_Keyboard
{
	const uint TrackIR_Precision = Key_F13;
	const uint TrackIR_Center    = Key_F14;
	const uint TrackIR_Pause     = Key_F15;
}

namespace StarCitizenControls_vJoy1
{
	const uint AxisFlightRoll            = VJOY::X;
	const uint AxisFlightPitch           = VJOY::Y;
	const uint AxisFlightYaw             = VJOY::Z;
	const uint AxisFlightStrafeLongi     = VJOY::ROTX;
	const uint AxisFlightStrafeLat       = VJOY::ROTY;
	const uint AxisFlightStrafeVertical  = VJOY::ROTZ;
	const uint AxisFlightThrust          = VJOY::SLIDER0;
	
	const uint LandingSystemToggle       = VJOY::DX1;
	const uint IncreasePower             = VJOY::DX2;
	const uint DecreasePower             = VJOY::DX3;
	const uint CycleAmmoBack             = VJOY::DX4;
	const uint CycleAmmo                 = VJOY::DX5;
	const uint CycleRadarRange           = VJOY::DX6;
	const uint Afterburner               = VJOY::DX7;
	const uint Boost                     = VJOY::DX8;
	const uint SpaceBrake                = VJOY::DX9;
	const uint DecoupledModeToggle       = VJOY::DX10;
	const uint Autoland                  = VJOY::DX11;
	const uint QuantumDriveToggle        = VJOY::DX12;
	const uint SwapYawRollToggle         = VJOY::DX13;
	const uint FireGroup1                = VJOY::DX14;
	const uint FireGroup2                = VJOY::DX15;
	const uint GForceSafetyToggle        = VJOY::DX16;
	const uint ComstabToggle             = VJOY::DX17;
	const uint ESPToggle                 = VJOY::DX18;
	const uint LookBehind                = VJOY::DX19;
	
	const uint CycleCounterMeasures      = VJOY::DX20;
	const uint LaunchCounterMeasures     = VJOY::DX21;
	
	const uint StrafeLeft                = VJOY::DX22;
	const uint StrafeRight               = VJOY::DX23;
	const uint StrafeUp                  = VJOY::DX24;
	const uint StrafeDown                = VJOY::DX25;
	const uint StrafeForward             = VJOY::DX26;
	const uint StrafeBackwards           = VJOY::DX27;
	
	const uint CycleHostileTargets       = VJOY::DX28;
	const uint CycleHostileTargetsBack   = VJOY::DX29;
	const uint CycleAllTargets           = VJOY::DX30;
	const uint CycleAllTargetsBack       = VJOY::DX31;
	const uint CycleFriendlyTargets      = VJOY::DX32;
	const uint CycleFriendlyTargetsBack  = VJOY::DX33;
	const uint CyclePinnedTargets        = VJOY::DX34;
	const uint CyclePinnedTargetsBack    = VJOY::DX35;
	const uint PinFocusedTarget          = VJOY::DX36;
	const uint TargetNearestHostile      = VJOY::DX37;
	const uint AcquireMissileLock        = VJOY::DX38;
	
	const uint PowerPreset1Toggle        = VJOY::DX39;
	const uint PowerPreset2Toggle        = VJOY::DX40;
	const uint PowerPreset3Toggle        = VJOY::DX41;
	const uint PowerPreset1Increase      = VJOY::DX42;
	const uint PowerPreset2Increase      = VJOY::DX43;
	const uint PowerPreset3Increase      = VJOY::DX44;
	const uint ResetPowerDistribution    = VJOY::DX45;
	
	const uint HeadlightsToggle          = VJOY::DX46;
	const uint PersonalIdBroadCastToggle = VJOY::DX47;
	const uint LandingTargetLockOnToggle = VJOY::DX48;
	const uint LaunchMissile             = VJOY::DX49;
	const uint MatchTargetVelocity       = VJOY::DX50;
}

namespace StarCitizenControls_vJoy2
{
	const uint AxisGroundThrust   = VJOY::X;
	const uint AxisGroundLat      = VJOY::Y;
	
	const uint ResetShieldsLevels = VJOY::DX1;
	const uint ShieldRaiseLeft    = VJOY::DX2;
	const uint ShieldRaiseRight   = VJOY::DX3;
	const uint ShieldRaiseFront   = VJOY::DX4;
	const uint ShieldRaiseBack    = VJOY::DX5;
	const uint ShieldRaiseTop     = VJOY::DX6;
	const uint ShieldRaiseBottom  = VJOY::DX7;
	
	const uint FlightReady        = VJOY::DX8;
	const uint PowerOff           = VJOY::DX9;
	
	const uint Brake              = VJOY::DX30;
	const uint Horn               = VJOY::DX31;
}

#endif

