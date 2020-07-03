#ifndef VIGEM_PID_WHITE_LISTER_CONSOLE
#define VIGEM_PID_WHITE_LISTER_CONSOLE


#include <QString>
#include <QCoreApplication>
#include <QNetworkAccessManager>


class VigemPidWhiteListerConsole
{
	public:
		VigemPidWhiteListerConsole(const QString &devconDirPath = QCoreApplication::applicationDirPath() + "/../3rdparty/ViGEm/Resources/");
		VigemPidWhiteListerConsole(const VigemPidWhiteListerConsole &s) = default;
		VigemPidWhiteListerConsole(VigemPidWhiteListerConsole &&s) = default;
		VigemPidWhiteListerConsole& operator=(const VigemPidWhiteListerConsole& s) = delete;
		VigemPidWhiteListerConsole& operator=(VigemPidWhiteListerConsole &&s) = delete;
		~VigemPidWhiteListerConsole() = default;
		
		// ViGEm commands
		bool whiteList(qint16 pid);
		bool blackList(qint16 pid);
		QStringList affectedDevices();
		
		// check ViGEm status
		bool vigemIsReady() const;
		
		
	private:
		QString sendRequest(const QUrl &url);
		
		bool isHidGuardianInstalled() const;
		bool isHidCerberusInstalled() const;
		bool isHidCerberusRunning() const;
		
		QString m_devconExePath;
		QString m_urlToWhiteList;
		QString m_urlToBlackList;
		QNetworkAccessManager m_qnam;
};


#endif

