#ifndef VIGEM_PID_WHITE_LISTER
#define VIGEM_PID_WHITE_LISTER


#include <QString>
#include <QCoreApplication>
#include <QNetworkAccessManager>


class VigemPidWhiteLister
{
	public:
		VigemPidWhiteLister(const QString &devconDirPath = QCoreApplication::applicationDirPath() + "/../../HidingJoysticks/ViGEm/Resources/");
		VigemPidWhiteLister(const VigemPidWhiteLister &s) = default;
		VigemPidWhiteLister(VigemPidWhiteLister &&s) = default;
		VigemPidWhiteLister& operator=(const VigemPidWhiteLister& s) = delete;
		VigemPidWhiteLister& operator=(VigemPidWhiteLister &&s) = delete;
		~VigemPidWhiteLister() = default;
		
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

