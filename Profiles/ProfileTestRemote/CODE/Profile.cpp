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
#include "ThrustmasterWarthogJoystick.h"

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
	tmwj = nullptr;
	rjse = nullptr;
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
	rjse = nullptr;
	vj1  = nullptr;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	// we retrieve pointers on real joysticks we are interested in
	tmwj = this->registerRealJoystick("Joystick - HOTAS Warthog");
	if (tmwj) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red); return false;}
	
	emit message("Now connect the client application for the remote controller", Qt::black);
	RemoteJoystickServer *rjs = new RemoteJoystickServer{"TouchScreen2",32241,100};
	QObject::connect(rjs,SIGNAL(message(QString,QColor)),this,SIGNAL(message(QString,QColor)));
	rjse = this->registerRealJoystick(rjs);
	
	
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
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonPress{},   new ActionCallback{[this](){rjse->setData("button3",true);}});
	Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers, new TriggerButtonRelease{}, new ActionCallback{[this](){rjse->setData("button3",false);}});
	
	MapButton(rjse, 0, AllLayers, vj1, VJOY::DX1);
	MapButton(rjse, 1, AllLayers, vj1, VJOY::DX2);
	MapAxis(rjse, 0, AllLayers, vj1, VJOY::X);
}


