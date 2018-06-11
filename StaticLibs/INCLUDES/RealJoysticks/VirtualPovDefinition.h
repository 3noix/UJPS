#ifndef VIRTUAL_POV_DEFINITION
#define VIRTUAL_POV_DEFINITION


#include <QString>
using uint = unsigned int;


struct VirtualPovDefinition
{
	uint buttonUp;
	uint buttonRight;
	uint buttonDown;
	uint buttonLeft;
	QString povName;
};


#endif


