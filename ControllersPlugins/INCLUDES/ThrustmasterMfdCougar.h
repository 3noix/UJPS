#ifndef THRUSTMASTER_MFD_COUGAR_
#define THRUSTMASTER_MFD_COUGAR_


#include <QString>
using uint = unsigned int;


#ifndef INSIDE_PLUGIN
namespace ThrustmasterMfdCougar
#else
namespace ThrustmasterMfdCougar_
#endif
{
	const QString Description1 = "F16 MFD 1";
	const QString Description2 = "F16 MFD 2";
	
	const uint OSB1  = 0;
	const uint OSB2  = 1;
	const uint OSB3  = 2;
	const uint OSB4  = 3;
	const uint OSB5  = 4;
	const uint OSB6  = 5;
	const uint OSB7  = 6;
	const uint OSB8  = 7;
	const uint OSB9  = 8;
	const uint OSB10 = 9;
	const uint OSB11 = 10;
	const uint OSB12 = 11;
	const uint OSB13 = 12;
	const uint OSB14 = 13;
	const uint OSB15 = 14;
	const uint OSB16 = 15;
	const uint OSB17 = 16;
	const uint OSB18 = 17;
	const uint OSB19 = 18;
	const uint OSB20 = 19;
	
	const uint SYMU  = 20;
	const uint SYMD  = 21;
	const uint CONU  = 22;
	const uint COND  = 23;
	const uint BRTU  = 24;
	const uint BRTD  = 25;
	const uint GAINU = 26;
	const uint GAIND = 27;
};


#endif

