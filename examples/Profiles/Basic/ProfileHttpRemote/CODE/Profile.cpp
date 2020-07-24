#include "Profile.h"
#include "VirtualJoystick.h"
#include "RemoteJoystickHttp.h"
#include <QCoreApplication>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  STOP
//  SETUP JOYSTICKS
//  RUN ONE STEP
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
Profile::Profile() : AbstractProfileBasic{}
{
	remote = nullptr;
	vj1  = nullptr;
}






// STOP ///////////////////////////////////////////////////////////////////////
void Profile::stop()
{
	remote = nullptr;
	vj1  = nullptr;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	Q_INIT_RESOURCE(resources);
	
	remote = this->registerRemoteJoystickHttp("test",200,":/RESOURCES/");
	if (!remote)
	{
		emit message("Failed to create remote joystick!",Qt::red);
		return false;
	}
	
	emit message("Use \"" + remote->url() + "\" to access to the remote joystick",Qt::black);
	
	// virtual joystick(s) setup
	vj1 = this->registerVirtualJoystick(1);
	if (vj1) {emit message("Virtual joystick 1 acquired",Qt::black);}
	else {emit message("Virtual joystick 1 failed to configure",Qt::red);}
	
	return vj1;
}

// RUN ONE STEP ///////////////////////////////////////////////////////////////
void Profile::runOneStep(bool bInit)
{
	Q_UNUSED(bInit)
	
	vj1->setButton(0,remote->buttonPressed(0));
	vj1->setButton(1,remote->buttonPressed(1));
	vj1->setButton(2,remote->buttonPressed(2));
	vj1->setAxis(0,remote->axisValue(0));
	vj1->setAxis(1,remote->axisValue(1));
}

