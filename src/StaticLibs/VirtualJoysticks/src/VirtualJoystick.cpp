#include "VirtualJoystick.h"
#include "VirtualJoystickPrivate.h"


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
VirtualJoystick::VirtualJoystick(uint id, bool bForcedInit) : QObject{}
{
	m_pimpl = new VirtualJoystickPrivate{id,bForcedInit};
	QObject::connect(m_pimpl, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
}

// DESTRUCTEUR ////////////////////////////////////////////////////////////////
VirtualJoystick::~VirtualJoystick()
{
	delete m_pimpl;
}




// FORWARDING /////////////////////////////////////////////////////////////////
bool VirtualJoystick::setButton(uint button, bool bPressed, Priority p) {return m_pimpl->setButton(button,bPressed,p);}
bool VirtualJoystick::toggleButton(uint button, Priority p) {return m_pimpl->toggleButton(button,p);}
bool VirtualJoystick::getButton(uint button) const {return m_pimpl->getButton(button);}
bool VirtualJoystick::setAxis(uint axis, float value, Priority p, TrimOrNot ton) {return m_pimpl->setAxis(axis,value,p,ton);}
float VirtualJoystick::getAxis(uint axis) const {return m_pimpl->getAxis(axis);}
bool VirtualJoystick::setPov(uint pov, float value, Priority p) {return m_pimpl->setPov(pov,value,p);}
float VirtualJoystick::getPov(uint pov) const {return m_pimpl->getPov(pov);}

void VirtualJoystick::setButtonLocked(uint button, bool locked) {m_pimpl->setButtonLocked(button,locked);}
void VirtualJoystick::setAxisLocked(uint axis, bool locked) {m_pimpl->setAxisLocked(axis,locked);}
void VirtualJoystick::setAxisTrim(uint axis, float trim, AbsoluteOrRelative aor) {m_pimpl->setAxisTrim(axis,trim,aor);}
void VirtualJoystick::setPovLocked(uint pov, bool locked) {m_pimpl->setPovLocked(pov,locked);}

void VirtualJoystick::resetReport() {m_pimpl->resetReport();}
bool VirtualJoystick::flush(bool bEvenIfNoChange) {return m_pimpl->flush(bEvenIfNoChange);}
bool VirtualJoystick::isVJoyDeviceFree(uint numDevice) {return m_pimpl->isVJoyDeviceFree(numDevice);}

