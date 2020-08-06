#include "GameControllersEnumThread.h"
#include "GameControllerEnumerator.h"
#include "GameController.h"
#include <QMutexLocker>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  ENUMERATE CONTROLLERS ALL AT ONCE
//  ENUMERATE CONTROLLERS ONE BY ONE
//  STOP
//
//  GAME CONTROLLERS
//  RELEASE GAME CONTROLLERS
//  RUN
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GameControllersEnumThread::GameControllersEnumThread(QObject *parent) : QThread{parent}
{
	m_bStop = false;
	m_b1by1 = false;
}

GameControllersEnumThread::~GameControllersEnumThread()
{
	this->stop();
	this->wait();
	qDeleteAll(m_joysticks);
}






// ENUMERATE CONTROLLERS ALL AT ONCE //////////////////////////////////////////
void GameControllersEnumThread::enumerateControllersAllAtOnce()
{
	if (this->isRunning()) {return;}
	
	m_mutex.lock();
	m_bStop = false;
	m_b1by1 = false;
	qDeleteAll(m_joysticks);
	m_joysticks.clear();
	m_mutex.unlock();
	
	if (!this->isRunning()) {this->start();}
}

// ENUMERATE CONTROLLERS ONE BY ONE ///////////////////////////////////////////
void GameControllersEnumThread::enumerateControllersOneByOne()
{
	if (this->isRunning()) {return;}
	
	m_mutex.lock();
	m_bStop = false;
	m_b1by1 = true;
	qDeleteAll(m_joysticks);
	m_joysticks.clear();
	m_mutex.unlock();
	
	if (!this->isRunning()) {this->start();}
}

// STOP ///////////////////////////////////////////////////////////////////////
void GameControllersEnumThread::stop()
{
	QMutexLocker locker{&m_mutex};
	m_bStop = true;
}






// GAME CONTROLLERS ///////////////////////////////////////////////////////////
std::vector<GameController*> GameControllersEnumThread::gameControllers()
{
	QMutexLocker locker{&m_mutex};
	return m_joysticks;
}

// RELEASE GAME CONTROLLERS ///////////////////////////////////////////////////
std::vector<GameController*> GameControllersEnumThread::releaseGameControllers()
{
	QMutexLocker locker{&m_mutex};
	std::vector<GameController*> gcv = m_joysticks;
	m_joysticks.clear();
	return gcv;
}

// RUN ////////////////////////////////////////////////////////////////////////
void GameControllersEnumThread::run()
{
	m_mutex.lock();
	bool b1by1 = m_b1by1;
	m_mutex.unlock();
	
	if (b1by1)
	{
		GameControllerEnumerator e;
		while (!e.hasFinished())
		{
			GameController *gc = e.nextController(); // long step
			QMutexLocker locker{&m_mutex};
			if (gc) {m_joysticks.push_back(gc);}
			if (m_bStop) {return;}
		}
		emit done();
	}
	else
	{
		QMutexLocker locker{&m_mutex};
		m_joysticks = GameControllerEnumerator::enumerateControllers(); // very long step
		emit done();
	}
}

