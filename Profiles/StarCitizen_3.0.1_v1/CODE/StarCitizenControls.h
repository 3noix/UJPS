#ifndef STAR_CITIZEN_CONTROLS
#define STAR_CITIZEN_CONTROLS


#include "vJoyDevice.h"
namespace VJOY = vJoyDevice;
using uint = unsigned int;


namespace StarCitizenControls
{
	/*const uint AxisRoll                  = VJOY::X;
	const uint AxisPitch                 = VJOY::Y;
	const uint AxisThrust                = VJOY::Z;
	const uint AxisStrafeLat             = VJOY::ROTX;
	const uint AxisStrafeLongi           = VJOY::ROTY;
	const uint AxisYaw                   = VJOY::ROTZ;
	const uint AxisStrafeVertical        = VJOY::SLIDER0;*/
	
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
	const uint ESPToggle                 = VJOY::DX17;
	const uint ComstabToggle             = VJOY::DX18;
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
	
	const uint ResetShieldsLevels        = VJOY::DX46;
	const uint ShieldRaiseLeft           = VJOY::DX47;
	const uint ShieldRaiseRight          = VJOY::DX48;
	const uint ShieldRaiseFront          = VJOY::DX49;
	const uint ShieldRaiseBack           = VJOY::DX50;
	const uint ShieldRaiseTop            = VJOY::DX51;
	const uint ShieldRaiseBottom         = VJOY::DX52;
	
	const uint HeadlightsToggle          = VJOY::DX53;
	const uint PersonalIdBroadCastToggle = VJOY::DX54;
	
	const uint TrackIR_Precision         = Key_F13;
	const uint TrackIR_Center            = Key_F14;
	const uint TrackIR_Pause             = Key_F15;
	
	const uint Brake                     = VJOY::DX55;
	const uint Horn                      = VJOY::DX56;
	
	const uint LandingTargetLockOnToggle = VJOY::DX57;
	const uint LaunchMissile             = VJOY::DX58;
}

#endif

