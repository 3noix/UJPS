#include "Profile.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoystick.h"
#include "WindowsKeys.h"
using namespace Keys;

#include "EnhancedJoystick.h"
#include "RemoteJoystickServer.h"
#include "RealJoysticksManager.h"
#include "ThrustmasterWarthogJoystick.h"
#include <QCoreApplication>

using VJOY = VirtualJoystick;
namespace TMWJ = ThrustmasterWarthogJoystick;


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
	rjse = nullptr;
	vj1  = nullptr;
}

Profile::~Profile()
{
	this->stop();
	if (rjm) {delete rjm; rjm = nullptr;}
}








// STOP ///////////////////////////////////////////////////////////////////////
bool Profile::stop()
{
	if (tmwj) {delete tmwj; tmwj = nullptr;}
	if (rjse) {delete rjse; rjse = nullptr;}
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
	if (rj1) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red); return false;}
	
	emit message("Now connect the client application for the remote controller", Qt::black);
	RemoteJoystickServer *rj2 = new RemoteJoystickServer{"TouchScreen2",32241,100};
	QObject::connect(rj2,SIGNAL(message(QString,QColor)),this,SIGNAL(message(QString,QColor)));
	if (!rj2) {return false;}
	
	tmwj = new EnhancedJoystick(rj1,false);
	rjse = new EnhancedJoystick(rj2,true);
	
	this->registerRealJoystick(tmwj);
	this->registerRealJoystick(rjse);
	
	
	// virtual joystick(s) setup
	vj1 = new VirtualJoystick(1,128);
	QObject::connect(vj1,SIGNAL(message(QString,QColor)),this,SIGNAL(message(QString,QColor)));
	emit message("Virtual joystick 1 configured",Qt::black);
	this->registerVirtualJoystick(vj1);
	
	
	return (tmwj && rjse && vj1);
}

// RUN FIRST STEP /////////////////////////////////////////////////////////////
void Profile::runFirstStep()
{
	vj1->resetReport();
	
	MapAxisRelative(tmwj, TMWJ::JOYY, AllLayers, vj1, VJOY::Z, 4000.0f);
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this](){rjse->setData("button3",true);}});
	
	MapButton(rjse, 0, AllLayers, vj1, VJOY::DX1);
	MapButton(rjse, 1, AllLayers, vj1, VJOY::DX2);
	MapAxis(rjse, 0, AllLayers, vj1, VJOY::X);
}


