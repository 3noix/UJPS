#ifndef MFD_CONTROLS
#define MFD_CONTROLS


using uint = unsigned int;


namespace MfdControls
{
	const QStringList controlsNames
	{
		"PowerPreset1Increase",
		"PowerPreset2Increase",
		"PowerPreset3Increase",
		"ResetPowerDistribution",
		"PowerPreset1OnOff",
		"PowerPreset2OnOff",
		"PowerPreset3OnOff",
		"PowerOnOff",
		
		"MatchTargetVelocity",
		"GForceSafetyToggle",
		"ComStabToggle",
		"ESPToggle",
		"LandingGearToggle",
		"Autoland",
		"QuantumDriveToggle",
		
		"FlightReady",
		"OpenAllDoors",
		"CloseAllDoors",
		"LockAllDoors",
		"UnlockAllDoors",
		"HeadLightsToggle"
	};
	
	// power
	const uint PowerPreset1Increase   = 0;
	const uint PowerPreset2Increase   = 1;
	const uint PowerPreset3Increase   = 2;
	const uint ResetPowerDistribution = 3;
	const uint PowerPreset1OnOff      = 4;
	const uint PowerPreset2OnOff      = 5;
	const uint PowerPreset3OnOff      = 6;
	const uint PowerOnOff             = 7;
	
	// IFCS
	const uint GForceSafetyToggle  = 8;
	const uint ComStabToggle       = 9;
	const uint EspToggle           = 10;
	const uint MatchTargetVelocity = 11;
	const uint LandingGearToggle   = 12;
	const uint Autoland            = 13;
	const uint QuantumDriveToggle  = 14;
	
	// SYS
	const uint FlightReady      = 15;
	const uint HeadLightsToggle = 16;
	const uint OpenAllDoors     = 17;
	const uint CloseAllDoors    = 18;
	const uint LockAllDoors     = 19;
	const uint UnlockAllDoors   = 20;
};


#endif

