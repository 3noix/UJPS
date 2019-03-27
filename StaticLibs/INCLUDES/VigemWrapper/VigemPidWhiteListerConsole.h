#ifndef VIGEM_PID_WHITE_LISTER_CONSOLE
#define VIGEM_PID_WHITE_LISTER_CONSOLE


#include <QString>
#include <QCoreApplication>
#include <QNetworkAccessManager>


class VigemPidWhiteListerConsole
{
	public:
		VigemPidWhiteListerConsole(const QString &devconDirPath = QCoreApplication::applicationDirPath() + "/../../HidingJoysticks/ViGEm/Resources/");
		VigemPidWhiteListerConsole(const VigemPidWhiteListerConsole &s) = default;
		VigemPidWhiteListerConsole(VigemPidWhiteListerConsole &&s) = default;
		VigemPidWhiteListerConsole& operator=(const VigemPidWhiteListerConsole& s) = delete;
		VigemPidWhiteListerConsole& operator=(VigemPidWhiteListerConsole &&s) = delete;
		~VigemPidWhiteListerConsole() = default;
		
		// white or black listing pid
		bool whiteList(qint16 pid);
		bool blackList(qint16 pid);
		
		// check ViGEm status
		bool vigemIsReady() const;
		
		
	private:
		bool sendRequest(const QUrl &url);
		
		bool isHidGuardianInstalled() const;
		bool isHidCerberusInstalled() const;
		bool isHidCerberusRunning() const;
		
		QString m_devconExePath;
		QString m_urlToWhiteList;
		QString m_urlToBlackList;
		QNetworkAccessManager m_qnam;
};


#endif

