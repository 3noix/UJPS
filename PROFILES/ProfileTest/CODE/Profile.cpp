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
#include <QCoreApplication>

using VJOY = VirtualJoystick;
namespace TMWJ = ThrustmasterWarthogJoystick;
namespace TMWT = ThrustmasterWarthogThrottle;
namespace MFGX = MfgCrosswindRudderPedals;


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
	tmwj = nullptr;
	tmwt = nullptr;
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
	if (tmwj) {delete tmwj; tmwj = nullptr;}
	if (tmwt) {delete tmwt; tmwt = nullptr;}
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
	if (!rjm)
	{
		rjm = new RealJoysticksManager{};
		QString controllersPluginsDirPath = QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/";
		rjm->loadPlugins(QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/");
		QObject::connect(rjm, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
		rjm->searchForControllers();
	}
	AbstractRealJoystick *rj1 = rjm->joystick("Joystick - HOTAS Warthog");
	AbstractRealJoystick *rj2 = rjm->joystick("Throttle - HOTAS Warthog");
	AbstractRealJoystick *rj3 = rjm->joystick("MFG Crosswind V2");
	
	if (rj1) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red);}
	
	if (rj2) {emit message("Warthog throttle detected !",Qt::black);}
	else {emit message("Warthog throttle not detected !",Qt::red);}
	
	if (rj3) {emit message("MFG Crosswind rudder pedals detected !",Qt::black);}
	else {emit message("MFG Crosswind rudder pedals not detected !",Qt::red);}
	
	if (!rj1 || !rj2 || !rj3) {return false;}
	
	tmwj = new EnhancedJoystick(rj1,false);
	tmwt = new EnhancedJoystick(rj2,false);
	mfgx = new EnhancedJoystick(rj3,false);
	
	this->registerRealJoystick(tmwj);
	this->registerRealJoystick(tmwt);
	this->registerRealJoystick(mfgx);
	
	
	// virtual joystick(s) setup
	vj1 = new VirtualJoystick(1,128);
	QObject::connect(vj1,&VirtualJoystick::message,this,&Profile::message);
	emit message("Virtual joystick 1 configured",Qt::black);
	this->registerVirtualJoystick(vj1);
	
	
	return (tmwj && tmwt && mfgx && vj1);
}

// INIT ///////////////////////////////////////////////////////////////////////
void Profile::init()
{
	vj1->resetReport();
	
	MapAxis(mfgx, MFGX::RUDDER, AllLayers, vj1, VJOY::X);
	MapMergeAxes(mfgx, MFGX::BRK_LEFT, 0.5f, mfgx, MFGX::BRK_RIGHT, -0.5f, AllLayers, vj1, VJOY::Y);
	
	MapAxisRelative(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::Z, 4000.0f);
}


