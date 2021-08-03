#include "Profile.h"
#include "UjpsCore/Triggers.h"
#include "UjpsCore/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoysticks/VirtualJoystick.h"
#include "RealJoysticks/EnhancedJoystick.h"
#include "RealJoysticks/RemoteJoystickServer.h"

#include "vJoyDevice.h"
#include "UjpsCore/WindowsKeys.h"
using namespace Keys;
namespace VJOY = vJoyDevice;


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
	rjse = nullptr;
	vj1  = nullptr;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	// virtual joystick(s) setup
	vj1 = this->registerVirtualJoystick(1);
	if (vj1) {emit message("Virtual joystick 1 acquired",Qt::black);}
	else {emit message("Virtual joystick 1 failed to configure",Qt::red);}
	
	// remote joystick
	emit message("Now connect the client application for the remote controller", Qt::black);
	RemoteJoystickServer *rjs = new RemoteJoystickServer{"MFD_remote",0,32241,100};
	rjse = this->registerRemoteJoystick(rjs);
	
	return (rjse && vj1);
}

// RUN FIRST STEP /////////////////////////////////////////////////////////////
void Profile::runFirstStep()
{
	vj1->resetReport();
	for (int i=0; i<28; ++i) {MapButton(rjse,i,AllLayers,vj1,i);}
}

