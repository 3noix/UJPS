#include "EnhancedJoystick.h"
#include "Lim.h"
#include "CURVES/SCurve.h"
#include "CURVES/JCurve.h"
#include "CURVES/CustomCurve.h"
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
//  BUTTON COUNT
//  BUTTON PRESSED
//  BUTTON NAME
//  BUTTONS NAMES
//
//  AXIS COUNT
//  AXIS VALUE
//  AXIS NAME
//  AXES NAMES
//
//  SET DATA
//
//  SET BUTTON LOCKED
//  SET AXIS LOCKED
//  SET AXIS TRIM
//  AXIS RAW VALUE
//
//  SET S CURVE
//  SET J CURVE
//  SET CUSTOM CURVE
//  SET CURVE
//  REMOVE CURVE
//
//  UPDATE AXIS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
EnhancedJoystick::EnhancedJoystick(AbstractRealJoystick *j, bool bOwn) : AbstractRealJoystick()
{
	if (!j) {throw ExceptionNoDecoratedJoystick{};}
	m_j = j;
	m_bOwn = bOwn;
	
	for (bool& b : m_buttonsLocked) {b = false;}
	for (bool& b : m_axesLocked) {b = false;}
	for (float& f : m_axesTrim) {f = 0.0f;}
	for (float& f : m_axesValuesBeforeLock) {f = 0.0f;}
	for (AbstractAxisCurve*& c : m_axesCurves) {c = nullptr;}
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
	// recover changes of the embedded object
	QVector<JoystickChange> chgts = m_j->changes();
	int n = chgts.size();
	
	// remove or modify some of them function of locking and axes curves
	for (int i=n-1; i>=0; --i)
	{
		JoystickChange &ch = chgts[i];
		bool bGoodJoystick = ch.joystick->id() == this->id();
		bool bLockedButton = (ch.type == ControlType::Button && m_buttonsLocked[ch.numButtonOrAxis]);
		bool bLockedAxis = (ch.type == ControlType::Axis && ch.numButtonOrAxis < 8 && m_axesLocked[ch.numButtonOrAxis]);
		bool bNotLockedAxis = (ch.type == ControlType::Axis && ch.numButtonOrAxis < 8 && !m_axesLocked[ch.numButtonOrAxis]);
		
		// if locked, we remove the event
		if (bGoodJoystick && (bLockedButton || bLockedAxis)) {chgts.removeAt(i);}
		else if (bGoodJoystick && bNotLockedAxis)
		{
			float v = ch.axisValue + m_axesTrim[ch.numButtonOrAxis];	// we add the trim
			if (m_axesCurves[ch.numButtonOrAxis])
				v = m_axesCurves[ch.numButtonOrAxis]->run(v);			// we apply the curve
			ch.axisValue = lim<float>(v,-1.0f,1.0f);					// we limit between -1 and 1
		}
	}
	
	// add a change (axis position) in case of a change in trim or curve,
	// even if the axis of the embedded object did not move
	// in order not to wait for it to move
	for (uint axis : m_axesToUpdate)
	{
		for (const JoystickChange &ch : chgts)
		{
			if (ch.joystick && ch.joystick->id() == this->id() && ch.type == ControlType::Axis && ch.numButtonOrAxis == axis)
				continue;
		}
		chgts << JoystickChange{this,ControlType::Axis,axis,false,this->axisValue(axis)};
	}
	m_axesToUpdate.clear();
	
	return chgts;
}



// BUTTON COUNT ///////////////////////////////////////////////////////////////
uint EnhancedJoystick::buttonCount() const {return m_j->buttonCount();}
// BUTTON PRESSED /////////////////////////////////////////////////////////////
bool EnhancedJoystick::buttonPressed(uint button) const {return m_j->buttonPressed(button);}
// BUTTON NAME ////////////////////////////////////////////////////////////////
QString EnhancedJoystick::buttonName(uint button) const {return m_j->buttonName(button);}
// BUTTONS NAMES //////////////////////////////////////////////////////////////
QStringList EnhancedJoystick::buttonsNames() const {return m_j->buttonsNames();}


// AXIS COUNT /////////////////////////////////////////////////////////////////
uint EnhancedJoystick::axisCount() const {return m_j->axisCount();}
// AXIS VALUE /////////////////////////////////////////////////////////////////
float EnhancedJoystick::axisValue(uint axis) const
{
	if (axis >= 8) {return 0.0f;}
	if (m_axesLocked[axis]) {return m_axesValuesBeforeLock[axis];}
	
	float v = m_j->axisValue(axis);
	v += m_axesTrim[axis];										// we add the trim
	if (m_axesCurves[axis]) {v = m_axesCurves[axis]->run(v);}	// we apply the curve if needed
	return lim<float>(v, -1.0f, 1.0f);							// we limit between -1 and 1
}
// AXIS NAME //////////////////////////////////////////////////////////////////
QString EnhancedJoystick::axisName(uint axis) const {return m_j->axisName(axis);}
// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList EnhancedJoystick::axesNames() const {return m_j->axesNames();}


// SET DATA ///////////////////////////////////////////////////////////////////
void EnhancedJoystick::setData(const QString &str, QVariant v) {m_j->setData(str,v);}


// SET BUTTON LOCKED //////////////////////////////////////////////////////////
void EnhancedJoystick::setButtonLocked(uint button, bool locked)
{
	if (button >= 128) {return;}
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





// SET S CURVE ////////////////////////////////////////////////////////////////
void EnhancedJoystick::setSCurve(uint axis, float lowerDZ, float centerDZ, float upperDZ, float curve, float zoom)
{
	if (axis >= 8) {return;}
	this->removeCurve(axis);
	m_axesCurves[axis] = new SCurve(lowerDZ,centerDZ,upperDZ,curve,zoom);
	this->updateAxis(axis);
}

// SET J CURVE ////////////////////////////////////////////////////////////////
void EnhancedJoystick::setJCurve(uint axis, float zoom)
{
	if (axis >= 8) {return;}
	this->removeCurve(axis);
	m_axesCurves[axis] = new JCurve(zoom);
	this->updateAxis(axis);
}

// SET CUSTOM CURVE ///////////////////////////////////////////////////////////
void EnhancedJoystick::setCustomCurve(uint axis, const std::vector<float> &points)
{
	if (axis >= 8) {return;}
	this->removeCurve(axis);
	
	int n = points.size();
	if (n%2 == 0 && n > 0)
	{
		m_axesCurves[axis] = new CustomCurve(points);
		this->updateAxis(axis);
	}
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



