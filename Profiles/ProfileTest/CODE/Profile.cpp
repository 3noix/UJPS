#include "Profile.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoystick.h"
#include "vJoyDevice.h"
#include "WindowsKeys.h"
using namespace Keys;

#include "EnhancedJoystick.h"
#include "ThrustmasterWarthogJoystick.h"
#include "ThrustmasterWarthogThrottle.h"
#include "MfgCrosswindRudderPedals.h"

namespace VJOY = vJoyDevice;
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
	// we retrieve pointers on real joysticks we are interested in
	tmwj = this->registerRealJoystick(TMWJ::Description);
	tmwt = this->registerRealJoystick(TMWT::Description);
	mfgx = this->registerRealJoystick(MFGX::Description);
	
	if (tmwj) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red);}
	
	if (tmwt) {emit message("Warthog throttle detected !",Qt::black);}
	else {emit message("Warthog throttle not detected !",Qt::red);}
	
	if (mfgx) {emit message("MFG Crosswind rudder pedals detected !",Qt::black);}
	else {emit message("MFG Crosswind rudder pedals not detected !",Qt::red);}
	
	if (!tmwj || !tmwt || !mfgx) {return false;}
	
	
	// virtual joystick(s) setup
	vj1 = new VirtualJoystick{1};
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
	//Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonPress{},  new ActionAxisSetValue{vj1,VJOY::Z,0.5f});
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonPress{},  new ActionCallback{[this](){vj1->setAxis(VJOY::Z,0.5f);}});
	
	MapButton(tmwj, TMWJ::H2U, AllLayers, vj1, VJOY::DX49);
	MapButton(tmwj, TMWJ::H2R, AllLayers, vj1, VJOY::DX50);
	MapButton(tmwj, TMWJ::H2D, AllLayers, vj1, VJOY::DX51);
	MapButton(tmwj, TMWJ::H2L, AllLayers, vj1, VJOY::DX52);
	
	Map(tmwj, ControlType::Button, TMWJ::H3L, AllLayers, new TriggerButtonPress{},  new ActionKeyPress{Key_A});
	Map(tmwj, ControlType::Button, TMWJ::H3R, AllLayers, new TriggerButtonPress{},  new ActionKeyRelease{Key_A});
	Map(tmwj, ControlType::Button, TMWJ::H3D, AllLayers, new TriggerButtonChange{}, new ActionKeySetChange{Key_B});
	Map(tmwj, ControlType::Button, TMWJ::H3U, AllLayers, new TriggerButtonPress{},  new ActionKeyPulse{Key_C,0,ms2cycles(200)});
	
	/*
	Map(tmwj, ControlType::Button, TMWJ::H3L, AllLayers, new TriggerButtonPress{},  new ActionKeyPress{0x1C});
	Map(tmwj, ControlType::Button, TMWJ::H3R, AllLayers, new TriggerButtonPress{},  new ActionKeyRelease{0x1C});
	Map(tmwj, ControlType::Button, TMWJ::H3D, AllLayers, new TriggerButtonChange{}, new ActionKeySetChange{0x32});
	Map(tmwj, ControlType::Button, TMWJ::H3U, AllLayers, new TriggerButtonPress{},  new ActionKeyPulse{0x21,0,ms2cycles(200)});
	*/
	
	MapPov(tmwj, TMWJ::HAT1, AllLayers, vj1, VJOY::POV1);
	Map(tmwj, ControlType::Button, TMWJ::S3,  AllLayers, new TriggerButtonPress{},  new ActionPovSetValue{vj1,VJOY::POV1,20.0f});
}


