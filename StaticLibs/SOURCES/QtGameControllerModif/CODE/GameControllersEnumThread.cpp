#include "GameControllersEnumThread.h"
#include "GameController.h"
#include <QMutexLocker>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  ENUMERATE CONTROLLERS
//  GAME CONTROLLERS
//  RELEASE GAME CONTROLLERS
//  RUN
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GameControllersEnumThread::GameControllersEnumThread(QObject *parent) : QThread{parent}
{
}

GameControllersEnumThread::~GameControllersEnumThread()
{
	qDeleteAll(m_joysticks);
	this->wait();
}




// ENUMERATE CONTROLLERS //////////////////////////////////////////////////////
void GameControllersEnumThread::enumerateControllers()
{
	if (this->isRunning()) {return;}
	m_mutex.lock();
	qDeleteAll(m_joysticks);
	m_joysticks.clear();
	m_mutex.unlock();
	if (!this->isRunning()) {this->start();}
}

// GAME CONTROLLERS ///////////////////////////////////////////////////////////
QVector<GameController*> GameControllersEnumThread::gameControllers()
{
	QMutexLocker locker{&m_mutex};
	return m_joysticks;
}

// RELEASE GAME CONTROLLERS ///////////////////////////////////////////////////
QVector<GameController*> GameControllersEnumThread::releaseGameControllers()
{
	QMutexLocker locker{&m_mutex};
	QVector<GameController*> gcv = m_joysticks;
	m_joysticks.clear();
	return gcv;
}

// RUN ////////////////////////////////////////////////////////////////////////
void GameControllersEnumThread::run()
{
	QMutexLocker locker{&m_mutex};
	m_joysticks = GameController::enumerateControllers();
}

