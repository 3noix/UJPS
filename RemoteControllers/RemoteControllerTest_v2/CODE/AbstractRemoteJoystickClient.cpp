#include "AbstractRemoteJoystickClient.h"
#include "RemoteJoystickMessageTypes.h"

#include <QtWidgets>
#include <QtNetwork>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  SET STATE
//  STATE
//
//  SLOT CONNECT
//  SLOT DISCONNECT
//  SLOT SEND BUTTON INFO
//  SLOT SEND AXIS INFO
//
//  SLOT SESSION OPENED
//  SLOT CONNECTED
//  SLOT RECEIVE DATA
//  SLOT DISCONNECTED
//  SLOT ERROR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
AbstractRemoteJoystickClient::AbstractRemoteJoystickClient(QObject *parent) : QObject{parent}
{
	m_hostName = "";
	m_port = 0;
	m_state = State::NotConnected;
	m_tcpSocket = new QTcpSocket{this};
	m_networkSession = nullptr;
	
	// connections
	connect(m_tcpSocket, &QTcpSocket::connected, this, &AbstractRemoteJoystickClient::slotConnected);
	connect(m_tcpSocket, &QTcpSocket::disconnected, this, &AbstractRemoteJoystickClient::slotDisconnected);
	connect(m_tcpSocket, &QIODevice::readyRead, this, &AbstractRemoteJoystickClient::slotReceiveData);
	typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
	connect(m_tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &AbstractRemoteJoystickClient::slotError);
	
	// configuration du client
	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
	{
		// Get saved network configuration
		QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();
		
		// If the saved network configuration is not currently discovered use the system default
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
			config = manager.defaultConfiguration();
		
		m_networkSession = new QNetworkSession(config, this);
		connect(m_networkSession, &QNetworkSession::opened, this, &AbstractRemoteJoystickClient::slotSessionOpened);
		m_networkSession->open();
	}
}

// SET STATE //////////////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::setState(AbstractRemoteJoystickClient::State s)
{
	m_state = s;
	emit stateChanged(m_state);
}

// STATE //////////////////////////////////////////////////////////////////////
AbstractRemoteJoystickClient::State AbstractRemoteJoystickClient::state() const
{
	return m_state;
}






// SLOT CONNECT ///////////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotConnect(const QString &hostName, quint16 port)
{
	m_hostName = hostName;
	m_port = port;
	
	m_tcpSocket->abort();
	m_tcpSocket->connectToHost(m_hostName,m_port);
	this->setState(State::Connecting);
}

// SLOT DISCONNECT ////////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotDisconnect()
{
	m_tcpSocket->disconnectFromHost();
}

// SLOT SEND BUTTON INFO //////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotSendButtonInfo(quint8 button, bool bPressed)
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickMessageType::Button << button << bPressed;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT SEND AXIS INFO ////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotSendAxisInfo(quint8 axis, float axisValue)
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickMessageType::Axis << axis << axisValue;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}








// SLOT SESSION OPENED ////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotSessionOpened()
{
	// Save the used configuration
	QNetworkConfiguration config = m_networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
		id = m_networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	else
		id = config.identifier();
	
	QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();
}

// SLOT CONNECTED /////////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotConnected()
{
	this->setState(State::Connected);
	
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	m_tcpSocket->flush();
	out << quint16{0} << RemoteJoystickMessageType::Init;
	out << this->description();
	out << this->buttonCount() << this->buttonsNames();
	out << this->axisCount() << this->axesNames();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT DISCONNECTED //////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotDisconnected()
{
	this->setState(State::NotConnected);
	m_tcpSocket->abort();
}

// SLOT RECEIVE DATA //////////////////////////////////////////////////////////
void AbstractRemoteJoystickClient::slotReceiveData()
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
void AbstractRemoteJoystickClient::slotError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QAbstractSocket::RemoteHostClosedError)
		return;
	else if (socketError == QAbstractSocket::HostNotFoundError)
		emit error("The host was not found. Please check the host name and port settings");
	else if (socketError == QAbstractSocket::ConnectionRefusedError)
		emit error("The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct");
	else
		emit error("The following error occurred: " + m_tcpSocket->errorString());
	
	this->setState(State::Error);
}


