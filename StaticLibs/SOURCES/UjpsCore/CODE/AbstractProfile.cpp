#include "AbstractProfile.h"
#include "RealJoysticksManager.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  SET TIME STEP
//  TIME STEP
//  MS 2 CYCLES
//  SET REAL JOYSTICKS MANAGER
//  REAL JOYSTICKS MANAGER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AbstractProfile::AbstractProfile() : QObject{}
{
	m_dtms = 15;
	m_rjm = nullptr;
}

AbstractProfile::~AbstractProfile()
{
	if (m_rjm)
	{
		delete m_rjm;
		m_rjm = nullptr;
	}
}

// SET TIME STEP //////////////////////////////////////////////////////////////
void AbstractProfile::setTimeStep(int dtms)
{
	Q_ASSERT(dtms > 0);
	m_dtms = dtms;
}

// TIME STEP //////////////////////////////////////////////////////////////////
int AbstractProfile::timeStep() const
{
	return m_dtms;
}

// MS 2 CYCLES ////////////////////////////////////////////////////////////////
uint AbstractProfile::ms2cycles(uint msecs) const
{
	Q_ASSERT(msecs > 0);
	return ((msecs%m_dtms) ? msecs/m_dtms+1 : msecs/m_dtms);
}

// SET REAL JOYSTICKS MANAGER /////////////////////////////////////////////////
void AbstractProfile::setRealJoysticksManager(RealJoysticksManager *rjm)
{
	m_rjm = rjm;
	QObject::connect(m_rjm, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
}

// REAL JOYSTICKS MANAGER /////////////////////////////////////////////////////
RealJoysticksManager* AbstractProfile::realJoysticksManager() const
{
	return m_rjm;
}

