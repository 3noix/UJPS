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

namespace TMWJ = ThrustmasterWarthogJoystick;
namespace TMWT = ThrustmasterWarthogThrottle;
namespace MFGX = MfgCrosswindRudderPedals;
namespace SCK = StarCitizenControls_Keyboard;
namespace SC1 = StarCitizenControls_vJoy1;
namespace SC2 = StarCitizenControls_vJoy2;

#include "Profile_targeting.cpp"
#include "Profile_shields.cpp"
#include "Profile_trims.cpp"
#include "Profile_modes.cpp"


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








// STOP ///////////////////////////////////////////////////////////////////////
bool Profile::stop()
{
	if (tmwt)
	{
		tmwt->setData("BRIGHTNESS",0);
		tmwt->flush();
	}
	
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

// RUN FIRST STEP /////////////////////////////////////////////////////////////
void Profile::runFirstStep()
{
	// 1. dealing with layers
	this->registerLayerDim1(Layers::In, tmwt, TMWT::MSD);
	
	
	// 2. initialize the virtual joysticks data using the real joysticks data
	// be in sync with the initial mappings defined below
	vj1->resetReport();
	vj2->resetReport();
	vj1->setAxis(SC1::AxisFlightStrafeVertical,0.0f); // vertical strafe at 0 to avoid bad surprises
	
	// leds initialisation
	if (bUseLed)
	{
		tmwt->setData("BRIGHTNESS",1);
		tmwt->setData("BACKLIT",false);
		tmwt->setData("LED4",false);
		tmwt->setData("LED5",false);
	}
	else {tmwt->setData("BRIGHTNESS",0);}
	
	// 3. we create the initial mapping
	// 150 ms for Star Citizen because of the current low framerate
	// we update in case the user changed the time step compared to previous run of the profile
	ncPulse = ms2cycles(150);
	
	// divers
	MapAxis(mfgx, MFGX::RUDDER, AllLayers, vj1, SC1::AxisFlightYaw);
	mfgx->setAxisTrim(MFGX::RUDDER,-0.0028f);
	mfgx->setSCurve(MFGX::RUDDER, 0.035f, 0.012f, 0.035f, 1.0f, 0.0f);
	mfgx->setSCurve(MFGX::BRK_LEFT, 0.04f, 0.00f, 0.06f, 0.0f, 0.0f);
	//mfgx->setSCurve(MFGX::BRK_RIGHT, brkRight_LDZ, 0.00f, brkRight_RDZ, 0.0f, 0.0f);
	
	tmwj->setAxisTrim(TMWJ::JOYX,0.026f);
	tmwj->setAxisTrim(TMWJ::JOYY,-0.006f);
	tmwj->setSCurve(TMWJ::JOYX, 0.02f, 0.015f, 0.01f, 2.5f, 0.0f);
	tmwj->setSCurve(TMWJ::JOYY, 0.01f, 0.015f, 0.015f, 2.5f, 0.0f);
	
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
	MapButton(tmwt, TMWT::APENG, AllLayers, vj1, SC1::LandingSystemToggle);
	
	// throttle slider for power in relative (no axis provided for absolute power)
	tmwt->setSCurve(TMWT::THR_FC, 0.02f, 0.02f, 0.02f, 0, 0);
	MapAxis2(tmwt, TMWT::THR_FC, AllLayers, {-0.95,0.95},{
		new ActionButtonPress(vj1,SC1::IncreasePower),
		new ActionChain({new ActionButtonRelease{vj1,SC1::IncreasePower}, new ActionButtonRelease{vj1,SC1::DecreasePower}}),
		new ActionButtonPress(vj1,SC1::DecreasePower)
	});
	
	// brakes, boost, modes, radar, quantum drive
	MapButton(tmwt, TMWT::MSL, AllLayers, vj1, SC1::CycleAmmoBack);
	MapButton(tmwt, TMWT::MSR, AllLayers, vj1, SC1::CycleAmmo);
	MapButton(tmwt, TMWT::MSU, AllLayers, vj1, SC1::CycleRadarRange);
	//MapButton(tmwt, TMWT::MSD, AllLayers, ...); // deja utilise pour le shift
	MapButton(tmwt, TMWT::SPDF, AllLayers, vj1, SC1::Afterburner);
	MapButton(tmwt, TMWT::SPDB, AllLayers, vj1, SC1::Boost);
	MapButton(tmwt, TMWT::BSB, AllLayers, vj1, SC1::SpaceBrake);
	auto callbackDecoupledTogglePulse = [this]()
	{
		if (!tmwt->buttonPressed(TMWT::LDGH))
			DoAction(new ActionButtonPulse(vj1,SC1::DecoupledModeToggle,ncPulse));
	};
	Map(tmwt, ControlType::Button, TMWT::BSF, AllLayers, new TriggerButtonChange{}, new ActionCallback{callbackDecoupledTogglePulse});
	MapButton(tmwt, TMWT::CHB, AllLayers, vj1, SC1::Autoland);
	MapButton(tmwt, TMWT::CHF, AllLayers, vj1, SC1::QuantumDriveToggle);
	
	// APU button for yaw / roll swap
	auto swapYawRollToggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC1::SwapYawRollToggle,ncPulse});};
	Map(tmwt, ControlType::Button, TMWT::APUON, AllLayers, new TriggerButtonChange{}, new ActionCallback{swapYawRollToggle});
	
	// weapons groups, missiles and quick targeting
	MapButton(tmwj, TMWJ::TG1, AllLayers, vj1, SC1::FireGroup1);
	MapButton(tmwj, TMWJ::TG2, AllLayers, vj1, SC1::FireGroup2); // to shoot 1 and 2 simultaneously with one finger only
	MapButton(tmwj, TMWJ::S3,  AllLayers, vj1, SC1::FireGroup2);
	
	// IFCS safeties and look behind (HAT 1)
	MapButton(tmwj, TMWJ::H1L, AllLayers, vj1, SC1::GForceSafetyToggle);
	MapButton(tmwj, TMWJ::H1U, AllLayers, vj1, SC1::ESPToggle);
	MapButton(tmwj, TMWJ::H1R, AllLayers, vj1, SC1::ComstabToggle);
	MapButton(tmwj, TMWJ::H1D, AllLayers, vj1, SC1::LookBehind);
	
	// COUNTER-MEASURES (hat 2 L/R)
	MapButton(tmwj, TMWJ::H2L, AllLayers, vj1, SC1::CycleCounterMeasures);
	MapButton(tmwj, TMWJ::H2R, AllLayers, vj1, SC1::LaunchCounterMeasures);
	
	// STRAFE (HAT 3)
	MapButton(tmwj, TMWJ::H3L, AllLayers, vj1, SC1::StrafeLeft);
	MapButton(tmwj, TMWJ::H3R, AllLayers, vj1, SC1::StrafeRight);
	
	// TARGET SELECTION (hat 4)
	Map(tmwj, ControlType::Button, TMWJ::H4L, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browsePinnedTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4R, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browseAllTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4U, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browseHostileTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4D, {"i"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->browseFriendTargets();}});
	Map(tmwj, ControlType::Button, TMWJ::H4L, {"o"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->previousTarget();}});
	Map(tmwj, ControlType::Button, TMWJ::H4R, {"o"}, new TriggerButtonPress{}, new ActionCallback{[this]() {this->nextTarget();}});
	MapButton(tmwj, TMWJ::H4U, {"o"}, vj1, SC1::PinFocusedTarget);
	MapButton(tmwj, TMWJ::H4D, {"o"}, vj1, SC1::AcquireMissileLock);
	
	// POWER
	// switchs on : off
	auto powerPreset1Toggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC1::PowerPreset1Toggle,ncPulse});};
	auto powerPreset2Toggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC1::PowerPreset2Toggle,ncPulse});};
	auto powerPreset3Toggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC1::PowerPreset3Toggle,ncPulse});};
	Map(tmwt, ControlType::Button, TMWT::EACON,   AllLayers, new TriggerButtonChange{}, new ActionCallback{powerPreset1Toggle});
	Map(tmwt, ControlType::Button, TMWT::RDRNRM,  AllLayers, new TriggerButtonChange{}, new ActionCallback{powerPreset2Toggle});
	Map(tmwt, ControlType::Button, TMWT::IDLELON, AllLayers, new TriggerButtonChange{}, new ActionCallback{powerPreset3Toggle});
	// power distribution
	MapButton(tmwt, TMWT::CSL, AllLayers, vj1, SC1::PowerPreset1Increase);
	MapButton(tmwt, TMWT::CSD, AllLayers, vj1, SC1::PowerPreset2Increase);
	MapButton(tmwt, TMWT::CSR, AllLayers, vj1, SC1::PowerPreset3Increase);
	MapButton(tmwt, TMWT::CSU, AllLayers, vj1, SC1::ResetPowerDistribution);
	
	// SHIELDS distribution (slew control)
	MapButtonTempo(tmwt, TMWT::SC, AllLayers, ms2cycles(500),
		new ActionCallback{[this]() {this->switchShieldsMode();}},
		new ActionButtonPulse{vj1, SC1::ResetShieldsLevels, ncPulse}
	);
	MapAxis2(tmwt, TMWT::SCX, AllLayers, {-0.84,0.84},{
		new ActionButtonPress(vj1,SC1::ShieldRaiseLeft),
		new ActionChain({new ActionButtonRelease{vj1,SC1::ShieldRaiseLeft}, new ActionButtonRelease{vj1,SC1::ShieldRaiseRight}}),
		new ActionButtonPress(vj1,SC1::ShieldRaiseRight)
	});
	MapAxis2(tmwt, TMWT::SCY, AllLayers, {-0.84,0.84},{
		new ActionCallback{[this]() {this->shieldsDownArrow();}},
		new ActionCallback{[this]() {this->releaseLongiShieldsButtons();}},
		new ActionCallback{[this]() {this->shieldsUpArrow();}}
	});
	
	// LIGHT AND TRANSPONDER
	auto headlightsToggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC1::HeadlightsToggle,ncPulse});};
	auto pIdBroadcaToggle = [this]() {if (!tmwt->buttonPressed(TMWT::LDGH)) DoAction(new ActionButtonPulse{vj1,SC1::PersonalIdBroadCastToggle,ncPulse});};
	Map(tmwt, ControlType::Button, TMWT::EFLNORM, AllLayers, new TriggerButtonChange{}, new ActionCallback{headlightsToggle});
	Map(tmwt, ControlType::Button, TMWT::EFRNORM, AllLayers, new TriggerButtonChange{}, new ActionCallback{pIdBroadcaToggle});
	
	// track IR
	Map(tmwt, ControlType::Button, TMWT::PSF, AllLayers, new TriggerButtonPress{}, new ActionKeyPulse{SCK::TrackIR_Center,0,ncPulse});
	Map(tmwt, ControlType::Button, TMWT::PSB, AllLayers, new TriggerButtonPress{}, new ActionKeyPulse{SCK::TrackIR_Pause,0,ncPulse});
	
	// joystick trim
	Map(tmwt, ControlType::Button, TMWT::FLAPU, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_dxxy_trims();}});
	Map(tmwt, ControlType::Button, TMWT::FLAPD, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->reset_dxxy_trims();}});
}

