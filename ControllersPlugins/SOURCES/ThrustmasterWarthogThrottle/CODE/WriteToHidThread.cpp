#include "WriteToHidThread.h"
#include "HidDevice.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  LAUNCH WRITE DATA
//  RUN
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
WriteToHidThread::WriteToHidThread(QObject *parent) : QThread(parent)
{
	m_hidDevice = new HidDevice(0x044F,0x0404);
	m_hidDevice->openHidDevice();
}

WriteToHidThread::~WriteToHidThread()
{
	this->wait();
}



// LAUNCH WRITE DATA //////////////////////////////////////////////////////////
void WriteToHidThread::launchWriteData(quint8 flags, quint8 brightness)
{
	m_mutex.lock();
	if (m_queue.size() > 5) {m_queue.clear();} // to avoid accumulation
	m_queue << qMakePair(flags,brightness);
	m_mutex.unlock();
	
	if (!this->isRunning()) {this->start();}
}




// RUN ////////////////////////////////////////////////////////////////////////
void WriteToHidThread::run()
{
	m_mutex.lock();
	if (m_queue.size() == 0)
	{
		m_mutex.unlock();
		return;
	}
	QPair<quint8,quint8> pair = m_queue.takeFirst();
	m_mutex.unlock();
	
	quint8 data[4];
	data[0] = 1;
	data[1] = 6;
	data[2] = pair.first;
	data[3] = pair.second;
	m_hidDevice->writeData(data,4);
	
	this->run();
}



