#ifndef THRUSTMASTER_WARTHOG_THROTTLE_
#define THRUSTMASTER_WARTHOG_THROTTLE_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace ThrustmasterWarthogThrottle
#else
namespace ThrustmasterWarthogThrottle_
#endif
{
	const QString Description = "Throttle - HOTAS Warthog";
	
	const uint SC       = 0;	// slew control
	const uint MSP      = 1;	// MS = micro switch
	const uint MSU      = 2;
	const uint MSR      = 3;
	const uint MSD      = 4;
	const uint MSL      = 5;
	const uint SPDF     = 6;	// speedbrake forward
	const uint SPDB     = 7;	// speedbrake backward
	const uint BSF      = 8;	// boat switch forward
	const uint BSB      = 9;	// boat switch backward
	const uint CHF      = 10;	// china hat forward
	const uint CHB      = 11;	// china hat backward
	const uint PSF      = 12;	// pinky switch forward
	const uint PSB      = 13;	// pinky switch backward
	const uint LTB      = 14;
	const uint EFLNORM  = 15;	// engine left fuel norm
	const uint EFRNORM  = 16;	// engine right fuel norm
	const uint EOLMOTOR = 17;	// engine left oper motor
	const uint EORMOTOR = 18;	// engine right oper motor
	const uint APUON    = 19;	// APU switch
	const uint LDGH     = 20;	// landing gear warning silence
	const uint FLAPU    = 21;	// flaps up
	const uint FLAPD    = 22;	// flapse down
	const uint EACON    = 23;
	const uint RDRNRM   = 24;	// radio altimeter norm
	const uint APENG    = 25;	// engage autopilot
	const uint APATT    = 26;	// autopilot path
	const uint APALT    = 27;	// autopilot ALT
	const uint IDLERON  = 28;	// idle right engine
	const uint IDLELON  = 29;	// idle left engine
	const uint EOLIGN   = 30;	// engine left oper ignition
	const uint EORIGN   = 31;	// engine right oper ignition
		
	const uint CSU      = 32;	// virtual: coolie switch UP
	const uint CSR      = 33;	// virtual: coolie switch RIGHT
	const uint CSD      = 34;	// virtual: coolie switch DOWN
	const uint CSL      = 35;	// virtual: coolie switch LEFT
	const uint EFLOVER  = 36;	// virtual: engine left fuel override
	const uint EFROVER  = 37;	// virtual: engine right fuel override
	const uint APUOFF   = 38;	// virtual
	const uint EACOFF   = 39;	// virutal
	const uint RDRDIS   = 40;	// virtual: radio altimeter disabled
	const uint APDIS    = 41;	// virtual: APENG button not pressed
	const uint IDLEROFF = 42;	// virtual
	const uint IDLELOFF = 43;	// virtual
	const uint EOLNORM  = 44;	// virtual
	const uint EORNORM  = 45;	// virtual
	const uint FLAPM    = 46;	// virtual: flaps middle
	const uint SPDM     = 47;	// virtual: speedbrake middle
	const uint BSM      = 48;	// virtual: boat switch middle
	const uint CHM      = 49;	// virtual: china hat middle
	const uint PSM      = 50;	// virtual: pinky switch middle
	const uint APAH     = 51;	// virtual: autopilot ALT/HDG
		
	const uint THR_LEFT  = 0;	// thrust left lever
	const uint THR_RIGHT = 1;	// thrust right lever
	const uint THR_FC    = 2;	// friction control
	const uint SCX       = 3;	// slew control X
	const uint SCY       = 4;	// slew control Y
};

#endif
