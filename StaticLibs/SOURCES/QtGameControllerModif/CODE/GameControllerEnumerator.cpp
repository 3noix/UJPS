#include "GameControllerEnumerator.h"
#include "GameControllerDirectInput.h"
#include "GameControllerXInput.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME
//
//  ENUMERATE CONTROLLERS
///////////////////////////////////////////////////////////////////////////////


// ENUMERATE CONTROLLERS //////////////////////////////////////////////////////
QVector<GameController*> GameControllerEnumerator::enumerateControllers(QObject *parent)
{
	QVector<GameController*> controllers;
	
	// search for DirectInput controllers
	for (uint i=0; i<NB_JOYSTICKS_MAX_DIRECTINPUT; ++i)
	{
		GameController *j = new GameControllerDirectInput{i,parent};
		bool bIgnore = (bUseXInput && j->description() == "Controller (XBOX 360 For Windows)");
		if (j->isValid() && !bIgnore) {controllers << j;}
		else {delete j;}
	}
	
	// search for XInput controllers
	if (bUseXInput)
	{
		for (uint i=0; i<NB_JOYSTICKS_MAX_XINPUT; ++i)
		{
			GameController *j = new GameControllerXInput{i,parent};
			if (j->isValid()) {controllers << j;}
			else {delete j;}
		}
	}
	
	// the end
	return controllers;
}

