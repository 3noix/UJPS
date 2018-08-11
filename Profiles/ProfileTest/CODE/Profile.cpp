#include "Profile.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
#include "CURVES/CurveExpNotCentered.h"
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
	delete actionTestRexec;
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
	
	vj2 = new VirtualJoystick{2};
	emit message("Virtual joystick 2 configured",Qt::black);
	this->registerVirtualJoystick(vj2);
	
	
	return (tmwj && tmwt && mfgx && vj1 && vj2);
}

// RUN FIRST STEP /////////////////////////////////////////////////////////////
void Profile::runFirstStep()
{
	vj1->resetReport();
	//tmwt->setData("BRIGHTNESS",1);
	tmwt->setData("BRIGHTNESS",0);
	tmwt->setData("BACKLIT",true);
	tmwt->flush();
	
	
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonChange{}, new ActionKeySetChange{Key_N});
	
	actionTestRexec = new ActionButtonPulse{vj2,VJOY::DX1,ms2cycles(100)};
	Map(tmwj, ControlType::Button, TMWJ::H2L, AllLayers, new TriggerButtonPress{},  new ActionSequence{{
		new ActionCallback{[this](){this->startRexec(0,ms2cycles(1000),actionTestRexec);}},
		new ActionCallback{[this](){this->stopRexec(0);}}
	}});
	
	auto sendMessage = [this](){emit message("Test Rexec",Qt::cyan);};
	Map(tmwj, ControlType::Button, TMWJ::H2R, AllLayers, new TriggerButtonPress{},  new ActionSequence{{
		new ActionCallback{[this,sendMessage](){this->startRexec(1,ms2cycles(1000),sendMessage);}},
		new ActionCallback{[this](){this->stopRexec(1);}}
	}});
	
	Map(tmwj, ControlType::Button, TMWJ::H3L, AllLayers, new TriggerButtonPress{},  new ActionKeyPress{Key_A});
	Map(tmwj, ControlType::Button, TMWJ::H3R, AllLayers, new TriggerButtonPress{},  new ActionKeyRelease{Key_A});
	Map(tmwj, ControlType::Button, TMWJ::H3D, AllLayers, new TriggerButtonChange{}, new ActionKeySetChange{Key_B});
	Map(tmwj, ControlType::Button, TMWJ::H3U, AllLayers, new TriggerButtonPress{},  new ActionKeyPulse{Key_C,0,ms2cycles(200)});
	
	/*
	this->registerLayerDim2(Layers::Down,   tmwt, TMWT::BSB);
	this->registerLayerDim2(Layers::Middle, tmwt, TMWT::BSM);
	this->registerLayerDim2(Layers::Up,     tmwt, TMWT::BSF);
	MapButton(tmwj, TMWJ::TG1, {"d"}, vj1, VJOY::DX1);
	MapButton(tmwj, TMWJ::TG1, {"m"}, vj1, VJOY::DX2);
	MapButton(tmwj, TMWJ::TG1, {"u"}, vj1, VJOY::DX3);
	vj1->setButton(VJOY::DX1, tmwj->buttonPressed(TMWJ::TG1) && tmwt->buttonPressed(TMWT::BSB));
	vj1->setButton(VJOY::DX2, tmwj->buttonPressed(TMWJ::TG1) && tmwt->buttonPressed(TMWT::BSM));
	vj1->setButton(VJOY::DX3, tmwj->buttonPressed(TMWJ::TG1) && tmwt->buttonPressed(TMWT::BSF));
	*/
	/*
	MapAxis(mfgx, MFGX::RUDDER, AllLayers, vj1, VJOY::X);
	//mfgx->setCurve(MFGX::BRK_LEFT, new CurveExpNotCentered{0.0f,5.0f,3.0f,0.0f});
	//mfgx->setCurve(MFGX::BRK_RIGHT, new CurveExpNotCentered{0.0f,5.0f,3.0f,0.0f});
	MapMergeAxes(mfgx, MFGX::BRK_LEFT, 0.5f, mfgx, MFGX::BRK_RIGHT, -0.5f, AllLayers, vj1, VJOY::Y, new CurveExpNotCentered{0.0f,5.0f,3.0f,0.0f});
	*/
	
	MapSplitAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::ROTX, vj1, VJOY::ROTY);
	
	/*
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, VJOY::ROTX);
	MapAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::ROTY);
	Map(tmwj, ControlType::Button, TMWJ::H2L, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this](){tmwj->rotateAxes(TMWJ::JOYX, TMWJ::JOYY, 45.0);}});
	Map(tmwj, ControlType::Button, TMWJ::H2R, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this](){tmwj->removeAxisRotation(TMWJ::JOYX);}});
	*/
	
	MapAxisRelative(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::Z, 4000.0f);
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonPress{},  new ActionAxisSetValue{vj1,VJOY::Z,0.5f});
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonPress{},  new ActionCallback{[this](){vj1->setAxis(VJOY::Z,0.5f);}});
	
	/*MapAxis2(tmwj, TMWJ::JOYY, AllLayers, {-0.6,-0.2,0.2,0.6}, {
		new ActionButtonPulse{vj2,VJOY::DX46,ms2cycles(100)},
		new ActionButtonPulse{vj2,VJOY::DX47,ms2cycles(100)},
		new ActionButtonPulse{vj2,VJOY::DX48,ms2cycles(100)},
		new ActionButtonPulse{vj2,VJOY::DX49,ms2cycles(100)},
		new ActionButtonPulse{vj2,VJOY::DX50,ms2cycles(100)}
	});*/
	
	MapPov(tmwj, TMWJ::HAT1, AllLayers, vj1, VJOY::POV1);
	Map(tmwj, ControlType::Button, TMWJ::S3,  AllLayers, new TriggerButtonPress{},  new ActionPovSetValue{vj1,VJOY::POV1,20.0f});
}


