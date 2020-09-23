#include "RemoteJoystickServer.h"
#include "ExceptionFailedToConnect.h"
#include <QNetworkInterface>
#include <QHttpServer>
#include <QWebSocketServer>
#include <QWebSocket>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  IS CONNECTED
//  ETHERNET LOCAL IP ADDRESS
//  URL
//
//  LISTEN
//  CLOSE
//
//  SET DATA
//  DATA 2 STRING
//  FLUSH
//  SLOT NEW WS CONNECTION
//  SLOT PROCESS MESSAGE
//  SLOT WS SOCKET DISCONNECTED
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
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
RemoteJoystickServer::RemoteJoystickServer(const QString &name, quint16 httpPort, quint16 wsPort, uint id, const QString &resourcesPath) :
		QObject{}, AbstractRealJoystick{}
{
	m_name = name;
	m_httpPort = httpPort;
	m_wsPort = wsPort;
	m_id = id;
	m_resourcesPath = resourcesPath;
	
	for (bool &b : m_buttons) {b = false;}
	for (float &f : m_axes) {f = 0.0f;}
	for (float &f : m_povs) {f = -1.0f;}
	
	m_bDestructionInProgress = false;
	m_httpServer = nullptr;
	m_wsServer = nullptr;
	
	QString errorMessage;
	if (!this->listen(&errorMessage))
	{
		this->close();
		throw ExceptionFailedToConnect{errorMessage.toStdString()};
	}
}

RemoteJoystickServer::~RemoteJoystickServer()
{
	m_bDestructionInProgress = true;
	this->close();
}

// IS CONNECTED ///////////////////////////////////////////////////////////////
bool RemoteJoystickServer::isConnected() const
{
	return m_wsClients.size() > 0;
}

// ETHERNET LOCAL IP ADDRESS //////////////////////////////////////////////////
QString RemoteJoystickServer::ethernetLocalIpAddress(bool ipv6)
{
	// search for the first active ethernet network interface
	QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
	auto isActiveEthernet = [] (const QNetworkInterface &ni) {return ni.type() == QNetworkInterface::Ethernet && (ni.flags() & QNetworkInterface::IsUp);};
	auto result1 = std::find_if(interfaces.begin(),interfaces.end(),isActiveEthernet);
	if (result1 == interfaces.end()) {return QString{};}
	
	// search for the first ip address with the right protocol
	QList<QNetworkAddressEntry> addressesEntries = result1->addressEntries();
	QAbstractSocket::NetworkLayerProtocol protocolToSearch = (ipv6 ? QAbstractSocket::IPv6Protocol : QAbstractSocket::IPv4Protocol);
	auto isIpVX = [protocolToSearch] (const QNetworkAddressEntry &nae) {return nae.ip().protocol() == protocolToSearch;};
	auto result2 = std::find_if(addressesEntries.begin(),addressesEntries.end(),isIpVX);
	if (result2 == addressesEntries.end()) {return QString{};}
	return result2->ip().toString();
}

// URL ////////////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::url() const
{
	return "http://" + ethernetLocalIpAddress() + ":" + QString::number(m_httpPort);
}






// LISTEN /////////////////////////////////////////////////////////////////////
bool RemoteJoystickServer::listen(QString *errorMessage)
{
	if (!m_httpServer) {m_httpServer = new QHttpServer{};}
	//if (!m_httpServer && !m_resourcesPath.isEmpty()) {m_httpServer = new QHttpServer{};}
	if (!m_wsServer)
	{
		m_wsServer = new QWebSocketServer{m_name,QWebSocketServer::NonSecureMode};
		QObject::connect(m_wsServer, SIGNAL(newConnection()), this, SLOT(slotNewWsConnection()));
	}
	
	// http routing for files (typically html, css, js, images, ...)
	//if (m_httpServer)
	//{
		m_httpServer->route("/", [this] () {
			return QHttpServerResponse::fromFile(m_resourcesPath + "/index.html");
		});
		m_httpServer->route("/<arg>", [this] (const QString &fileName) {
			return QHttpServerResponse::fromFile(m_resourcesPath + "/" + fileName);
		});
	//}
	
	// start the servers
	if (!m_httpServer->listen(QHostAddress::Any,m_httpPort))
	{
		if (errorMessage) {*errorMessage = "HTTP server failed to listen";}
		return false;
	}
	if (!m_wsServer->listen(QHostAddress::Any,m_wsPort))
	{
		if (errorMessage) {*errorMessage = "WS server failed to listen: " + m_wsServer->errorString();}
		return false;
	}
	
	if (errorMessage) {*errorMessage = "";}
	return true;
}

// CLOSE //////////////////////////////////////////////////////////////////////
void RemoteJoystickServer::close()
{
	if (m_httpServer)
	{
		// the destruction of the QHttpServer close the connections...
		// QHttpServer does not provide a "close" function!
		//delete m_httpServer;
		m_httpServer->deleteLater();
		m_httpServer = nullptr;
	}
	
	if (m_wsServer)
	{
		m_wsServer->close();
		m_wsServer->deleteLater();
		m_wsServer = nullptr;
	}
}

// SET DATA ///////////////////////////////////////////////////////////////////
void RemoteJoystickServer::setData(const QString &str, QVariant v)
{
	QString vStr = data2string(v);
	if (vStr == "") {return;}
	
	QString msg = str + "=" + vStr;
	for (QWebSocket *socket : m_wsClients)
		socket->sendTextMessage(msg);
}

// DATA 2 STRING //////////////////////////////////////////////////////////////
QString RemoteJoystickServer::data2string(QVariant v)
{
	QVariant::Type type = v.type();
	
	if (type == QMetaType::Bool) {return v.toBool() ? "true" : "false";}
	else if (type == QMetaType::Int) {return QString::number(v.toInt());}
	else if (type == QMetaType::Float) {return QString::number(v.toFloat());}
	else if (type == QMetaType::Double) {return QString::number(v.toDouble());}
	else if (type == QMetaType::QString) {return v.toString();}
	
	return {};
}

// FLUSH //////////////////////////////////////////////////////////////////////
void RemoteJoystickServer::flush()
{
	// nothing
}






// SLOT NEW WS CONNECTION /////////////////////////////////////////////////////
void RemoteJoystickServer::slotNewWsConnection()
{
	QWebSocket *socket = m_wsServer->nextPendingConnection();
	
	QObject::connect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(slotProcessMessage(QString)));
	QObject::connect(socket, SIGNAL(disconnected()),               this, SLOT(slotWsSocketDisconnected()));
	
	m_wsClients.push_back(socket);
	if (m_wsClients.size() == 1) {emit connected();}
}

// SLOT PROCESS MESSAGE ///////////////////////////////////////////////////////
void RemoteJoystickServer::slotProcessMessage(const QString &msg)
{
	QStringList list = msg.split('/', Qt::KeepEmptyParts);
	if (list.size() != 3) {return;}
	
	const QString &inputType = list[0];
	const QString &value = list[2];
	bool numOk = true;
	uint num = list[1].toUInt(&numOk);
	if (!numOk) {return;}
	
	if (inputType == "button")
	{
		if (num >= 128) {return;}
		if (value != "true" && value != "false") {return;}
		
		bool bPressed = (value == "true");
		JoystickChange ch{this,ControlType::Button,num,bPressed,0.0f};
		m_changes << ch;
		m_buttons[num] = bPressed;
	}
	else if (inputType == "axis")
	{
		if (num >= 8) {return;}
		bool valueOk = true;
		float axisValue = value.toFloat(&valueOk);
		if (!valueOk) {return;}
		if (axisValue < -1.0f || axisValue > 1.0f) {return;}
		
		JoystickChange ch{this,ControlType::Axis,num,false,axisValue};
		m_changes << ch;
		m_axes[num] = axisValue;
	}
	else if (inputType == "pov")
	{
		if (num >= 4) {return;}
		bool valueOk = true;
		float povValue = value.toFloat(&valueOk);
		if (!valueOk) {return;}
		if (povValue >= 360.0f || (povValue < 0.0f && povValue != -1.0f)) {return;}
		
		JoystickChange ch{this,ControlType::Pov,num,false,povValue};
		m_changes << ch;
		m_povs[num] = povValue;
	}
}

// SLOT WS SOCKET DISCONNECTED ////////////////////////////////////////////////
void RemoteJoystickServer::slotWsSocketDisconnected()
{
	if (QWebSocket *socket = qobject_cast<QWebSocket*>(sender()))
	{
		m_wsClients.remove(socket);
		socket->abort();
		socket->deleteLater();
	}
	
	if (m_wsClients.size() == 0 && !m_bDestructionInProgress) {emit disconnected();}
}






// ID /////////////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::id() const {return m_id;}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::description() const {return m_name;}

// HARDWARE ID ////////////////////////////////////////////////////////////////
QString RemoteJoystickServer::hardwareId() const {return {};}

// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void RemoteJoystickServer::readGameController() {}

// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> RemoteJoystickServer::changes()
{
	QVector<JoystickChange> changes = m_changes;
	m_changes.clear();
	return changes;
}






// BUTTONS ////////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::buttonsCount() const {return 128;}

bool RemoteJoystickServer::buttonPressed(uint button) const
{
	if (button >= 128) {return false;}
	return m_buttons[button];
}

QString RemoteJoystickServer::buttonName(uint button) const
{
	Q_UNUSED(button)
	return {};
}

QStringList RemoteJoystickServer::buttonsNames() const {return {};}






// AXES ///////////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::axesCount() const {return 8;}

float RemoteJoystickServer::axisValue(uint axis) const
{
	if (axis >= 8) {return 0.0f;}
	return m_axes[axis];
}

QString RemoteJoystickServer::axisName(uint axis) const
{
	Q_UNUSED(axis)
	return {};
}

QStringList RemoteJoystickServer::axesNames() const {return {};}






// POVS ///////////////////////////////////////////////////////////////////////
uint RemoteJoystickServer::povsCount() const {return 4;}

float RemoteJoystickServer::povValue(uint pov) const
{
	if (pov >= 4) {return -1.0f;}
	return m_povs[pov];
}

QString RemoteJoystickServer::povName(uint pov) const
{
	Q_UNUSED(pov)
	return {};
}

QStringList RemoteJoystickServer::povsNames() const {return {};}

