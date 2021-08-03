#ifndef PROFILE_ENGINE
#define PROFILE_ENGINE


#include <QObject>
#include <QColor>
#include "VigemWrapper/VigemPidWhiteLister.h"
class QTimer;
class QPluginLoader;
class AbstractProfile;
class GameControllersEnumThread;


class ProfileEngine : public QObject
{
	Q_OBJECT
	
	public:
		ProfileEngine(bool bWhiteList, QObject *parent = nullptr);
		ProfileEngine(const ProfileEngine &other) = delete;
		ProfileEngine(ProfileEngine &&other) = delete;
		ProfileEngine& operator=(const ProfileEngine &other) = delete;
		ProfileEngine& operator=(ProfileEngine &&other) = delete;
		virtual ~ProfileEngine();
		
		void loadProfile(const QString &dllFilePath);
		void stopLoading();
		bool unloadProfile();
		bool isLoaded() const;
		
		void play(int dtms);
		bool isInitialized() const;
		void stop();
		bool isActive() const;
		void wait();
		
		
	private slots:
		void slotResumeLoadProfile();
		void slotOneLoop();
		void slotStartTimer();
		void slotRemoteJoystickDisconnected();
		
		
	signals:
		void message(const QString &message, QColor color);
		void loadDone(bool bLoadOk);
		void initDone(bool bInitOk);
		void stopped();
		
		
	private:
		QTimer *m_timer;
		QString m_dllFileName;
		AbstractProfile *m_profile;
		QPluginLoader *m_loader;
		GameControllersEnumThread *m_thread;
		
		VigemPidWhiteLister m_vigemInterface;
};


#endif

