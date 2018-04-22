#ifndef THRUSTMASTER_WARTHOG_JOYSTICK
#define THRUSTMASTER_WARTHOG_JOYSTICK


using uint = unsigned int;


namespace ThrustmasterWarthogJoystick
{
	const uint TG1 = 0;		// trigger stage 1
	const uint S2  = 1;		// Weapon release
	const uint S3  = 2;		// NWS (nose wheel steering)
	const uint S4  = 3;
	const uint S1  = 4;		// MMCB (master mode control button)
	const uint TG2 = 5;		// trigger stage 2
	const uint H2U = 6;		// H2 = TMS
	const uint H2R = 7;
	const uint H2D = 8;
	const uint H2L = 9;
	const uint H3U = 10;	// H3 = DMS
	const uint H3R = 11;
	const uint H3D = 12;
	const uint H3L = 13;
	const uint H4U = 14;	// H4 = CMS
	const uint H4R = 15;
	const uint H4D = 16;
	const uint H4L = 17;
	const uint H4P = 18;
	const uint H1U = 19;	// H1 = Trim switch / POV (4 virtual buttons)
	const uint H1R = 20;
	const uint H1D = 21;
	const uint H1L = 22;
		
	const uint JOYX = 0;
	const uint JOYY = 1;
};

#endif
