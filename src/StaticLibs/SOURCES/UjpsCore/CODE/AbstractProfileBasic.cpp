#include "AbstractProfileBasic.h"
#include "RealJoysticksManager.h"
#include "RemoteJoystickServer.h"
#include "VirtualJoystick.h"

#include <QCoreApplication>
#include <vector>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  PLAY
//  STOP
//  RUN
//  IS INIT COMPLETE
//
//  REGISTER REAL JOYSTICK
//  REGISTER REMOTE JOYSTICK
//  SLOT REMOTE JOYSTICK CONNECTED
//  REGISTER VIRTUAL JOYSTICK
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AbstractProfileBasic::AbstractProfileBasic() : AbstractProfile{}
{
	m_bFirstStep = true;
}

AbstractProfileBasic::~AbstractProfileBasic()
{
	this->stop();
}

// PLAY ///////////////////////////////////////////////////////////////////////
bool AbstractProfileBasic::play()
{
	m_bFirstStep = true;
	if (!this->setupJoysticks()) {return false;}
	return true;
}

// STOP ///////////////////////////////////////////////////////////////////////
void AbstractProfileBasic::stop()
{
	// not doing qDeleteAll on m_realJoysticksNoRemote, on purpose:
	// the RealJoysticksManager has their ownership,
	// and it is reset only if profile is unloaded
	
	qDeleteAll(m_remoteJoysticks);
	qDeleteAll(m_virtualJoysticks);
	
	m_realJoysticksNoRemote.clear();
	m_remoteJoysticks.clear();
	m_virtualJoysticks.clear();
}

// RUN ////////////////////////////////////////////////////////////////////////
void AbstractProfileBasic::run()
{
	// read the states of each real joystick
	for (AbstractRealJoystick *rj : m_realJoysticksNoRemote) {rj->readGameController();}
	for (AbstractRealJoystick *rj : m_remoteJoysticks)       {rj->readGameController();}
	
	// core of the loop
	this->runOneStep(m_bFirstStep);
	
	// flush virtual then real joysticks
	for (VirtualJoystick *vj : m_virtualJoysticks)           {vj->flush();} // send HID report to vJoy devices
	for (AbstractRealJoystick *rj : m_realJoysticksNoRemote) {rj->flush();} // implementation defined
	for (AbstractRealJoystick *rj : m_remoteJoysticks)       {rj->flush();} // implementation defined
	
	m_bFirstStep = false;
}

// IS INIT COMPLETE ///////////////////////////////////////////////////////////
bool AbstractProfileBasic::isInitComplete() const
{
	auto isConnected = [] (RemoteJoystickServer *rjs) {return rjs->isConnected();};
	return std::all_of(m_remoteJoysticks.begin(),m_remoteJoysticks.end(),isConnected);
}






// REGISTER REAL JOYSTICK /////////////////////////////////////////////////////
AbstractRealJoystick* AbstractProfileBasic::registerRealJoystick(const QString &description, int num)
{
	RealJoysticksManager *rjm = this->realJoysticksManager();
	if (!rjm) {return nullptr;}
	
	AbstractRealJoystick *rj = rjm->joystick(description,num);
	if (!rj) {return nullptr;}
	
	m_realJoysticksNoRemote.push_back(rj);
	return rj;
}

// REGISTER REMOTE JOYSTICK ///////////////////////////////////////////////////
void AbstractProfileBasic::registerRemoteJoystick(RemoteJoystickServer *rjs)
{
	if (!rjs) {return;}
	QObject::connect(rjs, SIGNAL(connected()),    this, SLOT(slotRemoteJoystickConnected()));
	QObject::connect(rjs, SIGNAL(disconnected()), this, SIGNAL(remoteJoystickDisconnected()));
	m_remoteJoysticks.push_back(rjs);
}

// SLOT REMOTE JOYSTICK CONNECTED /////////////////////////////////////////////
void AbstractProfileBasic::slotRemoteJoystickConnected()
{
	if (this->isInitComplete())
		emit asyncInitComplete();
}

// REGISTER VIRTUAL JOYSTICK //////////////////////////////////////////////////
VirtualJoystick* AbstractProfileBasic::registerVirtualJoystick(uint id)
{
	try
	{
		VirtualJoystick *vj = new VirtualJoystick{id};
		QObject::connect(vj, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
		m_virtualJoysticks.push_back(vj);
		return vj;
	}
	catch (std::exception &e)
	{
		emit message(e.what(),Qt::red);
		return nullptr;
	}
}

