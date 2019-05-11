#include "RemoteJoystickServer.h"
#include "RemoteJoystickMessageTypes.h"
#include "ExceptionFailedToConnect.h"
#include "ExceptionInconsistentInitData.h"
#include "Lim.h"
#include <QtNetwork>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  IS CONNECTED
//
//  ID
//  DESCRIPTION
//  HARDWARE ID
//  READ GAME CONTROLLER
//  CHANGES
//
//  BUTTONS COUNT
//  BUTTON PRESSED
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXES COUNT
//  AXIS VALUE
//  AXIS NAME
//  AXES NAMES
//
//  POVS COUNT
//  POV VALUE
//  POV NAME
//  POVS NAMES
//
//  SET DATA
//  FLUSH
//
//  SLOT SESSION OPENED
//  SLOT NEW CONNECTION
//  SLOT RECEIVE DATA
//  SLOT REMOVE CONNECTION
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
RemoteJoystickServer::RemoteJoystickServer(const QString &name, int portNumber, uint id, int msecTimeOut) :
		QObject{}, AbstractRealJoystick{}
{
	m_name = name;
	m_portNumber = portNumber;
	m_id = id;
	m_msecTimeOut = msecTimeOut;
	m_bConnected = false;
	
	m_dataSize = 0;
	m_messageType = RemoteJoystickMessageType::Invalid;
	
	m_initialized = false;
	m_initFailed = false;
	m_nbButtons = 0;
	m_nbAxes = 0;
	m_nbPovs = 0;
	for (bool &b : m_buttons) {b = false;}
	for (float &f : m_axes) {f = 0.0f;}
	for (float &f : m_povs) {f = -1.0f;}
	
	m_tcpServer = nullptr;
	m_tcpSocket = nullptr;
	m_networkSession = nullptr;
	
	
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
		if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered) {config = manager.defaultConfiguration();}
		
		m_networkSession = new QNetworkSession{config,this};
		QObject::connect(m_networkSession, &QNetworkSession::opened, this, &RemoteJoystickServer::slotSessionOpened);
		m_networkSession->open();
	}
	else
	{
		this->slotSessionOpened();
	}
	
	QObject::connect(m_tcpServer, &QTcpServer::newConnection, this, &RemoteJoystickServer::slotNewConnection);
	/*if (!m_tcpServer->waitForNewConnection(m_msecTimeOut))
	{
		m_tcpServer->close();
		delete m_tcpServer;
		throw ExceptionFailedToConnect{"Failed to connect to the remote controller"};
	}*/
}

RemoteJoystickServer::~RemoteJoystickServer()
{
	m_tcpServer->close();
	delete m_tcpServer;
	//m_tcpServer->deleteLater();
}

// IS CONNECTED ///////////////////////////////////////////////////////////////
bool RemoteJoystickServer::isConnected() const
{
	return m_bConnected;
}






// ID /////////////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::id() const
{
	return m_id;
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::description() const
{
	return m_name;
}

// HARDWARE ID ////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::hardwareId() const
{
	return {};
}

// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void RemoteJoystickServer::readGameController()
{
	
}

// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> RemoteJoystickServer::changes()
{
	QVector<JoystickChange> changes = m_changes;
	m_changes.clear();
	return changes;
}






// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint RemoteJoystickServer::buttonsCount() const {return m_nbButtons;}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool RemoteJoystickServer::buttonPressed(uint button) const
{
	if (button >= m_nbButtons) {return false;}
	return m_buttons[button];
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::buttonName(uint button) const
{
	if (button >= m_nbButtons) {return QString();}
	return m_buttonsNames[button];
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList RemoteJoystickServer::buttonsNames() const {return m_buttonsNames;}






// AXES COUNT /////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::axesCount() const {return m_nbAxes;}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float RemoteJoystickServer::axisValue(uint axis) const
{
	if (axis >= m_nbAxes) {return 0.0f;}
	return m_axes[axis];
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::axisName(uint axis) const
{
	if (axis >= m_nbAxes) {return QString();}
	return m_axesNames[axis];
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList RemoteJoystickServer::axesNames() const {return m_axesNames;}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::povsCount() const {return m_nbPovs;}

// POV VALUE //////////////////////////////////////////////////////////////////
float RemoteJoystickServer::povValue(uint pov) const
{
	if (pov >= m_nbPovs) {return -1.0f;}
	return m_povs[pov];
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::povName(uint pov) const
{
	if (pov >= m_nbPovs) {return QString();}
	return m_povsNames[pov];
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList RemoteJoystickServer::povsNames() const {return m_povsNames;}






// SET DATA ///////////////////////////////////////////////////////////////////
void RemoteJoystickServer::setData(const QString &str, QVariant v)
{
	if (m_initFailed) {return;}
	if (!m_tcpSocket) {return;}
	
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	out << str << v;
	m_tcpSocket->write(ba);
}

// FLUSH //////////////////////////////////////////////////////////////////////
void RemoteJoystickServer::flush()
{
	// nothing
}






// SLOT SESSION OPENED ////////////////////////////////////////////////////////
void RemoteJoystickServer::slotSessionOpened()
{
	// Save the used configuration
	if (m_networkSession)
	{
		QNetworkConfiguration config = m_networkSession->configuration();
		QString id;
		if (config.type() == QNetworkConfiguration::UserChoice)
			id = m_networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
		else
			id = config.identifier();
		
		QSettings settings{QSettings::UserScope, QLatin1String{"QtProject"}};
		settings.beginGroup(QLatin1String{"QtNetwork"});
		settings.setValue(QLatin1String{"DefaultNetworkConfiguration"}, id);
		settings.endGroup();
	}
	
	m_tcpServer = new QTcpServer{};
	if (!m_tcpServer->listen(QHostAddress::Any,m_portNumber))
	{
		m_tcpServer->close();
		QString message = "Unable to start the server " + m_name + ": " + m_tcpServer->errorString();
		delete m_tcpServer;
		throw ExceptionFailedToConnect{message.toStdString()};
		return;
	}
	
	/*
	// use the first non-localhost IPv4 address
	QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (const QHostAddress &ha : ipAddressesList)
	{
		if (ha != QHostAddress::LocalHost && ha.toIPv4Address())
		{
			ipAddress = ha.toString();
			break;
		}
	}
	// if we did not find one, use IPv4 localhost
	if (ipAddress == "") {ipAddress = QHostAddress{QHostAddress::LocalHost}.toString();}
	QString message = "IP: " + ipAddress + ", port: " + QString::number(m_tcpServer->serverPort());
	*/
}

// SLOT NEW CONNECTION ////////////////////////////////////////////////////////
void RemoteJoystickServer::slotNewConnection()
{
	QTcpSocket *newConnection = m_tcpServer->nextPendingConnection();
	if (m_tcpSocket)
	{
		// new connection request ignored (already connected)
		newConnection->disconnectFromHost();
		return;
	}
	
	m_tcpSocket = newConnection;
	QObject::connect(m_tcpSocket, &QIODevice::readyRead, this, &RemoteJoystickServer::slotReceiveData);
	QObject::connect(m_tcpSocket, &QAbstractSocket::disconnected, this, &RemoteJoystickServer::slotRemoveConnection);
	m_bConnected = true;
	emit connected();
}

// SLOT RECEIVE DATA //////////////////////////////////////////////////////////
void RemoteJoystickServer::slotReceiveData()
{
	if (m_initFailed) {return;}
	
	QDataStream in{m_tcpSocket};
	in.setVersion(QDataStream::Qt_5_7);
	
	// search for the size of the message
	if (m_messageType == RemoteJoystickMessageType::Invalid && m_dataSize == 0)
	{
		if (m_tcpSocket->bytesAvailable() < sizeof(quint16)) {return;}
		in >> m_dataSize;
	}
	
	// search for message type
	//if (m_dataSize == 0) {qDebug() << "BUG 1";}
	if (m_tcpSocket->bytesAvailable() < m_dataSize) {return;}
	in >> m_messageType;
	
	// init message
	if (m_messageType == RemoteJoystickMessageType::Init)
	{
		QString name;
		quint8 nbButtons, nbAxes, nbPovs;
		QStringList buttonsNames, axesNames, povsNames;
		in >> name >> nbButtons >> buttonsNames >> nbAxes >> axesNames >> nbPovs >> povsNames;
		
		m_messageType = RemoteJoystickMessageType::Invalid;
		m_dataSize = 0;
		
		if (name != m_name)
		{
			QString str = "Names of client (" + name + ") and server (" + m_name + ") does not match. You may not have connected the expected remote joystick";
			emit message(str,QColor{255,127,0});
			m_initFailed = true;
			//throw ExceptionInconsistentInitData{str.toStdString()};
		}
		
		if (nbButtons != buttonsNames.size() || nbAxes != axesNames.size() || nbPovs != povsNames.size())
		{
			QString str = "Wrong init data received: inconsistency in buttons/axes number and names";
			emit message(str,QColor{255,127,0});
			m_initFailed = true;
			//throw ExceptionInconsistentInitData{str.toStdString()};
		}
		
		if (m_initFailed) {return;}
		m_nbButtons = nbButtons;
		m_buttonsNames = buttonsNames;
		m_nbAxes = nbAxes;
		m_axesNames = axesNames;
		m_nbPovs = nbPovs;
		m_povsNames = povsNames;
		m_initialized = true;
	}
	// button change
	else if (m_messageType == RemoteJoystickMessageType::Button)
	{
		quint8 numButton;
		bool bPressed;
		in >> numButton >> bPressed;
		
		if (numButton < m_nbButtons)
		{
			JoystickChange ch{this,ControlType::Button,numButton,bPressed,0.0f};
			m_changes << ch;
			m_buttons[numButton] = bPressed;
		}
		
		m_messageType = RemoteJoystickMessageType::Invalid;
		m_dataSize = 0;
	}
	// axis change
	else if (m_messageType == RemoteJoystickMessageType::Axis)
	{
		quint8 numAxis;
		float axisValue;
		in >> numAxis >> axisValue;
		
		if (numAxis < m_nbAxes)
		{
			JoystickChange ch{this,ControlType::Axis,numAxis,false,axisValue};
			m_changes << ch;
			m_axes[numAxis] = axisValue;
		}
		
		m_messageType = RemoteJoystickMessageType::Invalid;
		m_dataSize = 0;
	}
	// pov change
	else if (m_messageType == RemoteJoystickMessageType::Pov)
	{
		quint8 numPov;
		float povValue;
		in >> numPov >> povValue;
		
		if (numPov < m_nbPovs)
		{
			JoystickChange ch{this,ControlType::Pov,numPov,false,povValue};
			m_changes << ch;
			m_povs[numPov] = povValue;
		}
		
		m_messageType = RemoteJoystickMessageType::Invalid;
		m_dataSize = 0;
	}
	else
	{
		//qDebug() << "BUG 2";
		return;
	}
	
	this->slotReceiveData();
}

// SLOT REMOVE CONNECTION /////////////////////////////////////////////////////
void RemoteJoystickServer::slotRemoveConnection()
{
	if (!m_tcpSocket) {return;}
	
	m_tcpSocket->disconnectFromHost();
	m_tcpSocket->abort();
	m_tcpSocket->deleteLater();
	m_tcpSocket = nullptr;
	m_bConnected = false;
}

