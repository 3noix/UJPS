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
//
//  SET BUTTON LOCKED
//  SET AXIS LOCKED
//  SET AXIS TRIM
//
//  FLUSH
//  RESET REPORT
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
VirtualJoystick::VirtualJoystick(uint id, uint nbButtons, uint nbAxes, bool bForcedInit) : QObject()
{
	if (id > NB_JOYSTICKS_MAX || nbButtons > 128 || nbAxes > 8)
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
	emit message("vJoy device " + QString::number(m_id) + " successfully configured",Qt::black);
	
	// init trims and locks
	for (bool& b : m_buttonsLocked) {b = false;}
	for (bool& b : m_buttonsNoRewrite) {b = false;}
	for (bool& b : m_axesLocked) {b = false;}
	for (bool& b : m_axesNoRewrite) {b = false;}
	for (LONG& t : m_axesTrim) {t = 0L;}
	
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
bool VirtualJoystick::setButton(uint button, bool bPressed, RewriteOrNot ron)
{
	if (button >= 128 || m_buttonsLocked[button] || m_buttonsNoRewrite[button]) {return false;}
	if (ron == RewriteOrNot::NoRewrite) {m_buttonsNoRewrite[button] = true;}
	
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
bool VirtualJoystick::toggleButton(uint button, RewriteOrNot ron)
{
	bool b = this->getButton(button);
	return this->setButton(button,!b,ron);
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
bool VirtualJoystick::setAxis(uint axis, float value, RewriteOrNot ron, TrimOrNot ton)
{
	if (axis >= 8 || m_axesLocked[axis] || m_axesNoRewrite[axis]) {return false;}
	if (ron == RewriteOrNot::NoRewrite) {m_axesNoRewrite[axis] = true;}
	
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







// FLUSH //////////////////////////////////////////////////////////////////////
bool VirtualJoystick::flush(bool bEvenIfNoChange)
{
	if (!m_reportModified && !bEvenIfNoChange) {return true;}
	bool b = UpdateVJD(m_id, &m_report);
	
	m_reportModified = false;
	for (std::array<bool,128>::iterator it=m_buttonsNoRewrite.begin(); it!=m_buttonsNoRewrite.end(); ++it) {*it = false;}
	for (std::array<bool,8>::iterator it=m_axesNoRewrite.begin(); it!=m_axesNoRewrite.end(); ++it) {*it = false;}
	
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
	m_report.bHats       = 0L;			// DWORD
	m_report.bHatsEx1    = 0L;			// DWORD
	m_report.bHatsEx2    = 0L;			// DWORD
	m_report.bHatsEx3    = 0L;			// DWORD
}

