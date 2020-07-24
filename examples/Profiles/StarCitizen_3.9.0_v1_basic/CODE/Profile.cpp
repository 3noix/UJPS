#include "Profile.h"
#include "BASIC/ProfileBasicUtilities.h"
#include "CURVES/CurveExpCentered.h"
#include "CURVES/CurveExpNotCentered.h"

#include "VirtualJoystick.h"
#include "AbstractRealJoystick.h"
#include "ThrustmasterWarthogJoystick.h"
#include "ThrustmasterWarthogThrottle.h"
#include "MfgCrosswindRudderPedals.h"
#include "StarCitizenControls.h"
#include "Lim.h"

namespace TMWJ = ThrustmasterWarthogJoystick;
namespace TMWT = ThrustmasterWarthogThrottle;
namespace MFGX = MfgCrosswindRudderPedals;
namespace SCK = StarCitizenControls_Keyboard;
namespace SC1 = StarCitizenControls_vJoy1;
namespace SC2 = StarCitizenControls_vJoy2;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  STOP
//  SETUP JOYSTICKS
//  RUN ONE STEP
//
//  GET AXES DATA
//  PROCESS THE 6 FLIGHT AXES
//  GET LANDING FACTOR
//
//  PROCESS SPEED MANAGEMENT
//  PROCESS OTHER FLIGHT CONTROLS
//  PROCESS TARGETING
//  PROCESS SCAN
//  PROCESS WEAPONS AND CM
//  PROCESS POWER
//  PROCESS SHIELDS
//  PROCESS GROUND
//  PROCESS VIEW
//  PROCESS LEDS
//  PROCESS OTHER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
Profile::Profile() : AbstractProfileBasic{}
{
	tmwj = nullptr;
	tmwt = nullptr;
	mfgx = nullptr;
	vj1  = nullptr;
	vj2  = nullptr;
}

Profile::~Profile()
{
	this->stop();
}






// STOP ///////////////////////////////////////////////////////////////////////
void Profile::stop()
{
	// set led brightness at 0
	if (tmwt)
	{
		tmwt->setData("BRIGHTNESS",0);
		tmwt->flush();
	}
	
	// UnmapAll, delete real and virtual joysticks
	this->AbstractProfileBasic::stop();
	
	// it is a good idea to set them to nullptr
	tmwj = nullptr;
	tmwt = nullptr;
	mfgx = nullptr;
	vj1  = nullptr;
	vj2  = nullptr;
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
	
	
	// virtual joysticks setup
	vj1 = this->registerVirtualJoystick(1);
	if (vj1) {emit message("Virtual joystick 1 acquired",Qt::black);}
	else {emit message("Virtual joystick 1 failed to configure",Qt::red);}
	
	vj2 = this->registerVirtualJoystick(2);
	if (vj2) {emit message("Virtual joystick 2 acquired",Qt::black);}
	else {emit message("Virtual joystick 2 failed to configure",Qt::red);}
	
	
	return (tmwj && tmwt && mfgx && vj1 && vj2);
}

// RUN ONE STEP ///////////////////////////////////////////////////////////////
void Profile::runOneStep(bool bInit)
{
	if (bInit)
	{
		vj1->resetReport();
		
		tmwt->setData("BRIGHTNESS",0);
		tmwt->setData("BACKLIT",true);
		tmwt->setData("LED1",true);
		tmwt->setData("LED2",true);
		tmwt->setData("LED3",true);
		tmwt->setData("LED4",true);
		tmwt->setData("LED5",true);
		
		// not as constants in header, because the time-step can change
		nbCyclesPulseButton = ms2cycles(150);
		nbCycles500ms = ms2cycles(500);
		nbCycles1s = ms2cycles(1000);
	}
	
	// get axes data (and apply trim, curves, ...)
	AxesData data = this->getAxesData(bInit);
	
	this->processThe6FlightAxes(data);
	this->processSpeedManagement();
	this->processOtherFlightControls();
	this->processTargeting();
	this->processScan();
	this->processWeaponsAndCm();
	this->processPower();
	this->processShields();
	this->processGround(data);
	this->processView();
	this->processLeds(bInit);
	this->processOther();
}






// GET AXES DATA //////////////////////////////////////////////////////////////
Profile::AxesData Profile::getAxesData(bool bInit) const
{
	// get raw inputs
	float JOYX_raw = tmwj->axisValue(TMWJ::JOYX);
	float JOYY_raw = tmwj->axisValue(TMWJ::JOYY);
	float DRPED_raw = mfgx->axisValue(MFGX::RUDDER);
	float BRKL_raw = mfgx->axisValue(MFGX::BRK_LEFT);
	float BRKR_raw = mfgx->axisValue(MFGX::BRK_RIGHT);
	bool BPSF = tmwt->buttonPressed(TMWT::PSF);
	
	// tempo: short input = recenter, long input = set trim at 0
	static Tempo tempoTrim{nbCycles1s};
	TempoOutput tempoTrimOut = tempoTrim(BPSF);
	bool BRESETTRIMS = tempoTrimOut.longPress;
	bool BSETTRIMS = (tempoTrimOut.shortPress || (bInit && bTrimAtInit));
	bool bTrimMemCond = !(BRESETTRIMS || BSETTRIMS);
	
	// memo to achieve trim logic
	static Memorization<float> memo_joyx{JOYX_raw};
	static Memorization<float> memo_joyy{JOYY_raw};
	static Memorization<float> memo_drped{DRPED_raw};
	static Memorization<float> memo_brkl{BRKL_raw};
	static Memorization<float> memo_brkr{BRKR_raw};
	float JOYX_trimmed  = JOYX_raw  - memo_joyx(BRESETTRIMS  ? 0.0f : JOYX_raw,  bTrimMemCond);
	float JOYY_trimmed  = JOYY_raw  - memo_joyy(BRESETTRIMS  ? 0.0f : JOYY_raw,  bTrimMemCond);
	float DRPED_trimmed = DRPED_raw - memo_drped(BRESETTRIMS ? 0.0f : DRPED_raw, bTrimMemCond);
	float BRKL_trimmed  = BRKL_raw  - memo_brkl(BRESETTRIMS  ? 0.0f : 1.0f+BRKL_raw,  bTrimMemCond);
	float BRKR_trimmed  = BRKR_raw  - memo_brkr(BRESETTRIMS  ? 0.0f : 1.0f+BRKR_raw,  bTrimMemCond);
	
	// addition of axes curves
	static CurveExpCentered curve_JOY{1.5f,1.5f,1.5f,2.5f,0.0f};
	static CurveExpCentered curve_DRPED{3.5f,1.3f,3.5f,1.0f,0.0f};
	static Interpolation1D interpDzBrk{{-0.92f,0.88f},{-1.0f,1.0f}};
	
	// thrust levers center notch
	float THRL_raw = tmwt->axisValue(TMWT::THR_LEFT);
	float THRR_raw = tmwt->axisValue(TMWT::THR_RIGHT);
	float THRL = (THRL_raw>thrlevx2) ? (THRL_raw-thrlevx2)/(1-thrlevx2) : (THRL_raw<thrlevx1 ? (THRL_raw-thrlevx1)/(1+thrlevx1) : 0.0f);
	float THRR = (THRR_raw>thrlevx2) ? (THRR_raw-thrlevx2)/(1-thrlevx2) : (THRR_raw<thrlevx1 ? (THRR_raw-thrlevx1)/(1+thrlevx1) : 0.0f);
	
	AxesData out;
	out.JOYX  = curve_JOY.run(JOYX_trimmed);
	out.JOYY  = curve_JOY.run(JOYY_trimmed);
	out.THRL  = -THRL;
	out.THRR  = -THRR;
	out.DRPED = curve_DRPED.run(DRPED_trimmed);
	out.BRKL  = interpDzBrk(BRKL_trimmed);
	out.BRKR  = interpDzBrk(BRKR_trimmed);
	return out;
}

// PROCESS THE 6 FLIGHT AXES //////////////////////////////////////////////////
void Profile::processThe6FlightAxes(const AxesData &data) const
{
	// modes
	bool BGNDMODE = tmwt->buttonPressed(TMWT::APALT);
	bool BLNDMODE = tmwt->buttonPressed(TMWT::APAH);
	bool BCRZMODE = tmwt->buttonPressed(TMWT::APPAT);
	bool BFLTMODE = (BLNDMODE || BCRZMODE);
	
	// landing factor
	float KLNDFACTOR = this->getLandingFactor(BLNDMODE);
	
	// movements (final)
	float FLIGHT_ROLL = (BGNDMODE ? 0.0f : (BLNDMODE ? kLndRollPitch*data.JOYX : data.JOYX));
	float FLIGHT_PITCH = (BGNDMODE ? 0.0f : (BLNDMODE ? kLndRollPitch*data.JOYY : data.JOYY));
	float FLIGHT_YAW = (BGNDMODE ? 0.0f : data.DRPED);
	float FLIGHT_THROTTLE = KLNDFACTOR * data.THRR;
	
	bool BSTRAFERIGHT = (BFLTMODE && tmwj->buttonPressed(TMWJ::H3R));
	bool BSTRAFELEFT = (BFLTMODE && tmwj->buttonPressed(TMWJ::H3L));
	bool BSTRAFEUP = (BFLTMODE && tmwj->buttonPressed(TMWJ::H3U));
	bool BSTRAFEDOWN = (BFLTMODE && tmwj->buttonPressed(TMWJ::H3D));
	float FLIGHT_STRAFE_LAT = BGNDMODE ? 0.0f : (BSTRAFELEFT ? -1.0f : (BSTRAFERIGHT ? 1.0f : (KLNDFACTOR * 0.5f * (data.BRKR-data.BRKL))));
	float FLIGHT_STRAFE_VERT = BGNDMODE ? 0.0f : (BSTRAFEDOWN ? -1.0f : (BSTRAFEUP ? 1.0f : KLNDFACTOR * data.THRL));
	
	// set outputs
	vj1->setAxis(SC1::AxisFlightRoll,FLIGHT_ROLL);
	vj1->setAxis(SC1::AxisFlightPitch,FLIGHT_PITCH);
	vj1->setAxis(SC1::AxisFlightYaw,FLIGHT_YAW);
	vj1->setAxis(SC1::AxisFlightThrottle,FLIGHT_THROTTLE);
	vj1->setAxis(SC1::AxisFlightStrafeLat,FLIGHT_STRAFE_LAT);
	vj1->setAxis(SC1::AxisFlightStrafeVertical,FLIGHT_STRAFE_VERT);
}

// GET LANDING FACTOR /////////////////////////////////////////////////////////
float Profile::getLandingFactor(bool bLndMode) const
{
	// get raw inputs
	bool BSHIFTR = tmwj->buttonPressed(TMWJ::S4);
	bool BMSR = tmwt->buttonPressed(TMWT::MSR);
	bool BMSL = tmwt->buttonPressed(TMWT::MSL);
	bool BMSU = tmwt->buttonPressed(TMWT::MSU);
	
	// integrate -1 or +1 function of button pressed
	static Integrator integ_lnd_factor{0.3f,-1.0f,1.0f,this->timeStep()};
	static PulseOnRising risingMSU;
	bool bResetLndFactor = (BSHIFTR && risingMSU(BMSU));
	float integInputTemp = (BMSL && BSHIFTR) ? -1.0f : ((BMSR && BSHIFTR) ? 1.0f : 0.0f);
	float integOutput1 = integ_lnd_factor(kIntLndFactor*integInputTemp,bResetLndFactor,0.3f);
	
	// apply curve (for exponential sensitivity)
	static CurveExpNotCentered curve_KLNDFACTOR{0.0f,0.0f,2.8f,0.0f};
	float integOutput2 = curve_KLNDFACTOR.run(integOutput1);
	
	// range modification: from -1->+1 to kIntLndFactorMin->1
	float kLndFactorTemp = kIntLndFactorMin + (1.0f-kIntLndFactorMin) * 0.5f * (1.0f+integOutput2);
	
	// rate limitation
	static RateLimiter rlimLdnFactor{kIntLndFactorRlim,kLndFactorTemp,this->timeStep()};
	float KLNDFACTOR = rlimLdnFactor(bLndMode ? kLndFactorTemp : 1.0f);
	return KLNDFACTOR;
}






// PROCESS SPEED MANAGEMENT ///////////////////////////////////////////////////
void Profile::processSpeedManagement() const
{
	// get raw inputs
	bool BSHIFTR = tmwj->buttonPressed(TMWJ::S4);
	bool BMSR = tmwt->buttonPressed(TMWT::MSR);
	bool BMSL = tmwt->buttonPressed(TMWT::MSL);
	bool BMSU = tmwt->buttonPressed(TMWT::MSU);
	float THRFC = -tmwt->axisValue(TMWT::THR_FC);
	
	// tempo
	static Tempo tempoSpd{nbCycles500ms};
	TempoOutput tempoSpdOut = tempoSpd(BMSU);
	static CrenelOnRising crenelSpdlim{nbCyclesPulseButton,true};
	static CrenelOnRising crenelCrzCtl{nbCyclesPulseButton,true};
	bool BSPDLIMTOGGLE = crenelSpdlim(!BSHIFTR && tempoSpdOut.shortPress);
	bool BCRZCTLTOGGLE = crenelCrzCtl(!BSHIFTR && tempoSpdOut.longPress);

	// integrate -1 or +1 function of button pressed
	static Integrator integ_spdlim{0.0f,-1.0f,1.0f,this->timeStep()};
	float integInput = (BMSL && !BSHIFTR) ? -1.0f : ((BMSR && !BSHIFTR) ? 1.0f : 0.0f);
	float integOutput = integ_spdlim(kIntSpdLim*integInput);
	static CurveExpNotCentered curve_SPDLIM{0.0f,0.0f,2.5f,0.0f};
	float spdlim = curve_SPDLIM.run(integOutput);
	
	// set outputs
	vj1->setAxis(SC1::AxisFlightSpeedLimit,spdlim);
	vj1->setAxis(SC1::AxisFlightThrLimit,THRFC);
	vj1->setButton(SC1::SpeedLimiterToggle,BSPDLIMTOGGLE);
	vj1->setButton(SC1::CruiseControlToggle,BCRZCTLTOGGLE);
}

// PROCESS OTHER FLIGHT CONTROLS //////////////////////////////////////////////
void Profile::processOtherFlightControls() const
{
	bool BFLTMODE = (tmwt->buttonPressed(TMWT::APAH) || tmwt->buttonPressed(TMWT::APPAT));
	bool BSHIFTL = tmwt->buttonPressed(TMWT::MSD);
	
	// decoupled
	bool bTogglesInhibition = tmwt->buttonPressed(TMWT::LDGH);
	bool BBSF = tmwt->buttonPressed(TMWT::BSF);
	static PulseOnRising risingBsf;
	static PulseOnFalling fallingBsf;
	bool decoupledPulse = ((risingBsf(BBSF) || fallingBsf(BBSF)) && !bTogglesInhibition && BFLTMODE);
	static CrenelOnRising risingDecoupled{nbCyclesPulseButton,true};
	bool BDECOUPLEDTOGGLE = risingDecoupled(decoupledPulse);
	
	// GForce safety
	static PulseOnRising risingH1L;
	bool H1L_pulse = risingH1L(tmwj->buttonPressed(TMWJ::H1L));
	bool gForceTemp = (H1L_pulse && BFLTMODE && BSHIFTL);
	static CrenelOnRising crenelGforce{nbCyclesPulseButton,true};
	bool BGFORCESAFETYTOGGLE = crenelGforce(gForceTemp);
	
	// ESP
	static PulseOnRising risingH1R;
	bool H1R_pulse = risingH1R(tmwj->buttonPressed(TMWJ::H1R));
	bool espTemp = (H1R_pulse && BFLTMODE && BSHIFTL);
	static CrenelOnRising crenelEsp{nbCyclesPulseButton,true};
	bool ESPTOGGLE = crenelEsp(espTemp);
	
	// landing
	bool BAPENG = tmwt->buttonPressed(TMWT::APENG);
	static Tempo tempoLanding{nbCycles500ms};
	TempoOutput tempoLandingOut = tempoLanding(BAPENG);
	static CrenelOnRising risingLngToggle{nbCyclesPulseButton,true};
	bool BLNDSYSTOGGLE = risingLngToggle(BFLTMODE && tempoLandingOut.shortPress);
	bool BSETAUTOLAND = (BFLTMODE && tempoLandingOut.longPress);
	static PulseOnFalling fallingAutoland;
	bool BRESETAUTOLAND = fallingAutoland(BFLTMODE && BAPENG);
	static FlipFlop flipFlopAutoland{true,false};
	bool BAUTOLAND = flipFlopAutoland(BSETAUTOLAND,BRESETAUTOLAND);
	
	// other
	bool BAFTERBURNER = (BFLTMODE && tmwt->buttonPressed(TMWT::SPDB));
	bool BSPACEBRAKE = (BFLTMODE && tmwt->buttonPressed(TMWT::BSB));
	bool QTSYSTOGGLE = (BFLTMODE && tmwt->buttonPressed(TMWT::CHB));
	bool QTDRIVE = (BFLTMODE && tmwt->buttonPressed(TMWT::CHF));
	bool BMATCHTGTVELOCITY = (BFLTMODE && tmwj->buttonPressed(TMWJ::H1U));
	
	// set outputs
	vj1->setButton(SC1::DecoupledModeToggle,BDECOUPLEDTOGGLE);
	vj1->setButton(SC1::GForceSafetyToggle,BGFORCESAFETYTOGGLE);
	vj1->setButton(SC1::ESPToggle,ESPTOGGLE);
	vj1->setButton(SC1::Afterburner,BAFTERBURNER);
	vj1->setButton(SC1::SpaceBrake,BSPACEBRAKE);
	vj1->setButton(SC1::QuantumTravelSystemToggle,QTSYSTOGGLE);
	vj1->setButton(SC1::QuantumDrive,QTDRIVE);
	vj1->setButton(SC1::MatchTargetVelocity,BMATCHTGTVELOCITY);
	vj1->setButton(SC1::LandingSystemToggle,BLNDSYSTOGGLE);
	vj1->setButton(SC1::Autoland,BAUTOLAND);
}

// PROCESS TARGETING //////////////////////////////////////////////////////////
void Profile::processTargeting() const
{
	// get raw inputs
	bool BSHIFTL = tmwt->buttonPressed(TMWT::MSD);
	bool BH4L = tmwj->buttonPressed(TMWJ::H4L);
	bool BH4U = tmwj->buttonPressed(TMWJ::H4U);
	bool BH4R = tmwj->buttonPressed(TMWJ::H4R);
	bool BH4D = tmwj->buttonPressed(TMWJ::H4D);
	bool BS1 = tmwj->buttonPressed(TMWJ::S1);
	
	static PulseOnRising risingH4L, risingH4U, risingH4R, risingH4D, risingBS1;
	bool H4L_pulse = risingH4L(BH4L);
	bool H4U_pulse = risingH4U(BH4U);
	bool H4R_pulse = risingH4R(BH4R);
	bool H4D_pulse = risingH4D(BH4D);
	bool BS1_pulse = risingBS1(BS1);
	
	// get the targeting mode
	static TargetingMode targetingMode = All;
	if (BSHIFTL && H4L_pulse) {targetingMode = Pinned;}
	else if (BSHIFTL && H4U_pulse) {targetingMode = Hostiles;}
	else if (BSHIFTL && H4R_pulse) {targetingMode = All;}
	else if (BSHIFTL && H4D_pulse) {targetingMode = Friends;}
	
	// actions depending on targeting mode
	static CrenelOnRising crenelNextPinTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPrevPinTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelNextAllTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPrevAllTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelNextHstTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPrevHstTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelNextFrdTgt{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPrevFrdTgt{nbCyclesPulseButton,true};
	bool BNEXTPINTGT = crenelNextPinTgt(targetingMode == Pinned && H4R_pulse && !BSHIFTL);
	bool BPREVPINTGT = crenelPrevPinTgt(targetingMode == Pinned && H4L_pulse && !BSHIFTL);
	bool BNEXTALLTGT = crenelNextAllTgt(targetingMode == All && H4R_pulse && !BSHIFTL);
	bool BPREVALLTGT = crenelPrevAllTgt(targetingMode == All && H4L_pulse && !BSHIFTL);
	bool BNEXTHSTTGT = crenelNextHstTgt(targetingMode == Hostiles && H4R_pulse && !BSHIFTL);
	bool BPREVHSTTGT = crenelPrevHstTgt(targetingMode == Hostiles && H4L_pulse && !BSHIFTL);
	bool BNEXTFRDTGT = crenelNextFrdTgt(targetingMode == Friends && H4R_pulse && !BSHIFTL);
	bool BPREVFRDTGT = crenelPrevFrdTgt(targetingMode == Friends && H4L_pulse && !BSHIFTL);
	
	// other
	static CrenelOnRising crenelTgtNearestHst{nbCyclesPulseButton,true};
	static CrenelOnRising crenelReticleFocus{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPinTgt{nbCyclesPulseButton,true};
	bool BTGTNEARESTHST = crenelTgtNearestHst(BS1_pulse && BSHIFTL);
	bool BRETICLEFOCUS = crenelReticleFocus(BS1_pulse && !BSHIFTL);
	bool BPINTGT = crenelPinTgt(H4D_pulse && !BSHIFTL);
	
	// set outputs
	vj1->setButton(SC1::CyclePinnedTargets,BNEXTPINTGT);
	vj1->setButton(SC1::CyclePinnedTargetsBack,BPREVPINTGT);
	vj1->setButton(SC1::CycleAllTargets,BNEXTALLTGT);
	vj1->setButton(SC1::CycleAllTargetsBack,BPREVALLTGT);
	vj1->setButton(SC1::CycleHostileTargets,BNEXTHSTTGT);
	vj1->setButton(SC1::CycleHostileTargetsBack,BPREVHSTTGT);
	vj1->setButton(SC1::CycleFriendlyTargets,BNEXTFRDTGT);
	vj1->setButton(SC1::CycleFriendlyTargetsBack,BPREVFRDTGT);
	vj1->setButton(SC1::TargetNearestHostile,BTGTNEARESTHST);
	vj1->setButton(SC1::ReticleFocus,BRETICLEFOCUS);
	vj1->setButton(SC1::PinFocusedTarget,BPINTGT);
}

// PROCESS SCAN ///////////////////////////////////////////////////////////////
void Profile::processScan() const
{
	// get raw inputs
	bool BSCANONCS = tmwt->buttonPressed(TMWT::APUOFF);
	bool BCSL = tmwt->buttonPressed(TMWT::CSL);
	bool BCSU = tmwt->buttonPressed(TMWT::CSU);
	bool BCSR = tmwt->buttonPressed(TMWT::CSR);
	bool BCSD = tmwt->buttonPressed(TMWT::CSD);
	
	// ping
	bool BSCANPING = (BSCANONCS && BCSD);
	static PulseOnRising risingCSL, risingCSR;
	bool CSL_pulse = risingCSL(BCSL);
	bool CSR_pulse = risingCSR(BCSR);
	static CrenelOnRising crenelScanIncAngle{nbCyclesPulseButton,true};
	static CrenelOnRising crenelScanDecAngle{nbCyclesPulseButton,true};
	bool BSCANINCANGLE = crenelScanIncAngle(BSCANONCS && CSR_pulse);
	bool BSCANDECANGLE = crenelScanDecAngle(BSCANONCS && CSL_pulse);
	
	// scan mode and scan activation
	static Tempo tempoScan{nbCycles500ms};
	TempoOutput tempoScanOut = tempoScan(BCSU);
	static CrenelOnRising crenelScanModelToggle{nbCyclesPulseButton,true};
	bool BSCANMODETOGGLE = crenelScanModelToggle(BSCANONCS && tempoScanOut.shortPress);
	static PulseOnFalling fallingCSUp;
	bool bResetActScan = fallingCSUp(BSCANONCS && BCSU);
	static FlipFlop flipFlopScan{true,false};
	bool BACTSCAN = flipFlopScan(BSCANONCS && tempoScanOut.longPress, bResetActScan);
	
	// set outputs
	vj2->setButton(SC2::ScanningRadarPing,BSCANPING);
	vj2->setButton(SC2::ScanningIncRadarAngle,BSCANINCANGLE);
	vj2->setButton(SC2::ScanningDecRadarAngle,BSCANDECANGLE);
	vj2->setButton(SC2::ScanningModeToggle,BSCANMODETOGGLE);
	vj2->setButton(SC2::ActivateScanning,BACTSCAN);
}
// PROCESS WEAPONS AND CM /////////////////////////////////////////////////////
void Profile::processWeaponsAndCm() const
{
	// get raw inputs
	bool BSHIFTL = tmwt->buttonPressed(TMWT::MSD);
	bool BTG1 = tmwj->buttonPressed(TMWJ::TG1);
	bool BTG2 = tmwj->buttonPressed(TMWJ::TG2);
	bool BS3  = tmwj->buttonPressed(TMWJ::S3);
	bool BH4P = tmwj->buttonPressed(TMWJ::H4P);
	bool BH2L = tmwj->buttonPressed(TMWJ::H2L);
	bool BH2R = tmwj->buttonPressed(TMWJ::H2R);
	bool BS2  = tmwj->buttonPressed(TMWJ::S2);
	bool BH4U = tmwj->buttonPressed(TMWJ::H4U);
	
	// missiles
	bool BLAUNCHMISS = (!BSHIFTL && BS2);
	
	static PulseOnRising risingH4U;
	bool H4U_pulse = risingH4U(BH4U);
	static CrenelOnRising crenelLockMissile{nbCyclesPulseButton,true};
	bool BACQMISSLOCK = crenelLockMissile(!BSHIFTL && H4U_pulse);
	
	static PulseOnRising risingS2;
	bool S2_pulse = risingS2(BS2);
	static CrenelOnRising crenelUnlockMissile{nbCyclesPulseButton,true};
	bool BUNLOCKMISS = crenelUnlockMissile(BSHIFTL && S2_pulse);
	
	// set outputs
	vj1->setButton(SC1::FireGroup1, BTG1);
	vj1->setButton(SC1::FireGroup2, BTG2 || BS3);
	vj1->setButton(SC1::FireGroup3, false);
	vj1->setButton(SC1::CycleGimbalMode, BH4P);
	vj1->setButton(SC1::LaunchMissile,BLAUNCHMISS);
	vj1->setButton(SC1::AcquireMissileLock,BACQMISSLOCK);
	vj1->setButton(SC1::UnlockMissile,BUNLOCKMISS);
	vj2->setButton(SC2::CycleCounterMeasures, BH2L);
	vj2->setButton(SC2::LaunchCounterMeasures, BH2R);
}
// PROCESS POWER //////////////////////////////////////////////////////////////
void Profile::processPower() const
{
	// get raw inputs
	bool BSHIFTR = tmwj->buttonPressed(TMWJ::S4);
	bool BPWRONCS = tmwt->buttonPressed(TMWT::APUON);
	bool BCSL = tmwt->buttonPressed(TMWT::CSL);
	bool BCSU = tmwt->buttonPressed(TMWT::CSU);
	bool BCSR = tmwt->buttonPressed(TMWT::CSR);
	bool BCSD = tmwt->buttonPressed(TMWT::CSD);
	bool BEORIGN = tmwt->buttonPressed(TMWT::EORIGN);
	bool BEORMOTOR = tmwt->buttonPressed(TMWT::EORMOTOR);
	bool BEACON = tmwt->buttonPressed(TMWT::EACON);
	bool BRDRNRM = tmwt->buttonPressed(TMWT::RDRNRM);
	bool BLTB = tmwt->buttonPressed(TMWT::LTB);
	bool bTogglesInhibition = tmwt->buttonPressed(TMWT::LDGH);
	
	// flight ready and power off
	static CrenelOnRising crenelFlightReady{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPowerOff{nbCyclesPulseButton,true};
	bool BFLIGHTREADY = crenelFlightReady(BEORIGN);
	bool BPOWEROFF = crenelPowerOff(BEORMOTOR);
	
	// increase / decrease
	bool BINCREASEPOWER = (BPWRONCS && BSHIFTR && BCSR);
	bool BDECREASEPOWER = (BPWRONCS && BSHIFTR && BCSL);
	
	// distribution changes
	static PulseOnRising risingCSL, risingCSU, risingCSR, risingCSD;
	bool CSL_pulse = risingCSL(BCSL);
	bool CSU_pulse = risingCSU(BCSU);
	bool CSR_pulse = risingCSR(BCSR);
	bool CSD_pulse = risingCSD(BCSD);
	static CrenelOnRising crenelPwrInc1{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPwrInc2{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPwrInc3{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPwrResetDist{nbCyclesPulseButton,true};
	bool POWERPRESET1INC = crenelPwrInc1(BPWRONCS && !BSHIFTR && CSL_pulse);
	bool POWERPRESET2INC = crenelPwrInc2(BPWRONCS && !BSHIFTR && CSD_pulse);
	bool POWERPRESET3INC = crenelPwrInc3(BPWRONCS && !BSHIFTR && CSR_pulse);
	bool RESETPOWERDISTRIB = crenelPwrResetDist(BPWRONCS && !BSHIFTR && CSU_pulse);
	
	// switches
	static PulseOnRising risingEac, risingRdr, risingLtb;
	static PulseOnFalling fallingEac, fallingRdr;
	bool switch1 = (risingEac(BEACON) || fallingEac(BEACON)) && !bTogglesInhibition;
	bool switch2 = (risingRdr(BRDRNRM) || fallingRdr(BRDRNRM)) && !bTogglesInhibition;
	bool switch3 = risingLtb(BLTB) && !bTogglesInhibition;
	static CrenelOnRising crenelPwrSwitch1{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPwrSwitch2{nbCyclesPulseButton,true};
	static CrenelOnRising crenelPwrSwitch3{nbCyclesPulseButton,true};
	bool BPOWERPRESET1TOGGLE = crenelPwrSwitch1(switch1);
	bool BPOWERPRESET2TOGGLE = crenelPwrSwitch2(switch2);
	bool BPOWERPRESET3TOGGLE = crenelPwrSwitch3(switch3);
	
	// set outputs
	vj1->setButton(SC1::FlightReady,BFLIGHTREADY);
	vj1->setButton(SC1::PowerOff,BPOWEROFF);
	vj1->setButton(SC1::IncreasePower,BINCREASEPOWER);
	vj1->setButton(SC1::DecreasePower,BDECREASEPOWER);
	vj1->setButton(SC1::PowerPreset1Increase,POWERPRESET1INC);
	vj1->setButton(SC1::PowerPreset2Increase,POWERPRESET2INC);
	vj1->setButton(SC1::PowerPreset3Increase,POWERPRESET3INC);
	vj1->setButton(SC1::ResetPowerDistribution,RESETPOWERDISTRIB);
	vj1->setButton(SC1::PowerPreset1Toggle,BPOWERPRESET1TOGGLE);
	vj1->setButton(SC1::PowerPreset2Toggle,BPOWERPRESET2TOGGLE);
	vj1->setButton(SC1::PowerPreset3Toggle,BPOWERPRESET3TOGGLE);
}
// PROCESS SHIELDS ////////////////////////////////////////////////////////////
void Profile::processShields() const
{
	// get raw inputs
	bool BSC = tmwt->buttonPressed(TMWT::SC);
	float SCX = tmwt->axisValue(TMWT::SCX);
	float SCY = tmwt->axisValue(TMWT::SCY);
	
	// shield mode and reset distrib
	static Tempo tempoShields{nbCycles500ms};
	TempoOutput tempoShieldsOut = tempoShields(BSC);
	static bool BSHDHORZ = bShieldsHorzInit;
	if (tempoShieldsOut.shortPress) {BSHDHORZ = !BSHDHORZ;}
	static CrenelOnRising crenelResetDistrib{nbCyclesPulseButton,true};
	bool BRESETSHDLEVELS = crenelResetDistrib(tempoShieldsOut.longPress);
	
	// actions
	bool BSHDRAISELEFT  = (SCX < -0.84);
	bool BSHDRAISERIGHT = (SCX >  0.84);
	bool BSHDRAISEBACK  = (SCY < -0.84 && BSHDHORZ);
	bool BSHDRAISEFRONT = (SCY >  0.84 && BSHDHORZ);
	bool BSHDRAISEUP    = (SCY < -0.84 && !BSHDHORZ);
	bool BSHDRAISEDOWN  = (SCY >  0.84 && !BSHDHORZ);
	
	// set outputs
	vj2->setButton(SC2::ShieldRaiseLeft,BSHDRAISELEFT);
	vj2->setButton(SC2::ShieldRaiseRight,BSHDRAISERIGHT);
	vj2->setButton(SC2::ShieldRaiseFront,BSHDRAISEFRONT);
	vj2->setButton(SC2::ShieldRaiseBack,BSHDRAISEBACK);
	vj2->setButton(SC2::ShieldRaiseTop,BSHDRAISEUP);
	vj2->setButton(SC2::ShieldRaiseBottom,BSHDRAISEDOWN);
	vj2->setButton(SC2::ResetShieldsLevels,BRESETSHDLEVELS);
}
// PROCESS GROUND /////////////////////////////////////////////////////////////
void Profile::processGround(const AxesData &data) const
{
	// get raw inputs
	bool BGNDMODE = tmwt->buttonPressed(TMWT::APALT);
	bool BS4 = tmwj->buttonPressed(TMWJ::S4);
	
	// throttle
	float coeff = 0.5f / lim<float>(1.0f-BRKR_LDZ-BRKR_RDZ,0.1f,1.0f);
	float thr1 = (bUseBrkPedForGnd ? data.BRKR : data.THRR);
	float thr2 = coeff * (1.0f+thr1-2.0f*BRKR_LDZ);
	float GROUND_THROTTLE = !BGNDMODE ? 0.0f : (data.THRL>0.0f ? lim<float>(thr2,0.0f,1.0f) : lim<float>(-thr2,-1.0f,0.0f));
	
	// other
	bool BHORN = (BGNDMODE && BS4);
	bool BBRAKE = (BGNDMODE && data.BRKL > -0.8f);
	float GROUND_LAT = (BGNDMODE ? data.JOYX : 0.0f);
	
	// set outputs
	vj2->setAxis(SC2::AxisGroundThrottle,GROUND_THROTTLE);
	vj2->setAxis(SC2::AxisGroundLat,GROUND_LAT);
	vj2->setButton(SC2::Brake,BBRAKE);
	vj2->setButton(SC2::Horn,BHORN);
}
// PROCESS VIEW ///////////////////////////////////////////////////////////////
void Profile::processView() const
{
	// get raw inputs
	bool BSHIFTL = tmwt->buttonPressed(TMWT::MSD);
	bool BH1R = tmwj->buttonPressed(TMWJ::H1R);
	bool BH1D = tmwj->buttonPressed(TMWJ::H1D);
	bool BH1L = tmwj->buttonPressed(TMWJ::H1L);
	/*bool BPSB = tmwt->buttonPressed(TMWT::PSB);
	
	// track IR
	static Tempo tempoTrackIr{nbCycles500ms};
	TempoOutput tempoTrackIrOut = tempoTrackIr(BPSB);
	static CrenelOnRising crenelTrackIrCenter{nbCyclesPulseButton,true};
	bool BTRKIRCENTER = crenelTrackIrCenter(tempoTrackIrOut.shortPress || tempoTrackIrOut.longPress);
	
	static Delay<bool> delayTrackIrPause{2*nbCyclesPulseButton};
	static CrenelOnRising crenelTrackIrPause{nbCyclesPulseButton,true};
	bool BTRKIRPAUSE = crenelTrackIrPause(delayTrackIrPause(tempoTrackIrOut.longPress));*/
	
	// set outputs
	vj2->setButton(SC2::ZoomIn, BH1L && !BSHIFTL);
	vj2->setButton(SC2::ZoomOut, BH1R && !BSHIFTL);
	vj2->setButton(SC2::LookBehind, BH1D);
}
// PROCESS LEDS ///////////////////////////////////////////////////////////////
void Profile::processLeds(bool bInit) const
{
	// get raw inputs
	bool BBSF = tmwt->buttonPressed(TMWT::BSF);
	bool BLDGH = tmwt->buttonPressed(TMWT::LDGH);
	bool BDECOUPLED = BBSF;
	
	// leds inhibition
	static bool BINHIBDECLEDS = false;
	static PulseOnRising risingInhib, risingDecoupled;
	if (risingDecoupled(BDECOUPLED)) {BINHIBDECLEDS = false;}
	else if (BDECOUPLED && risingInhib(BLDGH)) {BINHIBDECLEDS = true;}
	
	// duration the decoupled mode was on
	static float timeStepInSec = 0.001 * this->timeStep();
	static float duration = 0.0f;
	bool bNoInteg = (bInit || !BDECOUPLED);
	if (bNoInteg) {duration = 0.0f;}
	else {duration += timeStepInSec;}
	
	// leds flashing logic
	bool ledsOnInterm = (duration > dtLedsMin && modulo(duration-dtLedsMin,0.0f,dtLedsCycle) < 1.0f);
	bool ledsOffInterm = (duration > dtLedsMin && modulo(duration-dtLedsMin-dtLedsFlash,0.0f,dtLedsCycle) < 1.0f);
	static PulseOnRising risingLedsOn, risingLedsOff, risingNoInteg;
	bool BSBRIGHTNESS5 = (!BINHIBDECLEDS && risingLedsOn(ledsOnInterm));
	bool BSBRIGHTNESS0 = (BINHIBDECLEDS || risingLedsOff(ledsOffInterm) || risingNoInteg(bNoInteg));
	
	// set outputs
	if (BSBRIGHTNESS5) {tmwt->setData("BRIGHTNESS",5);}
	else if (BSBRIGHTNESS0) {tmwt->setData("BRIGHTNESS",0);}
}
// PROCESS OTHER //////////////////////////////////////////////////////////////
void Profile::processOther() const
{
	// get raw inputs
	bool bTogglesInhibition = tmwt->buttonPressed(TMWT::LDGH);
	bool BH2U = tmwj->buttonPressed(TMWJ::H2U);
	bool BH2D = tmwj->buttonPressed(TMWJ::H2D);
	bool BEFLNORM = tmwt->buttonPressed(TMWT::EFLNORM);
	bool BEFRNORM = tmwt->buttonPressed(TMWT::EFRNORM);
	
	// headlights and broadcast ID
	static PulseOnRising risingEfl, risingEfr;
	static PulseOnFalling fallingEfl, fallingEfr;
	bool bSwitchingEflNorm = (risingEfl(BEFLNORM) || fallingEfl(BEFLNORM));
	bool bSwitchingEfrNorm = (risingEfr(BEFRNORM) || fallingEfr(BEFRNORM));
	static CrenelOnRising crenelHeadlights{nbCyclesPulseButton,true};
	static CrenelOnRising crenelBroadcastId{nbCyclesPulseButton,true};
	bool BHEADLIGHTSTOGGLE = crenelHeadlights(bSwitchingEflNorm && !bTogglesInhibition);
	bool BIDBROADCASTTOGGLE = crenelBroadcastId(bSwitchingEfrNorm && !bTogglesInhibition);
	
	// set outputs
	vj2->setButton(SC2::HailTarget,BH2U);
	vj2->setButton(SC2::PushToTalk,BH2D);
	vj2->setButton(SC2::HeadlightsToggle,BHEADLIGHTSTOGGLE);
	vj2->setButton(SC2::PersonalIdBroadCastToggle,BIDBROADCASTTOGGLE);
}

