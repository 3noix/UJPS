#include "UjpsHttpServer.h"
#include "RemoteJoystickHttp.h"
#include <QHttpServer>
#include <QNetworkInterface>
#include <QFile>

using StatusCode = QHttpServerResponder::StatusCode;
UjpsHttpServer UjpsHttpServer::m_instance;


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  INSTANCE
//  ETHERNET LOCAL IP ADDRESS
//
//  LISTEN
//  REGISTER REMOTE GUI HTTP
//  CLOSE
//
//  PROCESS FILE
//  PROCESS BUTTON
//  PROCESS AXIS
//  PROCESS POV
//  URL
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
UjpsHttpServer::UjpsHttpServer()
{
	m_httpServer = nullptr;
}

UjpsHttpServer::~UjpsHttpServer()
{
	this->close();
}

// INSTANCE ///////////////////////////////////////////////////////////////////
UjpsHttpServer& UjpsHttpServer::instance()
{
	return m_instance;
}

// ETHERNET LOCAL IP ADDRESS //////////////////////////////////////////////////
QString UjpsHttpServer::ethernetLocalIpAddress(bool ipv6)
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






// LISTEN /////////////////////////////////////////////////////////////////////
bool UjpsHttpServer::listen()
{
	if (!m_httpServer) {return false;}
	
	// routing for files (typically html, css and js)
	m_httpServer->route("/file/<arg>/<arg>", [this] (const QString &name, const QString &fileName) {
		return this->processFile(name,fileName);
	});
	
	// routing for inputs
	m_httpServer->route("/button/<arg>/<arg>/<arg>", [this] (const QString &name, uint button, uint bPressed) {
		return this->processButton(name,button,bPressed!=0);
	});
	m_httpServer->route("/axis/<arg>/<arg>/<arg>", [this] (const QString &name, uint axis, float value) {
		return this->processAxis(name,axis,value);
	});
	m_httpServer->route("/pov/<arg>/<arg>/<arg>", [this] (const QString &name, uint pov, float value) {
		return this->processPov(name,pov,value);
	});
	
	return m_httpServer->listen(QHostAddress::Any,8080);
}

// REGISTER REMOTE GUI HTTP ///////////////////////////////////////////////////
RemoteJoystickHttp* UjpsHttpServer::registerRemoteGuiHttp(const QString &name, uint id, const QString &dirPath)
{
	if (name.contains('/')) {return nullptr;}
	if (m_httpRemotes.contains(name)) {return nullptr;}
	if (!m_httpServer) {m_httpServer = new QHttpServer{};}
	
	RemoteJoystickHttp *rjh = new RemoteJoystickHttp{name,id};
	m_httpRemotes.insert(name,RemoteData{dirPath,rjh});
	return rjh;
}

// CLOSE //////////////////////////////////////////////////////////////////////
void UjpsHttpServer::close()
{
	if (m_httpServer)
	{
		// the destruction of the QHttpServer close the connections...
		// QHttpServer does not provide a "close" function!
		delete m_httpServer;
		m_httpServer = nullptr;
		
		for (RemoteData &rd : m_httpRemotes) {delete rd.remote;}
		m_httpRemotes.clear();
	}
}






// PROCESS FILE ///////////////////////////////////////////////////////////////
QHttpServerResponse UjpsHttpServer::processFile(const QString &name, const QString &fileName)
{
	if (!m_httpRemotes.contains(name)) {return QHttpServerResponse(StatusCode::BadRequest);}
	const RemoteData &rd = m_httpRemotes[name];
	
	if (fileName == "gui.html")
	{
		QFile file{rd.dirPath + "/gui.html"};
		if (!file.open(QIODevice::ReadOnly)) {return QHttpServerResponse{StatusCode::NotFound};}
		QString html = file.readAll();
		html.replace("@name@",name);
		return QHttpServerResponse("text/html",html.toUtf8(),StatusCode::Ok);
	}
	else
	{
		return QHttpServerResponse::fromFile(rd.dirPath + "/" + fileName);
	}
}

// PROCESS BUTTON /////////////////////////////////////////////////////////////
QHttpServerResponse UjpsHttpServer::processButton(const QString &name, uint button, bool bPressed)
{
	if (!m_httpRemotes.contains(name)) {return QHttpServerResponse(StatusCode::BadRequest);}
	const RemoteData &rd = m_httpRemotes[name];
	if (button >= rd.remote->buttonsCount()) {return QHttpServerResponse(StatusCode::Forbidden);}
	
	rd.remote->addChange(JoystickChange{rd.remote,ControlType::Button,button,bPressed,0.0f});
	return QHttpServerResponse(StatusCode::NoContent);
}

// PROCESS AXIS ///////////////////////////////////////////////////////////////
QHttpServerResponse UjpsHttpServer::processAxis(const QString &name, uint axis, float value)
{
	if (!m_httpRemotes.contains(name)) {return QHttpServerResponse(StatusCode::BadRequest);}
	const RemoteData &rd = m_httpRemotes[name];
	if (axis >= rd.remote->axesCount()) {return QHttpServerResponse(StatusCode::Forbidden);}
	
	rd.remote->addChange(JoystickChange{rd.remote,ControlType::Axis,axis,false,value});
	return QHttpServerResponse(StatusCode::NoContent);
}

// PROCESS POV ////////////////////////////////////////////////////////////////
QHttpServerResponse UjpsHttpServer::processPov(const QString &name, uint pov, float value)
{
	if (!m_httpRemotes.contains(name)) {return QHttpServerResponse(StatusCode::BadRequest);}
	const RemoteData &rd = m_httpRemotes[name];
	if (pov >= rd.remote->povsCount()) {return QHttpServerResponse(StatusCode::Forbidden);}
	
	rd.remote->addChange(JoystickChange{rd.remote,ControlType::Pov,pov,false,value});
	return QHttpServerResponse(StatusCode::NoContent);
}

// URL ////////////////////////////////////////////////////////////////////////
QString UjpsHttpServer::url(const QString &name) const
{
	if (!m_httpRemotes.contains(name)) {return {};}
	QString pcIpAddress = UjpsHttpServer::ethernetLocalIpAddress();
	QString out = "http://" + pcIpAddress + ":8080/file/" + name + "/gui.html";
	return out;
}

