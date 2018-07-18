#include "EnhancedJoystick.h"
#include "Lim.h"
#include "CURVES/AbstractAxisCurve.h"
#include "ExceptionNoDecoratedJoystick.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  ID
//  DESCRIPTION
//  HARDWARE ID
//  READ GAME CONTROLLER
//  CHANGES
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
//
//  ROTATE AXES
//  REMOVE AXIS ROTATION
//
//  SET BUTTON LOCKED
//  SET AXIS LOCKED
//  SET AXIS TRIM
//  AXIS RAW VALUE
//  SET POV LOCKED
//
//  SET CURVE
//  REMOVE CURVE
//  UPDATE AXIS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
EnhancedJoystick::EnhancedJoystick(AbstractRealJoystick *j, bool bOwn) : AbstractRealJoystick{}, m_axesRotator{j}
{
	if (!j) {throw ExceptionNoDecoratedJoystick{};}
	m_j = j;
	m_bOwn = bOwn;
	
	for (bool& b : m_buttonsLocked) {b = false;}
	for (bool& b : m_buttonsValuesBeforeLock) {b = false;}
	for (bool& b : m_axesLocked) {b = false;}
	for (float& f : m_axesTrim) {f = 0.0f;}
	for (float& f : m_axesValuesBeforeLock) {f = 0.0f;}
	for (AbstractAxisCurve*& c : m_axesCurves) {c = nullptr;}
	for (bool& b : m_povsLocked) {b = false;}
	for (float& f : m_povsValuesBeforeLock) {f = -1.0f;}
}

EnhancedJoystick::~EnhancedJoystick()
{
	if (m_bOwn && m_j)
	{
		delete m_j;
		m_j = nullptr;
	}
	
	qDeleteAll(m_axesCurves);
}




// ID /////////////////////////////////////////////////////////////////////////
uint EnhancedJoystick::id() const {return m_j->id();}
// DESCRIPTION ////////////////////////////////////////////////////////////////
QString EnhancedJoystick::description() const {return m_j->description();}
// HARDWARE ID ////////////////////////////////////////////////////////////////
QString EnhancedJoystick::hardwareId() const {return m_j->hardwareId();}
// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void EnhancedJoystick::readGameController() {m_j->readGameController();}
// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> EnhancedJoystick::changes()
{
	// recover changes of the embedded object (after possible rotations)
	QVector<JoystickChange> chgts = m_axesRotator.changes();
	int n = chgts.size();
	
	// remove or modify some of them function of locking and axes curves
	for (int i=n-1; i>=0; --i)
	{
		JoystickChange &ch = chgts[i];
		bool bLockedButton  = (ch.type == ControlType::Button && ch.numButtonAxisPov < 128 && m_buttonsLocked[ch.numButtonAxisPov]);
		bool bLockedAxis    = (ch.type == ControlType::Axis   && ch.numButtonAxisPov < 8   && m_axesLocked[ch.numButtonAxisPov]);
		bool bNotLockedAxis = (ch.type == ControlType::Axis   && ch.numButtonAxisPov < 8   && !m_axesLocked[ch.numButtonAxisPov]);
		bool bLockedPov     = (ch.type == ControlType::Pov    && ch.numButtonAxisPov < 4   && m_povsLocked[ch.numButtonAxisPov]);
		
		// if locked, we remove the event
		if (bLockedButton || bLockedAxis || bLockedPov) {chgts.removeAt(i);}
		else if (bNotLockedAxis)
		{
			float v = ch.axisOrPovValue + m_axesTrim[ch.numButtonAxisPov];	// we add the trim
			if (m_axesCurves[ch.numButtonAxisPov])
				v = m_axesCurves[ch.numButtonAxisPov]->run(v);			// we apply the curve
			ch.axisOrPovValue = lim<float>(v,-1.0f,1.0f);					// we limit between -1 and 1
		}
	}
	
	// add a change (axis position) in case of a change in trim or curve,
	// even if the axis of the embedded object did not move
	// in order not to wait for it to move
	for (uint axis : m_axesToUpdate)
	{
		for (const JoystickChange &ch : chgts)
		{
			if (ch.joystick && ch.joystick->id() == this->id() && ch.type == ControlType::Axis && ch.numButtonAxisPov == axis)
				continue;
		}
		chgts << JoystickChange{this,ControlType::Axis,axis,false,this->axisValue(axis)};
	}
	m_axesToUpdate.clear();
	
	return chgts;
}



// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint EnhancedJoystick::buttonsCount() const {return m_j->buttonsCount();}
// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool EnhancedJoystick::buttonPressed(uint button) const
{
	if (button >= 128) {return false;}
	if (m_buttonsLocked[button]) {return m_buttonsValuesBeforeLock[button];}
	return m_j->buttonPressed(button);
}
// BUTTON NAME ////////////////////////////////////////////////////////////////
QString EnhancedJoystick::buttonName(uint button) const {return m_j->buttonName(button);}
// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList EnhancedJoystick::buttonsNames() const {return m_j->buttonsNames();}


// AXES COUNT /////////////////////////////////////////////////////////////////
uint EnhancedJoystick::axesCount() const {return m_j->axesCount();}
// AXIS VALUE /////////////////////////////////////////////////////////////////
float EnhancedJoystick::axisValue(uint axis) const
{
	if (axis >= 8) {return 0.0f;}
	if (m_axesLocked[axis]) {return m_axesValuesBeforeLock[axis];}
	
	float v = m_axesRotator.axisValue(axis);					// recover axis value (after probable rotation)
	v += m_axesTrim[axis];										// we add the trim
	if (m_axesCurves[axis]) {v = m_axesCurves[axis]->run(v);}	// we apply the curve if needed
	return lim<float>(v, -1.0f, 1.0f);							// we limit between -1 and 1
}
// AXIS NAME //////////////////////////////////////////////////////////////////
QString EnhancedJoystick::axisName(uint axis) const {return m_j->axisName(axis);}
// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList EnhancedJoystick::axesNames() const {return m_j->axesNames();}



// POVS COUNT /////////////////////////////////////////////////////////////////
uint EnhancedJoystick::povsCount() const {return m_j->povsCount();}
// POV VALUE //////////////////////////////////////////////////////////////////
float EnhancedJoystick::povValue(uint pov) const
{
	if (pov >= 4) {return -1.0f;}
	if (m_povsLocked[pov]) {return m_povsValuesBeforeLock[pov];}
	return m_j->povValue(pov);
}
// POV NAME ///////////////////////////////////////////////////////////////////
QString EnhancedJoystick::povName(uint pov) const {return m_j->povName(pov);}
// POVS NAMES /////////////////////////////////////////////////////////////////
QStringList EnhancedJoystick::povsNames() const {return m_j->povsNames();}




// SET DATA ///////////////////////////////////////////////////////////////////
void EnhancedJoystick::setData(const QString &str, QVariant v) {m_j->setData(str,v);}
// FLUSH //////////////////////////////////////////////////////////////////////
void EnhancedJoystick::flush() {m_j->flush();}


// ROTATE AXES ////////////////////////////////////////////////////////////////
bool EnhancedJoystick::rotateAxes(uint axis1, uint axis2, float angle)
{
	if (!m_axesRotator.rotateAxes(axis1,axis2,angle)) {return false;}
	this->updateAxis(axis1);
	this->updateAxis(axis2);
	return true;
}
// REMOVE AXIS ROTATION ///////////////////////////////////////////////////////
bool EnhancedJoystick::removeAxisRotation(uint axis)
{
	uint axis2 = m_axesRotator.removeAxisRotation(axis);
	if (axis2 == -1u) {return false;}
	this->updateAxis(axis);
	this->updateAxis(axis2);
	return true;
}




// SET BUTTON LOCKED //////////////////////////////////////////////////////////
void EnhancedJoystick::setButtonLocked(uint button, bool locked)
{
	if (button >= 128) {return;}
	m_buttonsValuesBeforeLock[button] = this->buttonPressed(button);
	m_buttonsLocked[button] = locked;
}

// SET AXIS LOCKED ////////////////////////////////////////////////////////////
void EnhancedJoystick::setAxisLocked(uint axis, bool locked)
{
	if (axis >= 8) {return;}
	m_axesValuesBeforeLock[axis] = this->axisValue(axis);
	m_axesLocked[axis] = locked;
}

// SET AXIS TRIM //////////////////////////////////////////////////////////////
void EnhancedJoystick::setAxisTrim(uint axis, float trim, AbsoluteOrRelative aor)
{
	if (axis >= 8) {return;}
	
	if (aor == AbsoluteOrRelative::Absolute)
		m_axesTrim[axis] = lim<float>(trim,-1.0f,1.0f);
	else
		m_axesTrim[axis] = lim<float>(m_axesTrim[axis]+trim,-1.0f,1.0f);
	
	this->updateAxis(axis);
}

// AXIS RAW VALUE /////////////////////////////////////////////////////////////
float EnhancedJoystick::axisRawValue(uint axis) const
{
	if (axis >= 8) {return 0.0f;}
	return m_j->axisValue(axis);
}

// SET POV LOCKED /////////////////////////////////////////////////////////////
void EnhancedJoystick::setPovLocked(uint pov, bool locked)
{
	if (pov >= 4) {return;}
	m_povsValuesBeforeLock[pov] = this->povValue(pov);
	m_povsLocked[pov] = locked;
}









// SET CURVE //////////////////////////////////////////////////////////////////
void EnhancedJoystick::setCurve(uint axis, AbstractAxisCurve *curve)
{
	if (axis >= 8) {return;}
	this->removeCurve(axis);
	
	if (curve) {m_axesCurves[axis] = curve;}
	this->updateAxis(axis);
}

// REMOVE CURVE ///////////////////////////////////////////////////////////////
void EnhancedJoystick::removeCurve(uint axis)
{
	if (axis >= 8) {return;}
	if (m_axesCurves[axis])
	{
		delete m_axesCurves[axis];
		m_axesCurves[axis] = nullptr;
		this->updateAxis(axis);
	}
}

// UPDATE AXIS ////////////////////////////////////////////////////////////////
void EnhancedJoystick::updateAxis(uint axis)
{
	if (m_axesToUpdate.size() == 0 || m_axesToUpdate.back() != axis)
		m_axesToUpdate.push_back(axis);
}



