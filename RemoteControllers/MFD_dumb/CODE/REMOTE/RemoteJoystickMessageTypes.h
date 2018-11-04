#ifndef REMOTE_JOYSTICK_MESSAGE_TYPES
#define REMOTE_JOYSTICK_MESSAGE_TYPES


#include <QtGlobal>
namespace RemoteJoystickMessageType
{
	const quint8 Invalid = 0;
	const quint8 Init = 1;		// a QString, 2 quint8 and 2 QStringList
	const quint8 Button = 2;	// a quint8 and a bool
	const quint8 Axis = 3;		// a quint8 and a float
	const quint8 Pov = 4;		// a quint8 and a float
};


#endif

