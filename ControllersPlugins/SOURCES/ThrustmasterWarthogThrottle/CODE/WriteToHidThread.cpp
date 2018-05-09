#include "WriteToHidThread.h"
#include "HidDevice.h"
#include <QMutexLocker>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  LAUNCH WRITE DATA
//  STOP
//  RUN
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
WriteToHidThread::WriteToHidThread(QObject *parent) : QThread(parent)
{
	m_abort = false;
	
	m_hidDevice = new HidDevice(0x044F,0x0404);
	m_hidDevice->openHidDevice();
}

WriteToHidThread::~WriteToHidThread()
{
	this->stop();
	this->wait();
	delete m_hidDevice;
}





// LAUNCH WRITE DATA //////////////////////////////////////////////////////////
void WriteToHidThread::launchWriteData(quint8 flags, quint8 brightness)
{
	m_mutex.lock();
	if (m_abort || m_queue.size() > 5) {m_queue.clear();} // to avoid accumulation
	if (!m_abort) {m_queue << qMakePair(flags,brightness);}
	m_mutex.unlock();
	
	if (!this->isRunning()) {this->start();}
}

// STOP ///////////////////////////////////////////////////////////////////////
void WriteToHidThread::stop()
{
	QMutexLocker locker{&m_mutex};
	m_abort = true;
}





// RUN ////////////////////////////////////////////////////////////////////////
void WriteToHidThread::run()
{
	// get the first task to do
	QMutexLocker locker{&m_mutex};
	if (m_abort || m_queue.size() == 0) {return;}
	QPair<quint8,quint8> pair = m_queue.takeFirst();
	locker.unlock();
	
	while (true)
	{
		// we do the work
		quint8 data[4];
		data[0] = 1;
		data[1] = 6;
		data[2] = pair.first;
		data[3] = pair.second;
		m_hidDevice->writeData(data,4); // it waits for finished before continuing
		
		// we verify if there is no other work to do
		locker.relock();
		if (m_abort || m_queue.size() == 0) {return;}
		pair = m_queue.takeFirst();
		locker.unlock();
	}
}

