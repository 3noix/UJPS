#include "VirtualJoystick.h"
#include "Lim.h"
#include "ExceptionFailedToStartVJoy.h"
#include "ExceptionFailedToAcquireVJoyDevice.h"
#include "ExceptionBadVirtualJoystickArgs.h"

#include "vJoyModifiedInterface/vjoyinterface.h"
#include "bitsLong.h"

#include <QProcess>
#include <QDir>

const int NB_JOYSTICKS_MAX = 16;

uint VirtualJoystick::m_nbInstances = 0;
bool VirtualJoystick::m_bUseVJoyConfigExe = false;
QString VirtualJoystick::m_vJoyConfigExeDirPath{};
QString VirtualJoystick::m_vJoyConfigExeFileName{};


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  ENABLE VJOYT IF NOT
//  DISABLE VJOY
//  IS VJOY DEVICE FREE
//  SET VJOY CONFIG OPTIONS
//
//  SET BUTTON
//  TOGGLE BUTTON
//  GET BUTTON
//  SET AXIS
//  GET AXIS
//  SET POV
//  GET POV
//
//  SET BUTTON LOCKED
//  SET AXIS LOCKED
//  SET AXIS TRIM
//  SET POV LOCKED
//
//  FLUSH
//  RESET REPORT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
VirtualJoystick::VirtualJoystick(uint id, uint nbButtons, uint nbAxes, uint nbPovs, bool bForcedInit) : QObject()
{
	if (id > NB_JOYSTICKS_MAX || nbButtons > 128 || nbAxes > 8 || nbPovs > 4)
		throw ExceptionBadVirtualJoystickArgs{};
	
	if (m_nbInstances == 0 && m_bUseVJoyConfigExe)
	{
		if (QDir::currentPath() != m_vJoyConfigExeDirPath)
		{
			// change current directory
			if (!QDir::setCurrent(m_vJoyConfigExeDirPath)) {throw ExceptionFailedToStartVJoy("FAILED to change current directory for vJoy directory");}
			emit message("Current directory changed",Qt::black);
		}
		
		// check if vJoy enabled, otherwise try to enable it
		VirtualJoystick::enableVJoyIfNot();
		
		// reset all vJoy devices
		QString command = m_vJoyConfigExeFileName + " -r";
		emit message("RESET VJOY DEVICES: "+command,Qt::black);
		QProcess::execute(command);
	}
	
	
	m_id = id;
	m_reportModified = false;
	m_report.bDevice = (BYTE)m_id;
	
	// create vJoy device
	if (m_bUseVJoyConfigExe)
	{
		QString command = m_vJoyConfigExeFileName + " " + QString::number(m_id) + " -f -a X Y Z Rx Ry Rz Sl0 Sl1 -b " + QString::number(nbButtons);
		emit message("CREATE VJOY DEVICE: "+command,Qt::black);
		QProcess::execute(command);
	}
	
	// get status
	VjdStat status = GetVJDStatus(m_id);
	if (status == VJD_STAT_OWN)
		throw ExceptionFailedToAcquireVJoyDevice("vJoy device " + QString::number(m_id).toStdString() + " is already owned by this feeder");
	else if (status == VJD_STAT_BUSY)
		throw ExceptionFailedToAcquireVJoyDevice("vJoy device " + QString::number(m_id).toStdString() + " is already owned by another feeder");
	else if (status == VJD_STAT_MISS)
		throw ExceptionFailedToAcquireVJoyDevice("vJoy device " + QString::number(m_id).toStdString() + " is not installed or disabled");
	else if (status != VJD_STAT_FREE)
		throw ExceptionFailedToAcquireVJoyDevice("vJoy device " + QString::number(m_id).toStdString() + " could not be acquired for an unknown reason");
	
	// acquire device
	if (!AcquireVJD(m_id))
		throw ExceptionFailedToAcquireVJoyDevice("Failed to acquire vJoy device " + QString::number(m_id).toStdString());
	//ResetVJD(m_id);
	m_bUseDiscretePovs = (GetVJDDiscPovNumber(m_id) > 0);
	emit message("vJoy device " + QString::number(m_id) + " successfully configured",Qt::black);
	
	// init trims and locks
	for (bool& b : m_buttonsLocked)   {b = false;}
	for (bool& b : m_buttonsHighPrio) {b = false;}
	for (bool& b : m_axesLocked)      {b = false;}
	for (bool& b : m_axesHighPrio)    {b = false;}
	for (LONG& t : m_axesTrim)        {t = 0L;}
	for (bool& b : m_povsLocked)      {b = false;}
	for (bool& b : m_povsHighPrio)    {b = false;}
	
	// init HID report
	this->resetReport();
	if (bForcedInit) {this->flush();}
	
	m_nbInstances++;
}

// DESTRUCTEUR ////////////////////////////////////////////////////////////////
VirtualJoystick::~VirtualJoystick()
{
	emit message("Releasing vJoy device " + QString::number(m_id),Qt::black);
	//std::cout << "Releasing vJoy device " << m_id;
	RelinquishVJD(m_id);
	
	m_nbInstances--;
	
	if (m_nbInstances == 0)
	{
		if (vJoyEnabled())
			VirtualJoystick::disableVJoy();
	}
}








// ENABLE VJOY IF NOT /////////////////////////////////////////////////////////
bool VirtualJoystick::enableVJoyIfNot()
{
	if (!m_bUseVJoyConfigExe) {return false;}
	
	if (!vJoyEnabled())
	{
		QString command = m_vJoyConfigExeFileName + " enable on";
		emit message("ENABLE VJOY: "+command,Qt::black);
		QProcess::execute(command);
		if (vJoyEnabled())
		{
			emit message("vJoy enabled",Qt::black);
			return true;
		}
		else
		{
			throw ExceptionFailedToStartVJoy("FAILED to start vJoy (must be run as Administrator to do so)");
			return false;
		}
	}
	else
	{
		emit message("vJoy is already enabled",Qt::black);
		return true;
	}
}


// DISABLE VJOY ///////////////////////////////////////////////////////////////
void VirtualJoystick::disableVJoy()
{
	if (!m_bUseVJoyConfigExe) {return;}
	
	QString command = m_vJoyConfigExeFileName + " enable off";
	emit message("EXECUTING: "+command,Qt::black);
	//std::cout << "DISABLE VJOY: " << qPrintable(command);
	QProcess::execute(command);
}

// IS VJOY DEVICE FREE ////////////////////////////////////////////////////////
bool VirtualJoystick::isVJoyDeviceFree(uint numDevice)
{
	VjdStat status = GetVJDStatus(numDevice);
	return (status == VJD_STAT_FREE || status == VJD_STAT_MISS);
}

// SET VJOY CONFIG OPTIONS ////////////////////////////////////////////////////
void VirtualJoystick::setVJoyConfigOptions(bool bUseIt, QString exeFilePath)
{
	QStringList list = exeFilePath.replace("\\","/").split('/',QString::SkipEmptyParts);
	if (list.size() == 0)
	{
		m_bUseVJoyConfigExe = bUseIt;
		m_vJoyConfigExeDirPath = "";
		m_vJoyConfigExeFileName = exeFilePath;
	}
	else
	{
		m_bUseVJoyConfigExe = bUseIt;
		m_vJoyConfigExeFileName = list.takeLast();
		m_vJoyConfigExeDirPath = list.join("/");
	}
}












// SET BUTTON /////////////////////////////////////////////////////////////////
bool VirtualJoystick::setButton(uint button, bool bPressed, Priority p)
{
	if (button >= 128 || m_buttonsLocked[button]) {return false;}
	if (p == Priority::Low && m_buttonsHighPrio[button]) {return false;}
	if (p == Priority::High) {m_buttonsHighPrio[button] = true;}
	
	if (button < 32 && bPressed)        {m_report.lButtons    |=  bitLong(button);}
	else if (button < 32 && !bPressed)  {m_report.lButtons    &= ~bitLong(button);}
	else if (button < 64 && bPressed)   {m_report.lButtonsEx1 |=  bitLong(button%32);}
	else if (button < 64 && !bPressed)  {m_report.lButtonsEx1 &= ~bitLong(button%32);}
	else if (button < 96 && bPressed)   {m_report.lButtonsEx2 |=  bitLong(button%32);}
	else if (button < 96 && !bPressed)  {m_report.lButtonsEx2 &= ~bitLong(button%32);}
	else if (button < 128 && bPressed)  {m_report.lButtonsEx3 |=  bitLong(button%32);}
	else if (button < 128 && !bPressed) {m_report.lButtonsEx3 &= ~bitLong(button%32);}
	
	m_reportModified = true;
	return true;
}

// TOGGLE BUTTON //////////////////////////////////////////////////////////////
bool VirtualJoystick::toggleButton(uint button, Priority p)
{
	bool b = this->getButton(button);
	return this->setButton(button,!b,p);
}

// GET BUTTON /////////////////////////////////////////////////////////////////
bool VirtualJoystick::getButton(uint button) const
{
	if (button >= 128) {return false;}
	
	if (button < 32)       {return (m_report.lButtons    & bitLong(button));}
	else if (button < 64)  {return (m_report.lButtonsEx1 & bitLong(button%32));}
	else if (button < 96)  {return (m_report.lButtonsEx2 & bitLong(button%32));}
	else if (button < 128) {return (m_report.lButtonsEx3 & bitLong(button%32));}
	
	return false;
}

// SET AXIS ///////////////////////////////////////////////////////////////////
bool VirtualJoystick::setAxis(uint axis, float value, Priority p, TrimOrNot ton)
{
	if (axis >= 8 || m_axesLocked[axis]) {return false;}
	if (p == Priority::Low && m_axesHighPrio[axis]) {return false;}
	if (p == Priority::High) {m_axesHighPrio[axis] = true;}
	
	LONG v = (value+1.0f) * 16384.0f;
	if (ton == TrimOrNot::UseTrim) {v += m_axesTrim[axis];}
	v = lim<LONG>(v,0L,32768L);
	
	if (axis == 0)      {m_report.wAxisX    = v;}
	else if (axis == 1) {m_report.wAxisY    = v;}
	else if (axis == 2) {m_report.wAxisZ    = v;}
	else if (axis == 3) {m_report.wAxisXRot = v;}
	else if (axis == 4) {m_report.wAxisYRot = v;}
	else if (axis == 5) {m_report.wAxisZRot = v;}
	else if (axis == 6) {m_report.wSlider   = v;}
	else if (axis == 7) {m_report.wDial     = v;}
	
	m_reportModified = true;
	return true;
}

// GET AXIS ///////////////////////////////////////////////////////////////////
float VirtualJoystick::getAxis(uint axis) const
{
	if (axis >= 8) {return 0.0f;}
	LONG value2 = this->getAxisPrivate(axis);
	float value = (2.0f*value2/32768.0f) - 1.0f;
	return value;
}

LONG VirtualJoystick::getAxisPrivate(uint axis) const
{
	if (axis >= 8) {return 16384L;}
	
	if (axis == 0)      {return m_report.wAxisX;}
	else if (axis == 1) {return m_report.wAxisY;}
	else if (axis == 2) {return m_report.wAxisZ;}
	else if (axis == 3) {return m_report.wAxisXRot;}
	else if (axis == 4) {return m_report.wAxisYRot;}
	else if (axis == 5) {return m_report.wAxisZRot;}
	else if (axis == 6) {return m_report.wSlider;}
	else if (axis == 7) {return m_report.wDial;}
	
	return 16384L;
}

// SET POV ////////////////////////////////////////////////////////////////////
bool VirtualJoystick::setPov(uint pov, float value, Priority p)
{
	if (pov >= 4 || m_povsLocked[pov]) {return false;}
	if (p == Priority::Low && m_povsHighPrio[pov]) {return false;}
	if (p == Priority::High) {m_povsHighPrio[pov] = true;}
	
	if (!m_bUseDiscretePovs)
	{
		DWORD v = -1u;
		if (value >= 0.0f && value < 360.0f)
		{
			v = (DWORD) (value*100.0f);
			v = lim<DWORD>(v,0u,35999u);
		}
		
		if (pov == 0)      {m_report.bHats    = v;}
		else if (pov == 1) {m_report.bHatsEx1 = v;}
		else if (pov == 2) {m_report.bHatsEx2 = v;}
		else if (pov == 3) {m_report.bHatsEx3 = v;}
	}
	else
	{
		DWORD position = -1u;
		if (value >= 0.0f && value < 360.0f)
		{
			if (value < 60.0f  || value > 300.0f)      {position = 0;}
			else if (value > 30.0f  && value < 150.0f) {position = 1;}
			else if (value > 120.0f && value < 240.0f) {position = 2;}
			else if (value > 210.0f && value < 330.0f) {position = 3;}
		}
		
		position = (position<<(4*pov));
		DWORD mask = (0x0000000F<<(4*pov));
		DWORD v = m_report.bHats;
		v = ((~mask)&v) | (mask&(position));
		m_report.bHats = v;
	}
	
	m_reportModified = true;
	return true;
}

// GET POV ////////////////////////////////////////////////////////////////////
float VirtualJoystick::getPov(uint pov) const
{
	if (pov >= 4) {return -1.0f;}
	
	if (!m_bUseDiscretePovs)
	{
		DWORD value2 = this->getPovPrivate(pov);
		if (value2 == -1UL) {return -1.0f;}
		float value = 0.01f * value2;
		return value;
	}
	else
	{
		DWORD mask = (0x0000000F<<(4*pov));
		DWORD position = (mask & m_report.bHats) >> (4*pov);
		if (position < 4) {return 90.0f * position;}
		return -1.0f;
	}
}

DWORD VirtualJoystick::getPovPrivate(uint pov) const
{
	if (pov == 0)      {return m_report.bHats;}
	else if (pov == 1) {return m_report.bHatsEx1;}
	else if (pov == 2) {return m_report.bHatsEx2;}
	else if (pov == 3) {return m_report.bHatsEx3;}
	
	return -1;
}








// SET BUTTON LOCKED //////////////////////////////////////////////////////////
void VirtualJoystick::setButtonLocked(uint button, bool locked)
{
	if (button >= 128) {return;}
	m_buttonsLocked[button] = locked;
}

// SET AXIS LOCKED ////////////////////////////////////////////////////////////
void VirtualJoystick::setAxisLocked(uint axis, bool locked)
{
	if (axis >= 8) {return;}
	m_axesLocked[axis] = locked;
}

// SET AXIS TRIM //////////////////////////////////////////////////////////////
void VirtualJoystick::setAxisTrim(uint axis, float trimF, AbsoluteOrRelative aor)
{
	if (axis >= 8) {return;}
	
	LONG newTrimTmp = trimF * 16384.0f;
	if (aor == AbsoluteOrRelative::Absolute)
		m_axesTrim[axis] = lim<LONG>(newTrimTmp,-16384L,16384L);
	else
		m_axesTrim[axis] = lim<LONG>(m_axesTrim[axis]+newTrimTmp,-16384L,16384L);
	
	LONG oldTrim = m_axesTrim[axis];
	LONG oldAxisValue = this->getAxisPrivate(axis);
	LONG newAxisValue = lim<LONG>(oldAxisValue+m_axesTrim[axis]-oldTrim,0L,32768L);
	
	if (axis == 0)      {m_report.wAxisX    = newAxisValue;}
	else if (axis == 1) {m_report.wAxisY    = newAxisValue;}
	else if (axis == 2) {m_report.wAxisZ    = newAxisValue;}
	else if (axis == 3) {m_report.wAxisXRot = newAxisValue;}
	else if (axis == 4) {m_report.wAxisYRot = newAxisValue;}
	else if (axis == 5) {m_report.wAxisZRot = newAxisValue;}
	else if (axis == 6) {m_report.wSlider   = newAxisValue;}
	else if (axis == 7) {m_report.wDial     = newAxisValue;}
	
	m_reportModified = true;
}

// SET POV LOCKED /////////////////////////////////////////////////////////////
void VirtualJoystick::setPovLocked(uint pov, bool locked)
{
	if (pov >= 4) {return;}
	m_povsLocked[pov] = locked;
}







// FLUSH //////////////////////////////////////////////////////////////////////
bool VirtualJoystick::flush(bool bEvenIfNoChange)
{
	if (!m_reportModified && !bEvenIfNoChange) {return true;}
	bool b = UpdateVJD(m_id, &m_report);
	
	m_reportModified = false;
	for (std::array<bool,128>::iterator it=m_buttonsHighPrio.begin(); it!=m_buttonsHighPrio.end(); ++it) {*it = false;}
	for (std::array<bool,8>::iterator it=m_axesHighPrio.begin(); it!=m_axesHighPrio.end(); ++it) {*it = false;}
	for (std::array<bool,4>::iterator it=m_povsHighPrio.begin(); it!=m_povsHighPrio.end(); ++it) {*it = false;}
	
	return b;
}

// RESET REPORT ///////////////////////////////////////////////////////////////
void VirtualJoystick::resetReport()
{
	m_report.bDevice     = (BYTE)m_id;	// BYTE
	m_report.wThrottle   = 0L;			// LONG
	m_report.wRudder     = 0L;			// LONG
	m_report.wAileron    = 0L;			// LONG
	m_report.wAxisX      = 0x4000L;		// LONG
	m_report.wAxisY      = 0x4000L;		// LONG
	m_report.wAxisZ      = 0x4000L;		// LONG
	m_report.wAxisXRot   = 0x4000L;		// LONG
	m_report.wAxisYRot   = 0x4000L;		// LONG
	m_report.wAxisZRot   = 0x4000L;		// LONG
	m_report.wSlider     = 0x4000L;		// LONG
	m_report.wDial       = 0x4000L;		// LONG
	m_report.wWheel      = 0L;			// LONG
	m_report.wAxisVX     = 0L;			// LONG
	m_report.wAxisVY     = 0L;			// LONG
	m_report.wAxisVZ     = 0L;			// LONG
	m_report.wAxisVBRX   = 0L;			// LONG
	m_report.wAxisVBRY   = 0L;			// LONG
	m_report.wAxisVBRZ   = 0L;			// LONG
	m_report.lButtons    = 0L;			// LONG
	m_report.lButtonsEx1 = 0L;			// LONG
	m_report.lButtonsEx2 = 0L;			// LONG
	m_report.lButtonsEx3 = 0L;			// LONG
	m_report.bHats       = -1L;			// DWORD
	m_report.bHatsEx1    = -1L;			// DWORD
	m_report.bHatsEx2    = -1L;			// DWORD
	m_report.bHatsEx3    = -1L;			// DWORD
}

