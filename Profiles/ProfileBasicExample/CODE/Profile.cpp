#include "Profile.h"

#include "VirtualJoystick.h"
#include "AbstractRealJoystick.h"
#include "ThrustmasterWarthogJoystick.h"
#include "ThrustmasterWarthogThrottle.h"
#include "MfgCrosswindRudderPedals.h"
#include "Controls.h"
#include "Lim.h"

namespace TMWJ = ThrustmasterWarthogJoystick;
namespace TMWT = ThrustmasterWarthogThrottle;
namespace MFGX = MfgCrosswindRudderPedals;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  STOP
//  SETUP JOYSTICKS
//  RUN ONE STEP
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
		
		return;
	}
	
	// retrieve inputs
	//float h1 = tmwj->povValue(TMWJ::HAT1);
	float x = tmwj->axisValue(TMWJ::JOYX);
	float y = tmwj->axisValue(TMWJ::JOYY);
	bool tg1 = tmwj->buttonPressed(TMWJ::TG1);
	
	// computations
	float rollInput = x + y;
	bool lgToggle = !tg1;
	
	// set outputs
	//vj1->setPov(0,h1);
	vj1->setAxis(Controls::AxisRoll,rollInput);
	vj1->setButton(Controls::LandingGear,lgToggle);
}

