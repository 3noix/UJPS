#include "RemoteJoystickHttp.h"
#include "UjpsHttpServer.h"
#include "Lim.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  URL
//
//  ID
//  DESCRIPTION
//  HARDWARE ID
//  READ GAME CONTROLLER
//  CHANGES
//  ADD CHANGE
//
//  BUTTONS COUNT
//  BUTTON PRESSED
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXES COUNT
//  AXIS VALUE
//  AXIS NAME
//  AXES NAMES
//
//  POVS COUNT
//  POV VALUE
//  POV NAME
//  POVS NAMES
//
//  SET DATA
//  FLUSH
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
RemoteJoystickHttp::RemoteJoystickHttp(const QString &name, uint id) : AbstractRealJoystick{}
{
	m_name = name;
	m_id = id;
	
	m_nbButtons = 128;
	m_nbAxes = 8;
	m_nbPovs = 4;
	for (bool &b : m_buttons) {b = false;}
	for (float &f : m_axes) {f = 0.0f;}
	for (float &f : m_povs) {f = -1.0f;}
}

// URL ////////////////////////////////////////////////////////////////////////
QString RemoteJoystickHttp::url() const
{
	return UjpsHttpServer::instance().url(m_name);
}






// ID /////////////////////////////////////////////////////////////////////////
uint RemoteJoystickHttp::id() const
{
	return m_id;
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString RemoteJoystickHttp::description() const
{
	return m_name;
}

// HARDWARE ID ////////////////////////////////////////////////////////////////
QString RemoteJoystickHttp::hardwareId() const
{
	return {};
}

// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void RemoteJoystickHttp::readGameController()
{
	
}

// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> RemoteJoystickHttp::changes()
{
	QVector<JoystickChange> changes = m_changes;
	m_changes.clear();
	return changes;
}

// ADD CHANGE /////////////////////////////////////////////////////////////////
void RemoteJoystickHttp::addChange(const JoystickChange &ch)
{
	if (ch.type == ControlType::Button) {m_buttons[ch.numButtonAxisPov] = ch.bButtonPressed;}
	else if (ch.type == ControlType::Axis) {m_axes[ch.numButtonAxisPov] = ch.axisOrPovValue;}
	else if (ch.type == ControlType::Pov)  {m_povs[ch.numButtonAxisPov] = ch.axisOrPovValue;}
	
	m_changes << ch;
}






// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint RemoteJoystickHttp::buttonsCount() const {return m_nbButtons;}

// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool RemoteJoystickHttp::buttonPressed(uint button) const
{
	if (button >= m_nbButtons) {return false;}
	return m_buttons[button];
}

// BUTTON NAME ////////////////////////////////////////////////////////////////
QString RemoteJoystickHttp::buttonName(uint button) const
{
	if (button >= m_nbButtons) {return QString();}
	return "Button " + QString::number(button+1);
}

// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList RemoteJoystickHttp::buttonsNames() const
{
	QStringList list;
	for (uint i=0; i<this->buttonsCount(); ++i) {list << this->buttonName(i);}
	return list;
}






// AXES COUNT /////////////////////////////////////////////////////////////////
uint RemoteJoystickHttp::axesCount() const {return m_nbAxes;}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float RemoteJoystickHttp::axisValue(uint axis) const
{
	if (axis >= m_nbAxes) {return 0.0f;}
	return m_axes[axis];
}

// AXIS NAME //////////////////////////////////////////////////////////////////
QString RemoteJoystickHttp::axisName(uint axis) const
{
	if (axis >= m_nbAxes) {return QString();}
	return "Axis " + QString::number(axis+1);
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList RemoteJoystickHttp::axesNames() const
{
	QStringList list;
	for (uint i=0; i<this->axesCount(); ++i) {list << this->axisName(i);}
	return list;
}






// POVS COUNT /////////////////////////////////////////////////////////////////
uint RemoteJoystickHttp::povsCount() const {return m_nbPovs;}

// POV VALUE //////////////////////////////////////////////////////////////////
float RemoteJoystickHttp::povValue(uint pov) const
{
	if (pov >= m_nbPovs) {return -1.0f;}
	return m_povs[pov];
}

// POV NAME ///////////////////////////////////////////////////////////////////
QString RemoteJoystickHttp::povName(uint pov) const
{
	if (pov >= m_nbPovs) {return QString();}
	return "POV " + QString::number(pov+1);
}

// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList RemoteJoystickHttp::povsNames() const
{
	QStringList list;
	for (uint i=0; i<this->povsCount(); ++i) {list << this->povName(i);}
	return list;
}






// SET DATA ///////////////////////////////////////////////////////////////////
void RemoteJoystickHttp::setData(const QString &str, QVariant v)
{
	Q_UNUSED(str)
	Q_UNUSED(v)
}

// FLUSH //////////////////////////////////////////////////////////////////////
void RemoteJoystickHttp::flush()
{
	// nothing
}