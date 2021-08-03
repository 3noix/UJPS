#include "Profile.h"
#include "VirtualJoysticks/VirtualJoystick.h"
#include "RealJoysticks/RemoteJoystickServer.h"
#include <QCoreApplication>


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
	remote = nullptr;
	vj1  = nullptr;
}

Profile::~Profile()
{
	this->stop();
}




// STOP ///////////////////////////////////////////////////////////////////////
void Profile::stop()
{
	this->AbstractProfileBasic::stop();
	
	remote = nullptr;
	vj1  = nullptr;
}

// SETUP JOYSTICKS ////////////////////////////////////////////////////////////
bool Profile::setupJoysticks()
{
	Q_INIT_RESOURCE(resources);
	
	emit message("Now connect the remote controller", Qt::black);
	remote = new RemoteJoystickServer{"remote",54321,54322,100,":/RESOURCES/"};
	if (!remote)
	{
		emit message("Failed to create remote joystick server!",Qt::red);
		return false;
	}
	this->registerRemoteJoystick(remote);
	emit message("Use \"" + remote->url() + "\" to access to the remote",Qt::black);
	
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
	vj1->setButton(3,remote->buttonPressed(3));
	vj1->setButton(4,remote->buttonPressed(4));
	vj1->setAxis(0,remote->axisValue(0));
	vj1->setAxis(1,remote->axisValue(1));
}

