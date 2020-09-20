#include "VigemPidWhiteLister.h"

#include <QProcess>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QMessageBox>
#include <QCoreApplication>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  WHITE LIST
//  BLACK LIST
//  AFFECTED DEVICES
//  SEND REQUEST
//
//  VIGEM IS READY
//  IS HID GUARDIAN INSTALLED
//  IS HID CERBERUS INSTALLED
//  IS HID CERBERUS RUNNING
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
VigemPidWhiteLister::VigemPidWhiteLister(const QString &devconDirPath)
{
	m_devconExePath = devconDirPath + "/devcon.exe";
	m_urlToWhiteList = "http://localhost:26762/api/v1/hidguardian/whitelist/add/";
	m_urlToBlackList = "http://localhost:26762/api/v1/hidguardian/whitelist/remove/";
}

// WHITE LIST /////////////////////////////////////////////////////////////////
bool VigemPidWhiteLister::whiteList(qint16 pid)
{
	QString urlStr = m_urlToWhiteList + QString::number(pid);
	return (this->sendRequest(urlStr) == "[\"OK\"]");
}

// BLACK LIST /////////////////////////////////////////////////////////////////
bool VigemPidWhiteLister::blackList(qint16 pid)
{
	QString urlStr = m_urlToBlackList + QString::number(pid);
	return (this->sendRequest(urlStr) == "[\"OK\"]");
}

// AFFECTED DEVICES ///////////////////////////////////////////////////////////
QStringList VigemPidWhiteLister::affectedDevices()
{
	QString urlStr = "http://localhost:26762/api/v1/hidguardian/affected/get";
	QString data = this->sendRequest(urlStr);
	data.remove('[');
	data.remove(']');
	data.remove('\"');
	data.replace("\\\\","\\");
	return data.split(',',Qt::SkipEmptyParts);
}

// SEND REQUEST ///////////////////////////////////////////////////////////////
QString VigemPidWhiteLister::sendRequest(const QUrl &url)
{
	QEventLoop localEventsLoop;
	QNetworkReply *reply = m_qnam.get(QNetworkRequest{url});
	QObject::connect(reply, &QNetworkReply::finished, &localEventsLoop, &QEventLoop::quit);
	localEventsLoop.exec();
	
	// we ignore an error (it occurs when we try to remove a pid that is not in the list)
	QString errorMessageToIgnore = "Error transferring http://localhost:26762/api/v1/hidguardian/whitelist/remove/";
	errorMessageToIgnore += QString::number(QCoreApplication::applicationPid()) + " - server replied: Internal Server Error";
	if (reply->error() != QNetworkReply::NoError && reply->errorString() != errorMessageToIgnore)
	{
		QMessageBox::critical(nullptr, "ViGEm error", reply->errorString(), QMessageBox::Ok);
		reply->deleteLater();
		return {};
	}
	
	// Get the http status code
	int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (v >= 200 && v < 300) // success
	{
		QString replyText = reply->readAll();
		reply->deleteLater();
		return replyText;
	}
	else if (v >= 300 && v < 400) // redirection
	{
		QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
		newUrl = reply->url().resolved(newUrl); // because the redirection url can be relative, we have to use the previous one to resolve it
		reply->deleteLater();
		return this->sendRequest(newUrl);
	}
	
	reply->deleteLater();
	return {};
}






// VIGEM IS READY /////////////////////////////////////////////////////////////
bool VigemPidWhiteLister::vigemIsReady() const
{
	bool b1 = this->isHidGuardianInstalled();
	bool b2 = this->isHidCerberusInstalled();
	bool b3 = this->isHidCerberusRunning();
	return (b1 && b2 && b3);
}

// IS HID GUARDIAN INSTALLED //////////////////////////////////////////////////
bool VigemPidWhiteLister::isHidGuardianInstalled() const
{
	QProcess process;
	process.start(m_devconExePath,{"Status","Root\\HidGuardian"});
	process.waitForFinished();
	
	QString data = process.readAllStandardOutput();
	data.replace("\r","");
	QStringList lines = data.split('\n',Qt::SkipEmptyParts);
	
	if (lines.size() == 0) {return false;}
	return lines.last().contains(" matching device(s) found");
}

// IS HID CERBERUS INSTALLED //////////////////////////////////////////////////
bool VigemPidWhiteLister::isHidCerberusInstalled() const
{
	QProcess process;
	process.start("cmd.exe",{"/c","sc","query","Hidcerberus.Srv"});
	process.waitForFinished();
	
	QString data = process.readAllStandardOutput();
	data.replace("\r","");
	QStringList lines = data.split('\n',Qt::SkipEmptyParts);
	
	if (lines.size() < 3) {return false;}
	return lines[2].contains("STATE");
}

// IS HID CERBERUS RUNNING ////////////////////////////////////////////////////
bool VigemPidWhiteLister::isHidCerberusRunning() const
{
	QProcess process;
	process.start("cmd.exe",{"/c","sc","query","Hidcerberus.Srv"});
	process.waitForFinished();
	
	QString data = process.readAllStandardOutput();
	data.replace("\r","");
	QStringList lines = data.split('\n',Qt::SkipEmptyParts);
	
	if (lines.size() < 3) {return false;}
	return (lines[2].contains("STATE") && lines[2].contains("RUNNING"));
}

