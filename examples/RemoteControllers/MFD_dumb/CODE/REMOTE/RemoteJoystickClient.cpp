#include "RemoteJoystickClient.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
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
//  SLOT MESSAGE RECEIVED
//  SLOT DISCONNECTED
//  SLOT ERROR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
RemoteJoystickClient::RemoteJoystickClient(QObject *parent) : QObject{parent}
{
	m_state = State::NotConnected;
	
	// connections
	QObject::connect(&m_webSocket, SIGNAL(connected()),                         this, SLOT(slotConnected()));
	QObject::connect(&m_webSocket, SIGNAL(disconnected()),                      this, SLOT(slotDisconnected()));
	QObject::connect(&m_webSocket, SIGNAL(textMessageReceived(QString)),        this, SLOT(slotMessageReceived(QString)));
	QObject::connect(&m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

// SET STATE //////////////////////////////////////////////////////////////////
void RemoteJoystickClient::setState(RemoteJoystickClient::State s)
{
	m_state = s;
	emit stateChanged(m_state);
}

// STATE //////////////////////////////////////////////////////////////////////
RemoteJoystickClient::State RemoteJoystickClient::state() const
{
	return m_state;
}






// SLOT CONNECT ///////////////////////////////////////////////////////////////
void RemoteJoystickClient::slotConnect(const QString &hostName, quint16 wsPort)
{
	QString url = "ws://" + hostName + ":" + QString::number(wsPort);
	m_webSocket.abort();
	m_webSocket.open(QUrl{url});
	this->setState(State::Connecting);
}

// SLOT DISCONNECT ////////////////////////////////////////////////////////////
void RemoteJoystickClient::slotDisconnect()
{
	m_webSocket.close();
}

// SLOT SEND BUTTON INFO //////////////////////////////////////////////////////
void RemoteJoystickClient::slotSendButtonInfo(uint button, bool bPressed)
{
	QString msg = "button/" + QString::number(button) + "/" + (bPressed ? "true" : "false");
	m_webSocket.sendTextMessage(msg);
}

// SLOT SEND AXIS INFO ////////////////////////////////////////////////////////
void RemoteJoystickClient::slotSendAxisInfo(uint axis, float axisValue)
{
	QString msg = "axis/" + QString::number(axis) + "/" + QString::number(axisValue);
	m_webSocket.sendTextMessage(msg);
}

// SLOT SEND POV INFO /////////////////////////////////////////////////////////
void RemoteJoystickClient::slotSendPovInfo(uint pov, float povValue)
{
	QString msg = "pov/" + QString::number(pov) + "/" + QString::number(povValue);
	m_webSocket.sendTextMessage(msg);
}






// SLOT CONNECTED /////////////////////////////////////////////////////////////
void RemoteJoystickClient::slotConnected()
{
	this->setState(State::Connected);
}

// SLOT DISCONNECTED //////////////////////////////////////////////////////////
void RemoteJoystickClient::slotDisconnected()
{
	m_webSocket.abort();
	this->setState(State::NotConnected);
}

// SLOT MESSAGE RECEIVED //////////////////////////////////////////////////////
void RemoteJoystickClient::slotMessageReceived(const QString &msg)
{
	emit signalSetData(msg);
}

// SLOT ERROR /////////////////////////////////////////////////////////////////
void RemoteJoystickClient::slotError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QAbstractSocket::RemoteHostClosedError)
		return;
	else if (socketError == QAbstractSocket::HostNotFoundError)
		emit error("The host was not found. Please check the host name and port settings");
	else if (socketError == QAbstractSocket::ConnectionRefusedError)
		emit error("The connection was refused by the peer. Make sure the server/profile is running, and check that the host name and port settings are correct");
	else
		emit error("The following error occurred: " + m_webSocket.errorString());
	
	this->setState(State::Error);
}

