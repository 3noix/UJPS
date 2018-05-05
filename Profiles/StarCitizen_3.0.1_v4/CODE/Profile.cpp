#include "Profile.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoystick.h"
#include "WindowsKeys.h"
using namespace Keys;

#include "EnhancedJoystick.h"
#include "RealJoysticksManager.h"
#include "ThrustmasterWarthogJoystick.h"
#include "ThrustmasterWarthogThrottle.h"
#include "MfgCrosswindRudderPedals.h"
#include "StarCitizenControls.h"
#include <QCoreApplication>

using VJOY = VirtualJoystick;
namespace TMWJ = ThrustmasterWarthogJoystick;
namespace TMWT = ThrustmasterWarthogThrottle;
namespace MFGX = MfgCrosswindRudderPedals;
namespace SC = StarCitizenControls;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  PLAY
//  STOP
//  SETUP JOYSTICKS
//  INIT
//
//  BROWSE HOSTILE TARGETS
//  BROWSE ALL TARGETS
//  BROWSE FRIEND TARGETS
//  BROWSE PINNED TARGETS
//  PREVIOUS TARGET
//  NEXT TARGET
//
//  SWITCH SHIELDS MODES
//  SHIELDS DOWN ARROW
//  SHIELDS UP ARROW
//  RELEASE LONGI SHIELDS BUTTONS
//
//  RESET DXXY TRIMS
//  SET DXXY TRIMS
//
//  SET CONTROLS GROUND
//  SET CONTROLS FLIGHT LANDING
//  SET CONTROLS FLIGHT CRUISE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
Profile::Profile() : AbstractProfile()
{
	rjm  = nullptr;
	tmwj = nullptr;
	tmwt = nullptr;
	mfgx = nullptr;
	vj1  = nullptr;
	vj2  = nullptr;
	
	ncPulse = ms2cycles(150); // 150 ms for Star Citizen because of the current low framerate
	m_bShieldsHorizontalMode = true;
	m_targetsTypeToCycle = 2;
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
	if (tmwj) {delete tmwj; tmwj = nullptr;}
	if (tmwt) {delete tmwt; tmwt = nullptr;}
	if (mfgx) {delete mfgx; mfgx = nullptr;}
	if (vj1)  {delete vj1;  vj1  = nullptr;}
	if (vj2)  {delete vj2;  vj2  = nullptr;}
	return true;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	// we allocate the RealJoysticksManager on the heap, because otherwise it will
	// crash at the second call of setupJoysticks... maybe because of pointer global variable
	// in the QtControllerModif lib (cf line 25 of qgamecontroller_win.cpp)
	
	// we retrieve pointers on real joysticks we are interested in
	if (!rjm)
	{
		rjm = new RealJoysticksManager{};
		QString controllersPluginsDirPath = QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/";
		rjm->loadPlugins(QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/");
		QObject::connect(rjm, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
		rjm->searchForControllers();
	}
	bool btmwj = rjm->joystick("Joystick - HOTAS Warthog");
	bool btmwt = rjm->joystick("Throttle - HOTAS Warthog");
	bool bmfgx = rjm->joystick("MFG Crosswind V2");
	
	if (btmwj) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red);}
	
	if (btmwt) {emit message("Warthog throttle detected !",Qt::black);}
	else {emit message("Warthog throttle not detected !",Qt::red);}
	
	if (bmfgx) {emit message("MFG Crosswind rudder pedals detected !",Qt::black);}
	else {emit message("MFG Crosswind rudder pedals not detected !",Qt::red);}
	
	if (!btmwj || !btmwt || !bmfgx) {return false;}
	
	tmwj = new EnhancedJoystick(rjm->joystick("Joystick - HOTAS Warthog"),false);
	tmwt = new EnhancedJoystick(rjm->joystick("Throttle - HOTAS Warthog"),false);
	mfgx = new EnhancedJoystick(rjm->joystick("MFG Crosswind V2"),false);
	
	this->registerRealJoystick(tmwj);
	this->registerRealJoystick(tmwt);
	this->registerRealJoystick(mfgx);
	
	
	// virtual joysticks setup
	vj1 = new VirtualJoystick(1,128);
	QObject::connect(vj1,&VirtualJoystick::message,this,&Profile::message);
	emit message("Virtual joystick 1 configured",Qt::black);
	this->registerVirtualJoystick(vj1);
	
	vj2 = new VirtualJoystick(2,34);
	QObject::connect(vj2,&VirtualJoystick::message,this,&Profile::message);
	emit message("Virtual joystick 2 configured",Qt::black);
	this->registerVirtualJoystick(vj2);
	
	
	return (tmwj && tmwt && mfgx && vj1 && vj2);
}

// INIT ///////////////////////////////////////////////////////////////////////
void Profile::init()
{
	// 1. dealing with layers
	this->registerLayerDim1(Layers::In, tmwt, TMWT::MSD);
	
	
	// 2. initialize the virtual joysticks data using the real joysticks data
	// be in sync with the initial mappings defined below
	vj1->resetReport();
	vj2->resetReport();
	vj1->setAxis(VJOY::SLIDER0,0.0f); // vertical strafe at 0 to avoid bad surprises
	
	
	// 3. we create the initial mapping
	// 150 ms for Star Citizen because of the current low framerate
	// we update in case the user changed the time step compared to previous run of the profile
	ncPulse = ms2cycles(150);
	
	// divers
	MapAxis(mfgx, MFGX::RUDDER, AllLayers, vj1, VJOY::ROTZ);
	mfgx->setAxisTrim(MFGX::RUDDER,-0.0028f);
	mfgx->setSCurve(MFGX::RUDDER, 0.035f, 0.012f, 0.035f, 1.0f, 0.0f);
	mfgx->setSCurve(MFGX::BRK_LEFT, 0.04f, 0.00f, 0.06f, 0.0f, 0.0f);
	//mfgx->setSCurve(MFGX::BRK_RIGHT, brkRight_LDZ, 0.00f, brkRight_RDZ, 0.0f, 0.0f);
	
	tmwj->setAxisTrim(TMWJ::JOYX,0.026f);
	tmwj->setAxisTrim(TMWJ::JOYY,-0.006f);
	tmwj->setSCurve(TMWJ::JOYX, 0.02f, 0.015f, 0.01f, 2.5f, 0.0f);
	tmwj->setSCurve(TMWJ::JOYY, 0.01f, 0.015f, 0.015f, 2.5f, 0.0f);
	
	MapButton(tmwj, TMWJ::H4P, AllLayers, vj2, VJOY::DX1);
	
	// CONTROL MODES AND LANDING
	// initialisation of control modes
	if (tmwt->buttonPressed(TMWT::APALT))      {this->setControlsGround();}
	else if (tmwt->buttonPressed(TMWT::APAH))  {this->setControlsFlightLanding();}
	else if (tmwt->buttonPressed(TMWT::APATT)) {this->setControlsFlightCruise();}
	// set transitions between control modes
	Map(tmwt, ControlType::Button, TMWT::APALT, AllLayers, new TriggerButtonPress{}, new ActionCallback([this](){this->setControlsGround();}));
	Map(tmwt, ControlType::Button, TMWT::APAH,  AllLayers, new TriggerButtonPress{}, new ActionCallback([this](){this->setControlsFlightLanding();}));
	Map(tmwt, ControlType::Button, TMWT::APATT, AllLayers, new TriggerButtonPress{}, new ActionCallback([this](){this->setControlsFlightCruise();}));
	// landing
	MapButton(tmwt, TMWT::APENG, AllLayers, vj1, SC::LandingSystemToggle);
	
	// throttle slider for power in relative (no axis provided for absolute power)
	tmwt->setSCurve(TMWT::THR_FC, 0.02f, 0.02f, 0.02f, 0, 0);
	MapAxis2(tmwt, TMWT::THR_FC, AllLayers, {-0.95,0.95},{
		new ActionButtonPress(vj1,SC::IncreasePower),
		new ActionChain({new ActionButtonRelease{vj1,SC::IncreasePower}, new ActionButtonRelease{vj1,SC::DecreasePower}}),
		new ActionButtonPress(vj1,SC::DecreasePower)
	});
	
	// brakes, boost, modes, radar, quantum drive
	MapButton(tmwt, TMWT::MSL, AllLayers, vj1, SC::CycleAmmoBack);
	MapButton(tmwt, TMWT::MSR, AllLayers, vj1, SC::CycleAmmo);
	MapButton(tmwt, TMWT::MSU, AllLayers, vj1, SC::CycleRadarRange);
	//MapButton(tmwt, TMWT::MSD, AllLayers, ...); // deja utilise pour le shift
	MapButton(tmwt, TMWT::SPDF, AllLayers, vj1, SC::Afterburner);
	MapButton(tmwt, TMWT::SPDB, AllLayers, vj1, SC::Boost);
	MapButton(tmwt, TMWT::BSB, AllLayers, vj1, SC::SpaceBrake);
	auto callbackDecoupledTogglePulse = [this]()
	{
		if (!tmwt->buttonPressed(TMWT::LDGH))
			DoAction(new ActionButtonPulse(vj1,SC::DecoupledModeToggle,ncPulse));
	};
	Map(tmwt, ControlType::Button, TMWT::BSF, AllLayers, new TriggerButtonChange{}, new ActionCallback(callbackDecoupledTogglePulse));
	MapButton(tmwt, TMWT::CHB, AllLayers, vj1, SC::Autoland);
	MapButton(tmwt, TMWT::CHF, AllLayers, vj1, SC::QuantumDriveToggle);
	
	// APU button for yaw / roll swap
	auto swapYawRollToggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC::SwapYawRollToggle,ncPulse});};
	Map(tmwt, ControlType::Button, TMWT::APUON, AllLayers, new TriggerButtonChange{}, new ActionCallback{swapYawRollToggle});
	
	// weapons groups, missiles and quick targeting
	MapButton(tmwj, TMWJ::TG1, AllLayers, vj1, SC::FireGroup1);
	MapButton(tmwj, TMWJ::TG2, AllLayers, vj1, SC::FireGroup2); // to shoot 1 and 2 simultaneously with one finger only
	MapButton(tmwj, TMWJ::S3,  AllLayers, vj1, SC::FireGroup2);
	
	// IFCS safeties and look behind (HAT 1)
	MapButton(tmwj, TMWJ::H1L, AllLayers, vj1, SC::GForceSafetyToggle);
	MapButton(tmwj, TMWJ::H1U, AllLayers, vj1, SC::ESPToggle);
	MapButton(tmwj, TMWJ::H1R, AllLayers, vj1, SC::ComstabToggle);
	MapButton(tmwj, TMWJ::H1D, AllLayers, vj1, SC::LookBehind);
	
	// COUNTER-MEASURES (hat 2 L/R)
	MapButton(tmwj, TMWJ::H2L, AllLayers, vj1, SC::CycleCounterMeasures);
	MapButton(tmwj, TMWJ::H2R, AllLayers, vj1, SC::LaunchCounterMeasures);
	
	// STRAFE (HAT 3)
	MapButton(tmwj, TMWJ::H3L, AllLayers, vj1, SC::StrafeLeft);
	MapButton(tmwj, TMWJ::H3R, AllLayers, vj1, SC::StrafeRight);
	
	// TARGET SELECTION (hat 4)
	Map(tmwj, ControlType::Button, TMWJ::H4L, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browsePinnedTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4R, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browseAllTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4U, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browseHostileTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4D, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browseFriendTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4L, {"o"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->previousTarget();}});
	Map(tmwj, ControlType::Button, TMWJ::H4R, {"o"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->nextTarget();}});
	MapButton(tmwj, TMWJ::H4U, {"o"}, vj1, SC::PinFocusedTarget);
	MapButton(tmwj, TMWJ::H4D, {"o"}, vj1, SC::AcquireMissileLock);
	
	// POWER
	// switchs on : off
	auto powerPreset1Toggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC::PowerPreset1Toggle,ncPulse});};
	auto powerPreset2Toggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC::PowerPreset2Toggle,ncPulse});};
	auto powerPreset3Toggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC::PowerPreset3Toggle,ncPulse});};
	Map(tmwt, ControlType::Button, TMWT::EACON,   AllLayers, new TriggerButtonChange{}, new ActionCallback{powerPreset1Toggle});
	Map(tmwt, ControlType::Button, TMWT::RDRNRM,  AllLayers, new TriggerButtonChange{}, new ActionCallback{powerPreset2Toggle});
	Map(tmwt, ControlType::Button, TMWT::IDLELON, AllLayers, new TriggerButtonChange{}, new ActionCallback{powerPreset3Toggle});
	// power distribution
	MapButton(tmwt, TMWT::CSL, AllLayers, vj1, SC::PowerPreset1Increase);
	MapButton(tmwt, TMWT::CSD, AllLayers, vj1, SC::PowerPreset2Increase);
	MapButton(tmwt, TMWT::CSR, AllLayers, vj1, SC::PowerPreset3Increase);
	MapButton(tmwt, TMWT::CSU, AllLayers, vj1, SC::ResetPowerDistribution);
	
	// SHIELDS distribution (slew control)
	MapButtonTempo(tmwt, TMWT::SC, AllLayers, ms2cycles(500),
		new ActionCallback{[this]() {this->switchShieldsMode();}},
		new ActionButtonPulse{vj1, SC::ResetShieldsLevels, ncPulse}
	);
	MapAxis2(tmwt, TMWT::SCX, AllLayers, {-0.84,0.84},{
		new ActionButtonPress(vj1,SC::ShieldRaiseLeft),
		new ActionChain({new ActionButtonRelease{vj1,SC::ShieldRaiseLeft}, new ActionButtonRelease{vj1,SC::ShieldRaiseRight}}),
		new ActionButtonPress(vj1,SC::ShieldRaiseRight)
	});
	MapAxis2(tmwt, TMWT::SCY, AllLayers, {-0.84,0.84},{
		new ActionCallback{[this]() {this->shieldsDownArrow();}},
		new ActionCallback{[this]() {this->releaseLongiShieldsButtons();}},
		new ActionCallback{[this]() {this->shieldsUpArrow();}}
	});
	
	// LIGHT AND TRANSPONDER
	auto headlightsToggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC::HeadlightsToggle,ncPulse});};
	auto pIdBroadcaToggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC::PersonalIdBroadCastToggle,ncPulse});};
	Map(tmwt, ControlType::Button, TMWT::EFLNORM, AllLayers, new TriggerButtonChange{}, new ActionCallback{headlightsToggle});
	Map(tmwt, ControlType::Button, TMWT::EFRNORM, AllLayers, new TriggerButtonChange{}, new ActionCallback{pIdBroadcaToggle});
	
	// track IR
	Map(tmwt, ControlType::Button, TMWT::PSF, AllLayers, new TriggerButtonPress{}, new ActionKeyPulse{SC::TrackIR_Center,0,ncPulse});
	Map(tmwt, ControlType::Button, TMWT::PSB, AllLayers, new TriggerButtonPress{}, new ActionKeyPulse{SC::TrackIR_Pause,0,ncPulse});
	
	// joystick trim
	Map(tmwt, ControlType::Button, TMWT::FLAPU, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_dxxy_trims();}});
	Map(tmwt, ControlType::Button, TMWT::FLAPD, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->reset_dxxy_trims();}});
	
	// we send the report
	vj1->sendReport();
}





// BROWSE HOSTILE TARGETS /////////////////////////////////////////////////////
void Profile::browseHostileTargets() {m_targetsTypeToCycle = 1;}

// BROWSE ALL TARGETS /////////////////////////////////////////////////////////
void Profile::browseAllTargets() {m_targetsTypeToCycle = 2;}

// BROWSE FRIEND TARGETS //////////////////////////////////////////////////////
void Profile::browseFriendTargets() {m_targetsTypeToCycle = 3;}

// BROWSE PINNED TARGETS //////////////////////////////////////////////////////
void Profile::browsePinnedTargets() {m_targetsTypeToCycle = 4;}


// PREVIOUS TARGET ////////////////////////////////////////////////////////////
void Profile::previousTarget()
{
	if (m_targetsTypeToCycle == 1)      {DoAction(new ActionButtonPulse{vj1,SC::CycleHostileTargetsBack,ncPulse});}
	else if (m_targetsTypeToCycle == 2) {DoAction(new ActionButtonPulse{vj1,SC::CycleAllTargetsBack,ncPulse});}
	else if (m_targetsTypeToCycle == 3) {DoAction(new ActionButtonPulse{vj1,SC::CycleFriendlyTargetsBack,ncPulse});}
	else                                {DoAction(new ActionButtonPulse{vj1,SC::CyclePinnedTargetsBack,ncPulse});}
}

// NEXT TARGET ////////////////////////////////////////////////////////////////
void Profile::nextTarget()
{
	if (m_targetsTypeToCycle == 1)      {DoAction(new ActionButtonPulse{vj1,SC::CycleHostileTargets,ncPulse});}
	else if (m_targetsTypeToCycle == 2) {DoAction(new ActionButtonPulse{vj1,SC::CycleAllTargets,ncPulse});}
	else if (m_targetsTypeToCycle == 3) {DoAction(new ActionButtonPulse{vj1,SC::CycleFriendlyTargets,ncPulse});}
	else                                {DoAction(new ActionButtonPulse{vj1,SC::CyclePinnedTargets,ncPulse});}
}







// SWITCH SHIELDS MODES ///////////////////////////////////////////////////////
void Profile::switchShieldsMode()
{
	m_bShieldsHorizontalMode = !m_bShieldsHorizontalMode;
}

// SHIELDS DOWN ARROW /////////////////////////////////////////////////////////
void Profile::shieldsDownArrow()
{
	if (m_bShieldsHorizontalMode) {vj1->setButton(SC::ShieldRaiseBack,true);}
	else {vj1->setButton(SC::ShieldRaiseBottom,true);}
}

// SHIELDS UP ARROW ///////////////////////////////////////////////////////////
void Profile::shieldsUpArrow()
{
	if (m_bShieldsHorizontalMode) {vj1->setButton(SC::ShieldRaiseFront,true);}
	else {vj1->setButton(SC::ShieldRaiseTop,true);}
}

// RELEASE LONGI SHIELDS BUTTONS //////////////////////////////////////////////
void Profile::releaseLongiShieldsButtons()
{
	vj1->setButton(SC::ShieldRaiseFront,false);
	vj1->setButton(SC::ShieldRaiseBack,false);
	vj1->setButton(SC::ShieldRaiseTop,false);
	vj1->setButton(SC::ShieldRaiseBottom,false);
}





// RESET DXXY TRIMS ///////////////////////////////////////////////////////////
void Profile::reset_dxxy_trims()
{
	tmwj->setAxisTrim(TMWJ::JOYX,0.0f);
	tmwj->setAxisTrim(TMWJ::JOYY,0.0f);
}

// SET DXXY TRIMS /////////////////////////////////////////////////////////////
void Profile::set_dxxy_trims()
{
	tmwj->setAxisTrim(TMWJ::JOYX,-tmwj->axisRawValue(TMWJ::JOYX));
	tmwj->setAxisTrim(TMWJ::JOYY,-tmwj->axisRawValue(TMWJ::JOYY));
	vj1->setAxis(VJOY::X,0.0f);
	vj1->setAxis(VJOY::Y,0.0f);
	vj1->setAxis(VJOY::ROTX,0.0f);
	vj1->setAxis(VJOY::ROTY,0.0f);
}







// SET CONTROLS GROUND ////////////////////////////////////////////////////////
void Profile::setControlsGround()
{
	if (true)
	{
		this->set_JOYXY_for_turn();
		this->set_THR_and_pedals();
	}
	else if (true)
	{
		this->set_JOYXY_for_turnNbrake();
		this->set_THR_for_ground();
	}
	else
	{
		this->set_JOYXY_for_turnNthrottle();
		this->set_THR_for_nothing();
	}
	
	this->set_S4_for_horn();
	this->set_BUTTONS_for_cruise();
}

// SET CONTROLS FLIGHT LANDING ////////////////////////////////////////////////
void Profile::setControlsFlightLanding()
{
	this->set_S4_for_landing(); // to quickly switch JOYXY from roll&pitch to strafe and vice-versa
	this->set_JOYXY_for_landing();
	this->set_BUTTONS_for_landing();
	this->set_THR_for_landing();
}

// SET CONTROLS FLIGHT CRUISE /////////////////////////////////////////////////
void Profile::setControlsFlightCruise()
{
	this->set_S4_for_nothing();
	this->set_JOYXY_for_rollNpitch();
	this->set_BUTTONS_for_cruise();
	this->set_THR_for_cruise();
}


// set_JOYXY_for_turn
// set_JOYXY_for_turnNthrottle
// set_JOYXY_for_turnNbrake
// set_JOYXY_for_landing
// set_JOYXY_for_strafe
// set_JOYXY_for_rollNpitch
void Profile::set_JOYXY_for_turn()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, VJOY::X, AxisDirection::Normal);
	vj1->setAxis(VJOY::Y, 0.0f);
	vj1->setAxis(VJOY::Z, 0.0f);
	vj1->setAxis(VJOY::ROTX, 0.0f);
	vj1->setAxis(VJOY::ROTY, 0.0f);
	
	vj1->setAxis(VJOY::X, tmwj->axisValue(TMWJ::JOYX));
	vj1->setButton(SC::Brake,false);
}

void Profile::set_JOYXY_for_turnNthrottle()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, VJOY::X, AxisDirection::Normal);
	MapAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::Z, AxisDirection::Normal);
	
	vj1->setAxis(VJOY::Y, 0.0f);
	vj1->setAxis(VJOY::ROTX, 0.0f);
	vj1->setAxis(VJOY::ROTY, 0.0f);
	
	vj1->setAxis(VJOY::X, tmwj->axisValue(TMWJ::JOYX));
	vj1->setAxis(VJOY::Z, tmwj->axisValue(TMWJ::JOYY));
	vj1->setButton(SC::Brake,false);
}

void Profile::set_JOYXY_for_turnNbrake()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	// joystick : turn et brake
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, VJOY::X, AxisDirection::Normal);
	MapAxis2(tmwj, TMWJ::JOYY, AllLayers, std::vector<float>{0.6f},{
		new ActionButtonRelease{vj1,SC::Brake},
		new ActionButtonPress{vj1,SC::Brake}
	});
	
	// set pitch and strafe axes at 0, otherwise they keep their last values
	vj1->setAxis(VJOY::Y, 0.0f);
	vj1->setAxis(VJOY::ROTX, 0.0f);
	vj1->setAxis(VJOY::ROTY, 0.0f);
	// set X axis at correct value, otherwise it is necessary to wait for a movement of the stick
	vj1->setAxis(VJOY::X, tmwj->axisValue(TMWJ::JOYX));
	// brake button in sync with the JOYY axis mapping
	vj1->setButton(SC::Brake,tmwj->axisValue(TMWJ::JOYY)>0.6f);
}

void Profile::set_JOYXY_for_landing()
{
	if (tmwj->buttonPressed(TMWJ::S4))
		this->set_JOYXY_for_strafe();
	else
		this->set_JOYXY_for_rollNpitch();
	
	vj1->setButton(SC::Brake,false);
}

void Profile::set_JOYXY_for_strafe()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	// joystick -> strafe
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, VJOY::ROTX, AxisDirection::Normal);
	MapAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::ROTY, AxisDirection::Reversed);
	
	// set roll and pitch axes at 0, otherwise they keep their last values
	vj1->setAxis(VJOY::X, 0.0f);
	vj1->setAxis(VJOY::Y, 0.0f);
	// set strafe axes at correct value, otherwise it is necessary to wait for a movement of the stick
	vj1->setAxis(VJOY::ROTX, tmwj->axisValue(TMWJ::JOYX));
	vj1->setAxis(VJOY::ROTY, -tmwj->axisValue(TMWJ::JOYY));
	vj1->setButton(SC::Brake,false);
}

void Profile::set_JOYXY_for_rollNpitch()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	// joystick : roll and pitch
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, VJOY::X, AxisDirection::Normal);
	MapAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::Y, AxisDirection::Normal);
	
	// set strafe axes at 0, otherwise they keep their last values
	vj1->setAxis(VJOY::ROTX, 0.0f);
	vj1->setAxis(VJOY::ROTY, 0.0f);
	// set roll and pitch axes at correct value, otherwise it is necessary to wait for a movement of the stick
	vj1->setAxis(VJOY::X, tmwj->axisValue(TMWJ::JOYX));
	vj1->setAxis(VJOY::Y, tmwj->axisValue(TMWJ::JOYY));
	vj1->setButton(SC::Brake,false);
}


// set_S4_for_horn
// set_S4_for_landing
// set_S4_for_nothing
void Profile::set_S4_for_horn()
{
	UnmapButton(tmwj, TMWJ::S4);
	MapButton(tmwj, TMWJ::S4, AllLayers, vj1, SC::Horn);
}

void Profile::set_S4_for_landing()
{
	UnmapButton(tmwj, TMWJ::S4);
	Map(tmwj, ControlType::Button, TMWJ::S4, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_JOYXY_for_strafe();}});
	Map(tmwj, ControlType::Button, TMWJ::S4, AllLayers, new TriggerButtonRelease{}, new ActionCallback{[this]() {this->set_JOYXY_for_rollNpitch();}});
}

void Profile::set_S4_for_nothing()
{
	UnmapButton(tmwj, TMWJ::S4);
}


// set_BUTTONS_for_landing
// set_BUTTONS_for_cruise
void Profile::set_BUTTONS_for_landing()
{
	UnmapButton(tmwj, TMWJ::S1);
	UnmapButton(tmwj, TMWJ::S2);
	UnmapButton(tmwj, TMWJ::H2U);
	UnmapButton(tmwj, TMWJ::H2D);
	UnmapButton(tmwj, TMWJ::H3U);
	UnmapButton(tmwj, TMWJ::H3D);
	
	MapButton(tmwj, TMWJ::S1, {"i"}, vj1, SC::TargetNearestHostile);
	MapButton(tmwj, TMWJ::S1, {"o"}, vj1, SC::CycleAllTargets); // to cycle landing pads
	//MapButton(tmwj, TMWJ::S2, AllLayers, vj1, SC::LandingTargetLockOnToggle); // to select a landing pad
	
	MapButton(tmwj, TMWJ::H2U, AllLayers, vj1, SC::StrafeUp);
	MapButton(tmwj, TMWJ::H2D, AllLayers, vj1, SC::StrafeDown);
	MapButton(tmwj, TMWJ::H3U, AllLayers, vj1, SC::StrafeForward);
	MapButton(tmwj, TMWJ::H3D, AllLayers, vj1, SC::StrafeBackwards);
}

void Profile::set_BUTTONS_for_cruise()
{
	UnmapButton(tmwj, TMWJ::S1);
	UnmapButton(tmwj, TMWJ::S2);
	UnmapButton(tmwj, TMWJ::H2U);
	UnmapButton(tmwj, TMWJ::H2D);
	UnmapButton(tmwj, TMWJ::H3U);
	UnmapButton(tmwj, TMWJ::H3D);
	
	MapButton(tmwj, TMWJ::S1, {"i"}, vj1, SC::TargetNearestHostile);
	MapButton(tmwj, TMWJ::S1, {"o"}, vj1, SC::CycleHostileTargets);
	MapButton(tmwj, TMWJ::S2, AllLayers, vj1, SC::LaunchMissile);
	
	MapButton(tmwj, TMWJ::H2U, AllLayers, vj1, SC::StrafeForward);
	MapButton(tmwj, TMWJ::H2D, AllLayers, vj1, SC::StrafeBackwards);
	MapButton(tmwj, TMWJ::H3U, AllLayers, vj1, SC::StrafeUp);
	MapButton(tmwj, TMWJ::H3D, AllLayers, vj1, SC::StrafeDown);
}


// set_THR_and_pedals
// set_THR_for_nothing
// set_THR_for_ground
// set_THR_for_landing
// set_THR_for_cruise
void Profile::set_THR_and_pedals()
{
	this->set_THR_for_nothing();
	
	MapAxis2(tmwt, TMWT::THR_RIGHT, AllLayers, 1, {
		new ActionCallback{[this](){this->set_BRKRIGHT_for_groundBackward();}},
		new ActionCallback{[this](){this->set_BRKRIGHT_for_groundForward();}}
	});
	if (tmwt->axisValue(TMWT::THR_RIGHT) > 0)
		this->set_BRKRIGHT_for_groundForward();
	else
		this->set_BRKRIGHT_for_groundBackward();
	
	Map(mfgx, ControlType::Axis, MFGX::BRK_LEFT, AllLayers, new TriggerAxisChangeComparison{true,thrBreak}, new ActionButtonPress{vj1,SC::Brake});
	Map(mfgx, ControlType::Axis, MFGX::BRK_LEFT, AllLayers, new TriggerAxisChangeComparison{false,thrBreak}, new ActionButtonRelease{vj1,SC::Brake});
	if (mfgx->axisValue(MFGX::BRK_LEFT) > thrBreak)
		vj1->setButton(SC::Brake,true);
	else
		vj1->setButton(SC::Brake,false);
}

void Profile::set_THR_for_nothing()
{
	UnmapAxis(mfgx, MFGX::BRK_LEFT);
	UnmapAxis(mfgx, MFGX::BRK_RIGHT);
	
	UnmapAxis(tmwt, TMWT::THR_LEFT);
	UnmapAxis(tmwt, TMWT::THR_RIGHT);
	tmwt->removeCurve(TMWT::THR_LEFT);
	tmwt->removeCurve(TMWT::THR_RIGHT);
	
	UnmapButton(tmwt, TMWT::LTB);
	vj1->setAxis(VJOY::SLIDER0, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_THR_for_ground()
{
	UnmapAxis(mfgx, MFGX::BRK_LEFT);
	UnmapAxis(mfgx, MFGX::BRK_RIGHT);
	
	UnmapAxis(tmwt, TMWT::THR_LEFT);
	UnmapAxis(tmwt, TMWT::THR_RIGHT);
	tmwt->removeCurve(TMWT::THR_LEFT);
	tmwt->removeCurve(TMWT::THR_RIGHT);
	
	if (tmwt->buttonPressed(TMWT::LTB))
		this->set_THRLEFT_for_groundBackward();
	else
		this->set_THRLEFT_for_groundForward();
	
	UnmapButton(tmwt, TMWT::LTB);
	Map(tmwt, ControlType::Button, TMWT::LTB, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_THRLEFT_for_groundBackward();}});
	Map(tmwt, ControlType::Button, TMWT::LTB, AllLayers, new TriggerButtonRelease{}, new ActionCallback{[this]() {this->set_THRLEFT_for_groundForward();}});
}

void Profile::set_THR_for_landing()
{
	UnmapAxis(mfgx, MFGX::BRK_LEFT);
	UnmapAxis(mfgx, MFGX::BRK_RIGHT);
	
	UnmapAxis(tmwt, TMWT::THR_LEFT);
	UnmapAxis(tmwt, TMWT::THR_RIGHT);
	tmwt->removeCurve(TMWT::THR_LEFT);
	tmwt->removeCurve(TMWT::THR_RIGHT);
	
	this->set_THRRIGHT_for_flightThrottle();
	
	if (tmwt->buttonPressed(TMWT::LTB))
		this->set_THRLEFT_for_nothing();
	else
		this->set_THRLEFT_for_verticalStrafe();
	
	UnmapButton(tmwt, TMWT::LTB);
	Map(tmwt, ControlType::Button, TMWT::LTB, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_THRLEFT_for_nothing();}});
	Map(tmwt, ControlType::Button, TMWT::LTB, AllLayers, new TriggerButtonRelease{}, new ActionCallback{[this]() {this->set_THRLEFT_for_verticalStrafe();}});
}

void Profile::set_THR_for_cruise()
{
	UnmapAxis(mfgx, MFGX::BRK_LEFT);
	UnmapAxis(mfgx, MFGX::BRK_RIGHT);
	
	UnmapAxis(tmwt, TMWT::THR_LEFT);
	UnmapAxis(tmwt, TMWT::THR_RIGHT);
	tmwt->removeCurve(TMWT::THR_LEFT);
	tmwt->removeCurve(TMWT::THR_RIGHT);
	this->set_THRRIGHT_for_flightThrottle();
	this->set_THRLEFT_for_nothing();
	UnmapButton(tmwt, TMWT::LTB);
}


// set_BRKRIGHT_for_groundForward
// set_BRKRIGHT_for_groundBackward
// set_THRLEFT_for_groundForward
// set_THRLEFT_for_groundBackward
// set_THRLEFT_for_verticalStrafe
// set_THRLEFT_for_nothing
// set_THRRIGHT_for_flightThrottle
void Profile::set_BRKRIGHT_for_groundForward()
{
	MapAxis(mfgx, MFGX::BRK_RIGHT, AllLayers, vj1, VJOY::Z, AxisDirection::Normal);
	mfgx->setCustomCurve(MFGX::BRK_RIGHT, {-1.0f+2.0f*brkRight_LDZ,0.0f,  1.0f-2.0f*brkRight_RDZ,1.0f});
	vj1->setAxis(VJOY::Z, mfgx->axisValue(MFGX::BRK_RIGHT));
	vj1->setAxis(VJOY::SLIDER0, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_BRKRIGHT_for_groundBackward()
{
	MapAxis(mfgx, MFGX::BRK_RIGHT, AllLayers, vj1, VJOY::Z, AxisDirection::Normal);
	mfgx->setCustomCurve(MFGX::BRK_RIGHT, {-1.0f+2.0f*brkRight_LDZ,0.0f,  1.0f-2.0f*brkRight_RDZ,-1.0f});
	vj1->setAxis(VJOY::Z, mfgx->axisValue(MFGX::BRK_RIGHT));
	vj1->setAxis(VJOY::SLIDER0, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_THRLEFT_for_groundForward()
{
	MapAxis(tmwt, TMWT::THR_LEFT, AllLayers, vj1, VJOY::Z, AxisDirection::Normal);
	tmwt->setCustomCurve(TMWT::THR_LEFT, {-1.0f,1.0f,  1.0f,0.0f});
	vj1->setAxis(VJOY::Z, -tmwt->axisValue(TMWT::THR_LEFT));
	vj1->setAxis(VJOY::SLIDER0, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_THRLEFT_for_groundBackward()
{
	MapAxis(tmwt, TMWT::THR_LEFT, AllLayers, vj1, VJOY::Z, AxisDirection::Normal);
	tmwt->setCustomCurve(TMWT::THR_LEFT, {-1.0f,-1.0f,  1.0f,0.0f});
	vj1->setAxis(VJOY::Z, -tmwt->axisValue(TMWT::THR_LEFT));
	vj1->setAxis(VJOY::SLIDER0, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_THRLEFT_for_verticalStrafe()
{
	MapAxis(tmwt, TMWT::THR_LEFT, AllLayers, vj1, VJOY::SLIDER0, AxisDirection::Reversed);
	float reductionFactor = 0.2f;
	tmwt->setCustomCurve(TMWT::THR_LEFT, {-1.0f,-reductionFactor,  1.0f,reductionFactor});
	vj1->setAxis(VJOY::SLIDER0, 0.0f);
	vj1->setAxisTrim(VJOY::SLIDER0, tmwt->axisValue(TMWT::THR_LEFT));
}

void Profile::set_THRLEFT_for_nothing()
{
	UnmapAxis(tmwt, TMWT::THR_LEFT);
	vj1->setAxis(VJOY::SLIDER0, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_THRRIGHT_for_flightThrottle()
{
	MapAxis(tmwt, TMWT::THR_RIGHT, AllLayers, vj1, VJOY::Z, AxisDirection::Normal); // THR_RIGHT mapped to thrust
	vj1->setAxis(VJOY::Z, tmwt->axisValue(TMWT::THR_RIGHT)); // set axis at correct value, otherwise it is necessary to wait for a movement of the throttle
}


