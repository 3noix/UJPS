#include "Profile.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoystick.h"
#include "WindowsKeys.h"
using namespace Keys;

#include "REAL_JOYSTICKS/RealJoysticksManager.h"
#include "REAL_JOYSTICKS/EnhancedJoystick.h"
#include "REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogJoystick.h"
#include "REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogThrottle.h"
#include "REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/MfgCrosswindRudderPedals.h"

using VJOY = VirtualJoystick;
using TMWJ = WarthogJoystick;
using TMWT = WarthogThrottle;
using MFGX = MfgCrosswindRudderPedals;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  PLAY
//  STOP
//  SETUP JOYSTICKS
//  INIT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
Profile::Profile() : AbstractProfile()
{
	rjm  = nullptr;
	mfgx = nullptr;
	vj1  = nullptr;
}

Profile::~Profile()
{
	this->stop();
	if (rjm) {delete rjm; rjm = nullptr;}
}






// PLAY ///////////////////////////////////////////////////////////////////////
bool Profile::play()
{
	if (!this->setupJoysticks()) {return false;}
	this->init();
	return true;
}

// STOP ///////////////////////////////////////////////////////////////////////
bool Profile::stop()
{
	if (mfgx) {delete mfgx; mfgx = nullptr;}
	if (vj1)  {delete vj1;  vj1  = nullptr;}
	return true;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	// we allocate the RealJoysticksManager on the heap, because otherwise it will
	// crash at the second call of setupJoysticks... maybe because of pointer global variable
	// in the QtControllerModif lib (cf line 25 of qgamecontroller_win.cpp)
	
	// we retrieve pointers on real joysticks we are interested in
	if (!rjm) {rjm = new RealJoysticksManager{};}
	AbstractRealJoystick *rj = rjm->joystick("MFG Crosswind V2");
	if (!rj)
	{
		emit message("MFG Crosswind rudder pedals not detected !",Qt::red);
		return false;
	}
	
	emit message("MFG Crosswind rudder pedals detected !",Qt::black);
	mfgx = new EnhancedJoystick(rj,false);
	this->registerRealJoystick(mfgx);
	
	
	// virtual joystick(s) setup
	vj1 = new VirtualJoystick(1,128);
	QObject::connect(vj1,&VirtualJoystick::message,this,&Profile::message);
	emit message("Virtual joystick 1 configured",Qt::black);
	this->registerVirtualJoystick(vj1);
	
	
	return (mfgx && vj1);
}

// INIT ///////////////////////////////////////////////////////////////////////
void Profile::init()
{
	vj1->resetReport();
	
	MapAxis(mfgx, MFGX::RUDDER, AllLayers, vj1, VJOY::X);
	MapMergeAxes(mfgx, MFGX::BRK_LEFT, 0.5f, mfgx, MFGX::BRK_RIGHT, -0.5f, AllLayers, vj1, VJOY::Y);
}


