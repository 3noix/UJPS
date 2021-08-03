#ifndef STAR_CITIZEN_CONTROLS
#define STAR_CITIZEN_CONTROLS


#include "vJoyDevice.h"
#include "UjpsCore/WindowsKeys.h"

namespace VJOY = vJoyDevice;
using namespace Keys;
using uint = unsigned int;


namespace StarCitizenControls_Keyboard
{
	const uint TrackIR_Precision = Key_F7;
	const uint TrackIR_Pause     = Key_F8;
	const uint TrackIR_Center    = Key_F9;
}


namespace StarCitizenControls_vJoy1
{
	// axes flight controls
	const uint AxisFlightRoll            = VJOY::X;
	const uint AxisFlightPitch           = VJOY::Y;
	const uint AxisFlightYaw             = VJOY::Z;
	const uint AxisFlightThrottle        = VJOY::ROTX;
	const uint AxisFlightStrafeLat       = VJOY::ROTY;
	const uint AxisFlightStrafeVertical  = VJOY::ROTZ;
	const uint AxisFlightSpeedLimit      = VJOY::SLIDER0;
	const uint AxisFlightThrLimit        = VJOY::SLIDER1;
	
	// buttons flight controls
	const uint Afterburner               = VJOY::DX1;
	const uint SpaceBrake                = VJOY::DX2;
	const uint DecoupledModeToggle       = VJOY::DX3;
	const uint Autoland                  = VJOY::DX4;
	const uint LandingSystemToggle       = VJOY::DX5;
	const uint QuantumTravelSystemToggle = VJOY::DX6;
	const uint QuantumDrive              = VJOY::DX7;
	const uint GForceSafetyToggle        = VJOY::DX8;
	const uint MatchTargetVelocity       = VJOY::DX9;
	const uint ESPToggle                 = VJOY::DX10;
	const uint SpeedLimiterToggle        = VJOY::DX11;
	const uint CruiseControlToggle       = VJOY::DX12;
	
	// targeting
	const uint CycleHostileTargets      = VJOY::DX16;
	const uint CycleHostileTargetsBack  = VJOY::DX17;
	const uint CycleAllTargets          = VJOY::DX18;
	const uint CycleAllTargetsBack      = VJOY::DX19;
	const uint CycleFriendlyTargets     = VJOY::DX20;
	const uint CycleFriendlyTargetsBack = VJOY::DX21;
	const uint CyclePinnedTargets       = VJOY::DX22;
	const uint CyclePinnedTargetsBack   = VJOY::DX23;
	const uint PinFocusedTarget         = VJOY::DX24;
	const uint TargetNearestHostile     = VJOY::DX25;
	const uint ReticleFocus             = VJOY::DX26;
	
	// power
	const uint FlightReady            = VJOY::DX29;
	const uint PowerOff               = VJOY::DX30;
	const uint IncreasePower          = VJOY::DX31;
	const uint DecreasePower          = VJOY::DX32;
	const uint PowerPreset1Toggle     = VJOY::DX33;
	const uint PowerPreset2Toggle     = VJOY::DX34;
	const uint PowerPreset3Toggle     = VJOY::DX35;
	const uint PowerPreset1Increase   = VJOY::DX36;
	const uint PowerPreset2Increase   = VJOY::DX37;
	const uint PowerPreset3Increase   = VJOY::DX38;
	const uint ResetPowerDistribution = VJOY::DX39;
	
	// weapons
	const uint FireGroup1         = VJOY::DX43;
	const uint FireGroup2         = VJOY::DX44;
	const uint FireGroup3         = VJOY::DX45;
	const uint AcquireMissileLock = VJOY::DX46;
	const uint LaunchMissile      = VJOY::DX47;
	const uint CycleGimbalMode    = VJOY::DX48;
	const uint UnlockMissile      = VJOY::DX49;
}


namespace StarCitizenControls_vJoy2
{
	// ground
	const uint AxisGroundThrottle = VJOY::X;
	const uint AxisGroundLat      = VJOY::Y;
	
	const uint Brake = VJOY::DX1;
	const uint Horn  = VJOY::DX2;
	
	// shields and counter-measures
	const uint CycleCounterMeasures  = VJOY::DX10;
	const uint LaunchCounterMeasures = VJOY::DX11;
	const uint ShieldRaiseLeft       = VJOY::DX12;
	const uint ShieldRaiseRight      = VJOY::DX13;
	const uint ShieldRaiseFront      = VJOY::DX14;
	const uint ShieldRaiseBack       = VJOY::DX15;
	const uint ShieldRaiseTop        = VJOY::DX16;
	const uint ShieldRaiseBottom     = VJOY::DX17;
	const uint ResetShieldsLevels    = VJOY::DX18;
	
	// scanning / radar
	const uint CycleRadarRange       = VJOY::DX22;
	const uint ScanningModeToggle    = VJOY::DX23;
	const uint ScanningRadarPing     = VJOY::DX24;
	const uint ActivateScanning      = VJOY::DX25;
	const uint ScanningIncRadarAngle = VJOY::DX26;
	const uint ScanningDecRadarAngle = VJOY::DX27;
	
	// comms
	const uint PushToTalk = VJOY::DX30;
	const uint HailTarget = VJOY::DX31;
	
	// view
	const uint ZoomIn     = VJOY::DX35;
	const uint ZoomOut    = VJOY::DX36;
	const uint LookBehind = VJOY::DX37;
	
	// other
	const uint HeadlightsToggle          = VJOY::DX41;
	const uint PersonalIdBroadCastToggle = VJOY::DX42;
}


#endif

