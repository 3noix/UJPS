#include "Profile.h"
#include "UjpsCore/Triggers.h"
#include "UjpsCore/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoysticks/VirtualJoystick.h"
#include "RealJoysticks/EnhancedJoystick.h"
#include "RealJoysticks/RemoteJoystickServer.h"

#include "UjpsCore/WindowsKeys.h"
#include "vJoyDevice.h"
#include "ThrustmasterWarthogJoystick.h"
using namespace Keys;
namespace VJOY = vJoyDevice;
namespace TMWJ = ThrustmasterWarthogJoystick;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  STOP
//  SETUP JOYSTICKS
//  RUN FIRST STEP
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
Profile::Profile() : AbstractProfileTarget{}
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
	this->AbstractProfileTarget::stop();
	
	// it is a good idea to set them to nullptr
	tmwj = nullptr;
	rjse = nullptr;
	vj1  = nullptr;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	// we retrieve pointers on real joysticks we are interested in
	tmwj = this->registerRealJoystick(TMWJ::Description);
	if (tmwj) {emit message("Warthog joystick detected !",Qt::black);}
	else {emit message("Warthog joystick not detected !",Qt::red); return false;}
	
	// virtual joystick(s) setup
	vj1 = this->registerVirtualJoystick(1);
	if (vj1) {emit message("Virtual joystick 1 acquired",Qt::black);}
	else {emit message("Virtual joystick 1 failed to configure",Qt::red);}
	
	// remote joystick at last
	emit message("Now connect the client application for the remote controller", Qt::black);
	RemoteJoystickServer *rjs = new RemoteJoystickServer{"TouchScreen2",0,32241,100};
	rjse = this->registerRemoteJoystick(rjs);
	
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
	MapPov(rjse, 0, AllLayers, vj1, VJOY::POV1);
}

