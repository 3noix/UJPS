#include "RemoteJoystickTcpClient.h"
#include "RemoteJoystickTcpMessageTypes.h"
#include <QtWidgets>
#include <QTcpSocket>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  DESCRIPTION
//  BUTTONS COUNT
//  BUTTONS NAMES
//  AXES COUNT
//  AXES NAMES
//  POVS COUNT
//  POVS NAMES
//  SET DATA
//  SET STATE
//  STATE
//
//  SLOT CONNECT
//  SLOT DISCONNECT
//  SLOT SEND BUTTON INFO
//  SLOT SEND AXIS INFO
//  SLOT SEND POV INFO
//
//  SLOT CONNECTED
//  SLOT RECEIVE DATA
//  SLOT DISCONNECTED
//  SLOT ERROR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
RemoteJoystickTcpClient::RemoteJoystickTcpClient(
	const QString &description,
	const QStringList &buttonsNames,
	const QStringList &axesNames,
	const QStringList &povsNames,
	QObject *parent) : QObject{parent}
{
	m_description = description;
	m_buttonsNames = buttonsNames;
	m_axesNames = axesNames;
	m_povsNames = povsNames;
	
	m_hostName = "";
	m_port = 0;
	m_state = State::NotConnected;
	m_tcpSocket = new QTcpSocket{this};
	
	// connections
	connect(m_tcpSocket, SIGNAL(connected()),    this, SLOT(slotConnected()));
	connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	connect(m_tcpSocket, SIGNAL(readyRead()),    this, SLOT(slotReceiveData()));
	connect(m_tcpSocket, SIGNAL(error()),        this, SLOT(slotError()));
}






// DESCRIPTION ////////////////////////////////////////////////////////////////
QString RemoteJoystickTcpClient::description() const
{
	return m_description;
}

// BUTTONS COUNT //////////////////////////////////////////////////////////////
quint8 RemoteJoystickTcpClient::buttonsCount() const
{
	return m_buttonsNames.size();
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList RemoteJoystickTcpClient::buttonsNames() const
{
	return m_buttonsNames;
}

// AXES COUNT /////////////////////////////////////////////////////////////////
quint8 RemoteJoystickTcpClient::axesCount() const
{
	return m_axesNames.size();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList RemoteJoystickTcpClient::axesNames() const
{
	return m_axesNames;
}

// POVS COUNT /////////////////////////////////////////////////////////////////
quint8 RemoteJoystickTcpClient::povsCount() const
{
	return m_povsNames.size();
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList RemoteJoystickTcpClient::povsNames() const
{
	return m_povsNames;
}

// SET DATA ///////////////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::setData(const QString &prop, QVariant v)
{
	emit signalSetData(prop,v);
}

// SET STATE //////////////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::setState(RemoteJoystickTcpClient::State s)
{
	m_state = s;
	emit stateChanged(m_state);
}

// STATE //////////////////////////////////////////////////////////////////////
RemoteJoystickTcpClient::State RemoteJoystickTcpClient::state() const
{
	return m_state;
}






// SLOT CONNECT ///////////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotConnect(const QString &hostName, quint16 port)
{
	m_hostName = hostName;
	m_port = port;
	
	m_tcpSocket->abort();
	m_tcpSocket->connectToHost(m_hostName,m_port);
	this->setState(State::Connecting);
}

// SLOT DISCONNECT ////////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotDisconnect()
{
	m_tcpSocket->disconnectFromHost();
}

// SLOT SEND BUTTON INFO //////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotSendButtonInfo(quint8 button, bool bPressed)
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickTcpMessageType::Button << button << bPressed;
	
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT SEND AXIS INFO ////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotSendAxisInfo(quint8 axis, float axisValue)
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickTcpMessageType::Axis << axis << axisValue;
	
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT SEND POV INFO /////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotSendPovInfo(quint8 pov, float povValue)
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickTcpMessageType::Pov << pov << povValue;
	
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}






// SLOT CONNECTED /////////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotConnected()
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickTcpMessageType::Init;
	out << this->description();
	out << this->buttonsCount() << this->buttonsNames();
	out << this->axesCount()    << this->axesNames();
	out << this->povsCount()    << this->povsNames();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
	
	this->setState(State::Connected);
}

// SLOT DISCONNECTED //////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotDisconnected()
{
	m_tcpSocket->abort();
	this->setState(State::NotConnected);
}

// SLOT RECEIVE DATA //////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotReceiveData()
{
	QDataStream in{m_tcpSocket};
	in.setVersion(QDataStream::Qt_5_7);
	in.startTransaction();
	
	QString prop;
	QVariant data;
	in >> prop >> data;
	if (!in.commitTransaction()) {return;}
	
	this->setData(prop,data);
}

// SLOT ERROR /////////////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QAbstractSocket::RemoteHostClosedError)
		return;
	else if (socketError == QAbstractSocket::HostNotFoundError)
		emit error("The host was not found. Please check the host name and port settings");
	else if (socketError == QAbstractSocket::ConnectionRefusedError)
		emit error("The connection was refused by the peer. Make sure the server/profile is running, and check that the host name and port settings are correct");
	else
		emit error("The following error occurred: " + m_tcpSocket->errorString());
	
	this->setState(State::Error);
}

