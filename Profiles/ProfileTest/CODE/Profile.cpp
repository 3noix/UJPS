#include "Profile.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoystick.h"
#include "WindowsKeys.h"
using namespace Keys;

#include "EnhancedJoystick.h"
#include "ThrustmasterWarthogJoystick.h"
#include "ThrustmasterWarthogThrottle.h"
#include "MfgCrosswindRudderPedals.h"

using VJOY = VirtualJoystick;
namespace TMWJ = ThrustmasterWarthogJoystick;
namespace TMWT = ThrustmasterWarthogThrottle;
namespace MFGX = MfgCrosswindRudderPedals;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  STOP
//  SETUP JOYSTICKS
//  RUN FIRST STEP
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
Profile::Profile() : AbstractProfile()
{
	tmwj = nullptr;
	tmwt = nullptr;
	mfgx = nullptr;
	vj1  = nullptr;
}

Profile::~Profile()
{
	this->stop();
}








// STOP ///////////////////////////////////////////////////////////////////////
void Profile::stop()
{
	// UnmapAll, delete real and virtual joysticks
	this->AbstractProfile::stop();
	
	// it is a good idea to set them to nullptr
	tmwj = nullptr;
	tmwt = nullptr;
	mfgx = nullptr;
	vj1  = nullptr;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	// we allocate the RealJoysticksManager on the heap, because otherwise it will
	// crash at the second call of setupJoysticks... maybe because of pointer global variable
	// in the QtControllerModif lib (cf line 25 of qgamecontroller_win.cpp)
	
	// we retrieve pointers on real joysticks we are interested in
	tmwj = this->registerRealJoystick("Joystick - HOTAS Warthog");
	tmwt = this->registerRealJoystick("Throttle - HOTAS Warthog");
	mfgx = this->registerRealJoystick("MFG Crosswind V2");
	
	if (tmwj) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red);}
	
	if (tmwt) {emit message("Warthog throttle detected !",Qt::black);}
	else {emit message("Warthog throttle not detected !",Qt::red);}
	
	if (mfgx) {emit message("MFG Crosswind rudder pedals detected !",Qt::black);}
	else {emit message("MFG Crosswind rudder pedals not detected !",Qt::red);}
	
	if (!tmwj || !tmwt || !mfgx) {return false;}
	
	
	// virtual joystick(s) setup
	vj1 = new VirtualJoystick(1,128);
	QObject::connect(vj1,&VirtualJoystick::message,this,&Profile::message);
	emit message("Virtual joystick 1 configured",Qt::black);
	this->registerVirtualJoystick(vj1);
	
	
	return (tmwj && tmwt && mfgx && vj1);
}

// RUN FIRST STEP /////////////////////////////////////////////////////////////
void Profile::runFirstStep()
{
	vj1->resetReport();
	
	MapAxis(mfgx, MFGX::RUDDER, AllLayers, vj1, VJOY::X);
	MapMergeAxes(mfgx, MFGX::BRK_LEFT, 0.5f, mfgx, MFGX::BRK_RIGHT, -0.5f, AllLayers, vj1, VJOY::Y);
	
	MapAxisRelative(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::Z, 4000.0f);
}


