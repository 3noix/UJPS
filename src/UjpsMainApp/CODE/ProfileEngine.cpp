#include "ProfileEngine.h"
#include "otherFunctions.h"
#include <QCoreApplication>
#include <QTimer>
#include <QPluginLoader>
#include "AbstractProfile.h"
#include "RealJoysticksManager.h"
#include "GameControllersEnumThread.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  WAIT
//
//  LOAD PROFILE
//  SLOT RESUME LOAD PROFILE
//  STOP LOADING
//  UNLOAD PROFILE
//  IS LOADED
//
//  PLAY
//  IS INITIALIZED
//  SLOT START TIMER
//  STOP
//  IS ACTIVE
//
//  SLOT ONE LOOP
//  SLOT REMOTE JOYSTICK DISCONNECTED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
ProfileEngine::ProfileEngine(bool bWhiteList, QObject *parent) : QObject{parent}
{
	m_timer = new QTimer{this};
	m_thread = new GameControllersEnumThread{this};
	
	QObject::connect(m_timer, &QTimer::timeout, this, &ProfileEngine::slotOneLoop);
	QObject::connect(m_thread, SIGNAL(done()), this, SLOT(slotResumeLoadProfile()));
	
	m_dllFileName = "";
	m_profile = nullptr;
	m_loader = nullptr;
	
	if (bWhiteList && m_vigemInterface.vigemIsReady())
		m_vigemInterface.whiteList(QCoreApplication::applicationPid());
}

ProfileEngine::~ProfileEngine()
{
	m_thread->wait();
	m_timer->stop();
	this->unloadProfile();
	
	// remove this application from the white list
	// (to avoid to pollute the white list with many invalid pids)
	if (m_vigemInterface.vigemIsReady())
		m_vigemInterface.blackList(QCoreApplication::applicationPid());
}

// WAIT ///////////////////////////////////////////////////////////////////////
void ProfileEngine::wait()
{
	m_thread->wait();
}






// LOAD PROFILE ///////////////////////////////////////////////////////////////
void ProfileEngine::loadProfile(const QString &dllFilePath)
{
	if (m_thread->isRunning()) {return;}
	
	if (m_loader)
	{
		emit loadDone(false);
		return;
	}
	
	emit message("Loading profile " + m_dllFileName,Qt::black);
	m_loader = new QPluginLoader{dllFilePath};
	if (QObject *plugin = m_loader->instance())
	{
		if (AbstractProfile* profile = qobject_cast<AbstractProfile*>(plugin))
		{
			m_dllFileName = shortName(dllFilePath);
			m_profile = profile;
			QObject::connect(m_profile, SIGNAL(message(QString,QColor)),      this, SIGNAL(message(QString,QColor)));
			QObject::connect(m_profile, SIGNAL(asyncInitComplete()),          this, SLOT(slotStartTimer()));
			QObject::connect(m_profile, SIGNAL(remoteJoystickDisconnected()), this, SLOT(slotRemoteJoystickDisconnected()));
			
			emit message("Enumerating controllers",Qt::black);
			m_thread->enumerateControllersOneByOne();
			return;
		}
	}
	
	emit message("Profile loading failed",Qt::red);
	delete m_loader;
	m_loader = nullptr;
	emit loadDone(false);
}

// SLOT RESUME LOAD PROFILE ///////////////////////////////////////////////////
void ProfileEngine::slotResumeLoadProfile()
{
	if (!m_profile) {return;} // we get here if thread was stopped at the last step
	QVector<GameController*> gcv = m_thread->releaseGameControllers();
	
	RealJoysticksManager *rjm = new RealJoysticksManager{};
	QString controllersPluginsDirPath = QCoreApplication::applicationDirPath() + "/ControllersPlugins/";
	rjm->loadPlugins(controllersPluginsDirPath);
	rjm->fromGameControllers(gcv);
	m_profile->setRealJoysticksManager(rjm); // ownership is transfered to the profile
	
	emit loadDone(true);
}

// STOP LOADING ///////////////////////////////////////////////////////////////
void ProfileEngine::stopLoading()
{
	// maybe the thread just finished
	if (!m_thread->isRunning())
	{
		this->stop();
		return;
	}
	
	m_thread->stop();
	m_thread->wait();
	
	m_loader->unload(); // it deletes m_profile, but on Qt5.11 it does not unleash the dll
	delete m_loader;
	
	emit message("Profile loading stopped",Qt::black);
	m_dllFileName = "";
	m_loader = nullptr;
	m_profile = nullptr;
}

// UNLOAD PROFILE /////////////////////////////////////////////////////////////
bool ProfileEngine::unloadProfile()
{
	if (m_thread->isRunning()) {return false;}
	if (!m_loader) {return true;}
	
	this->stop();
	bool b = m_loader->unload(); // it deletes m_profile, but on Qt5.11 it does not unleash the dll
	delete m_loader;
	
	emit message("Unload profile " + m_dllFileName,Qt::black);
	m_dllFileName = "";
	m_loader = nullptr;
	m_profile = nullptr;
	return b;
}

// IS LOADED //////////////////////////////////////////////////////////////////
bool ProfileEngine::isLoaded() const
{
	return (m_loader != nullptr && !m_thread->isRunning());
}






// PLAY ///////////////////////////////////////////////////////////////////////
void ProfileEngine::play(int dtms)
{
	if (m_thread->isRunning() || !m_profile || m_timer->isActive())
	{
		emit initDone(false);
		return;
	}
	
	// initialize profile
	emit message("Starting " + m_dllFileName,Qt::black);
	m_profile->setTimeStep(dtms);
	m_timer->setInterval(dtms);
	try
	{
		if (!m_profile->play())
		{
			emit message("Failed to initialize profile",Qt::red);
			emit initDone(false);
			return;
		}
	}
	catch (std::exception &e)
	{
		QString msg = "Failed to initialize profile: " + QString{e.what()};
		emit message(msg,Qt::red);
		emit initDone(false);
		return;
	}
	
	if (m_profile->isInitComplete())
		this->slotStartTimer();
}

// IS INITIALIZED /////////////////////////////////////////////////////////////
bool ProfileEngine::isInitialized() const
{
	return m_profile->isInitComplete();
}

// SLOT START TIMER ////////////////////////////////////////////////////////////
void ProfileEngine::slotStartTimer()
{
	// start the loop!
	m_timer->start();
	emit message("Running",Qt::black);
	emit initDone(true);
}

// STOP ////////////////////////////////////////////////////////////////////////
void ProfileEngine::stop()
{
	if (m_thread->isRunning()) {return;}
	m_timer->stop();
	
	if (!m_profile) {return;}
	m_profile->stop();
	emit message("Stop profile " + m_dllFileName,Qt::black);
}

// IS ACTIVE //////////////////////////////////////////////////////////////////
bool ProfileEngine::isActive() const
{
	return (m_timer->isActive() || m_thread->isRunning());
}






// SLOT ONE LOOP //////////////////////////////////////////////////////////////
void ProfileEngine::slotOneLoop()
{
	if (m_thread->isRunning()) {return;}
	if (!m_profile) {return;}
	
	try {m_profile->run();}
	catch (std::exception &e) {emit message(e.what(),Qt::red);}
}

// SLOT REMOTE JOYSTICK DISCONNECTED //////////////////////////////////////////
void ProfileEngine::slotRemoteJoystickDisconnected()
{
	m_timer->stop();
	m_profile->stop();
	emit stopped();
}

