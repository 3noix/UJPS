#include "GameController.h"
#include "GameControllerDirectInput.h"
#include "GameControllerXInput.h"
const uint NB_JOYSTICKS_MAX_DIRECTINPUT = 16;
const uint NB_JOYSTICKS_MAX_XINPUT = 4;


///////////////////////////////////////////////////////////////////////////////
// RESUME
//
//  CONSTRUCTEUR
//  ENUMERATE CONTROLLERS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
GameController::GameController(QObject *parent) : QObject{parent}
{
	
}



// ENUMERATE CONTROLLERS //////////////////////////////////////////////////////
QVector<GameController*> GameController::enumerateControllers(QObject *parent)
{
	QVector<GameController*> controllers;
	
	// search for DirectInput controllers
	for (uint i=0; i<NB_JOYSTICKS_MAX_DIRECTINPUT; ++i)
	{
		GameController *j = new GameControllerDirectInput{i,parent};
		if (j->isValid() && j->description() != "Controller (XBOX 360 For Windows)")
		{
			controllers << j;
		}
		else {delete j;}
	}
	
	// search for XInput controllers
	for (uint i=0; i<NB_JOYSTICKS_MAX_XINPUT; ++i)
	{
		GameController *j = new GameControllerXInput{i,parent};
		if (j->isValid())
		{
			controllers << j;
		}
		else {delete j;}
	}
	
	// the end
	return controllers;
}

