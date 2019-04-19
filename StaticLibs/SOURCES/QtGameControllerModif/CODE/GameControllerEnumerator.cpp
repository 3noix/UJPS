#include "GameControllerEnumerator.h"
#include "GameControllerDirectInput.h"
#include "GameControllerXInput.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME
//
//  ENUMERATE CONTROLLERS
//
//  CONSTRUCTEUR
//  RESET
//  NEXT CONTROLLER
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




// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
GameControllerEnumerator::GameControllerEnumerator()
{
	this->reset();
}

// RESET //////////////////////////////////////////////////////////////////////
void GameControllerEnumerator::reset()
{
	m_indexDirectInput = 0;
	m_indexXInput = 0;
}

// NEXT CONTROLLER ////////////////////////////////////////////////////////////
GameController* GameControllerEnumerator::nextController(QObject *parent)
{
	// init
	bool bLookIntoDirectInput = (m_indexDirectInput < NB_JOYSTICKS_MAX_DIRECTINPUT);
	bool bLookIntoXInput = (bUseXInput && m_indexXInput < NB_JOYSTICKS_MAX_XINPUT);
	
	// search for DirectInput controllers
	if (bLookIntoDirectInput)
	{
		for (uint i=m_indexDirectInput; i<NB_JOYSTICKS_MAX_DIRECTINPUT; ++i)
		{
			GameController *j = new GameControllerDirectInput{i,parent};
			bool bIgnore = (bUseXInput && j->description() == "Controller (XBOX 360 For Windows)");
			++m_indexDirectInput;
			
			if (j->isValid() && !bIgnore) {return j;}
			else {delete j;}
		}
	}
	
	// search for XInput controllers
	if (bLookIntoXInput)
	{
		for (uint i=m_indexXInput; i<NB_JOYSTICKS_MAX_XINPUT; ++i)
		{
			GameController *j = new GameControllerXInput{i,parent};
			++m_indexXInput;
			
			if (j->isValid()) {return j;}
			else {delete j;}
		}
	}
	
	// if finished
	return nullptr;
}

