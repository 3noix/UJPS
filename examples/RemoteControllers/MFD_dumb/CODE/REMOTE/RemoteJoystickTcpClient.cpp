#include "RemoteJoystickTcpClient.h"
#include "RemoteJoystickTcpMessageTypes.h"

#include <QtWidgets>
#include <QtNetwork>


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
//  SLOT SESSION OPENED
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
	m_networkSession = nullptr;
	
	// connections
	connect(m_tcpSocket, &QTcpSocket::connected, this, &RemoteJoystickTcpClient::slotConnected);
	connect(m_tcpSocket, &QTcpSocket::disconnected, this, &RemoteJoystickTcpClient::slotDisconnected);
	connect(m_tcpSocket, &QIODevice::readyRead, this, &RemoteJoystickTcpClient::slotReceiveData);
	typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
	connect(m_tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &RemoteJoystickTcpClient::slotError);
	
	// configuration du client
	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
	{
		// Get saved network configuration
		QSettings settings{QSettings::UserScope, QLatin1String{"QtProject"}};
		settings.beginGroup(QLatin1String{"QtNetwork"});
		const QString id = settings.value(QLatin1String{"DefaultNetworkConfiguration"}).toString();
		settings.endGroup();
		
		// If the saved network configuration is not currently discovered use the system default
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
			config = manager.defaultConfiguration();
		
		m_networkSession = new QNetworkSession{config,this};
		connect(m_networkSession, &QNetworkSession::opened, this, &RemoteJoystickTcpClient::slotSessionOpened);
		m_networkSession->open();
	}
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






// SLOT SESSION OPENED ////////////////////////////////////////////////////////
void RemoteJoystickTcpClient::slotSessionOpened()
{
	// Save the used configuration
	QNetworkConfiguration config = m_networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
		id = m_networkSession->sessionProperty(QLatin1String{"UserChoiceConfiguration"}).toString();
	else
		id = config.identifier();
	
	QSettings settings{QSettings::UserScope, QLatin1String{"QtProject"}};
	settings.beginGroup(QLatin1String{"QtNetwork"});
	settings.setValue(QLatin1String{"DefaultNetworkConfiguration"}, id);
	settings.endGroup();
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

