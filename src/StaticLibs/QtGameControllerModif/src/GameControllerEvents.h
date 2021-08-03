#ifndef GAME_CONTROLLER_EVENTS
#define GAME_CONTROLLER_EVENTS


using uint = unsigned int;


struct GameControllerAxisEvent
{
	uint controllerId;
	uint axis;
	float value;
};


struct GameControllerButtonEvent
{
	uint controllerId;
	uint button;
	bool pressed;
};


struct GameControllerPovEvent
{
	uint controllerId;
	uint pov;
	float angle;
};


#include <QMetaType>
Q_DECLARE_METATYPE(GameControllerAxisEvent);
Q_DECLARE_METATYPE(GameControllerButtonEvent);
Q_DECLARE_METATYPE(GameControllerPovEvent);


#endif

