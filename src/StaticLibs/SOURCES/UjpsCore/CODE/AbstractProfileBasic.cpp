#include "AbstractProfileBasic.h"
#include "RealJoysticksManager.h"
#include "RemoteJoystickTcpServer.h"
#include "RemoteJoystickHttp.h"
#include "UjpsHttpServer.h"
#include "VirtualJoystick.h"

#include <QCoreApplication>
#include <vector>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  PLAY
//  STOP
//  RUN
//  IS INIT COMPLETE
//
//  REGISTER REAL JOYSTICK
//  REGISTER REMOTE JOYSTICK TCP
//  REGISTER REMOTE JOYSTICK HTTP
//  SLOT REMOTE JOYSTICK TCP CONNECTED
//  REGISTER VIRTUAL JOYSTICK
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
AbstractProfileBasic::AbstractProfileBasic() : AbstractProfile{}
{
	m_bFirstStep = true;
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
	
	// not doing qDeleteAll on m_remoteJoysticksHttp, on purpose:
	// the UjpsHttpServer has their ownership
	// and delete them when "close" is called
	
	qDeleteAll(m_remoteJoysticksTcp);
	qDeleteAll(m_virtualJoysticks);
	
	m_realJoysticksNoRemote.clear();
	m_remoteJoysticksTcp.clear();
	m_remoteJoysticksHttp.clear();
	m_virtualJoysticks.clear();
	
	UjpsHttpServer::instance().close();
}

// RUN ////////////////////////////////////////////////////////////////////////
void AbstractProfileBasic::run()
{
	// read the states of each real joystick
	for (AbstractRealJoystick *rj : m_realJoysticksNoRemote) {rj->readGameController();}
	for (AbstractRealJoystick *rj : m_remoteJoysticksTcp)    {rj->readGameController();}
	for (AbstractRealJoystick *rj : m_remoteJoysticksHttp)   {rj->readGameController();}
	
	// core of the loop
	this->runOneStep(m_bFirstStep);
	
	// flush virtual then real joysticks
	for (VirtualJoystick *vj : m_virtualJoysticks)           {vj->flush();} // send HID report to vJoy devices
	for (AbstractRealJoystick *rj : m_realJoysticksNoRemote) {rj->flush();} // implementation defined
	for (AbstractRealJoystick *rj : m_remoteJoysticksTcp)    {rj->flush();} // implementation defined
	//for (AbstractRealJoystick *rj : m_remoteJoysticksHttp)   {rj->flush();} // sending data to them is not supported!
	
	m_bFirstStep = false;
}

// IS INIT COMPLETE ///////////////////////////////////////////////////////////
bool AbstractProfileBasic::isInitComplete() const
{
	for (RemoteJoystickTcpServer *rjs : m_remoteJoysticksTcp)
	{
		if (!rjs->isConnected())
		{return false;}
	}
	
	return true;
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

// REGISTER REMOTE JOYSTICK TCP ///////////////////////////////////////////////
void AbstractProfileBasic::registerRemoteJoystickTcp(RemoteJoystickTcpServer *rjs)
{
	if (!rjs) {return;}
	QObject::connect(rjs, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
	QObject::connect(rjs, SIGNAL(connected()),             this, SLOT(slotRemoteJoystickTcpConnected()));
	QObject::connect(rjs, SIGNAL(disconnected()),          this, SIGNAL(remoteJoystickTcpDisconnected()));
	m_remoteJoysticksTcp.push_back(rjs);
}

// REGISTER REMOTE JOYSTICK HTTP //////////////////////////////////////////////
RemoteJoystickHttp* AbstractProfileBasic::registerRemoteJoystickHttp(const QString &name, uint id, const QString &dirPath)
{
	UjpsHttpServer &httpServer = UjpsHttpServer::instance();
	RemoteJoystickHttp *rjh = httpServer.registerRemoteGuiHttp(name,id,dirPath);
	if (!rjh) {return nullptr;}
	
	m_remoteJoysticksHttp.push_back(rjh);
	httpServer.listen();
	return rjh;
}

// SLOT REMOTE JOYSTICK TCP CONNECTED /////////////////////////////////////////
void AbstractProfileBasic::slotRemoteJoystickTcpConnected()
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

