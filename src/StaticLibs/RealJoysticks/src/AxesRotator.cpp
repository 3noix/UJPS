#include "AxesRotator.h"
#include "AbstractRealJoystick.h"
#include "../../../../include/Other/Lim.h"
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  ROTATE AXES
//  REMOVE AXIS ROTATION
//
//  CHANGES
//  AXIS VALUE
//  SEARCH AXIS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
AxesRotator::AxesRotator(AbstractRealJoystick *j)
{
	m_j = j;
}

// ROTATE AXES ////////////////////////////////////////////////////////////////
bool AxesRotator::rotateAxes(uint axis1, uint axis2, float angleDeg)
{
	if (axis1 == axis2 || axis1 >= m_j->axesCount() || axis2 >= m_j->axesCount()) {return false;}
	if (m_rotatedAxes.contains(axis1) || m_rotatedAxes.contains(axis2)) {return false;}
	m_rotations << AxesRotation{axis1,axis2,angleDeg};
	m_rotatedAxes << axis1 << axis2;
	return true;
}

// REMOVE AXIS ROTATION ///////////////////////////////////////////////////////
uint AxesRotator::removeAxisRotation(uint axis)
{
	if (!m_rotatedAxes.contains(axis)) {return -1u;}
	int nbRotations = m_rotations.size();
	
	for (int i=0; i<nbRotations; ++i)
	{
		uint axis1 = m_rotations[i].axis1;
		uint axis2 = m_rotations[i].axis2;
		m_rotatedAxes.removeAll(axis1);
		m_rotatedAxes.removeAll(axis2);
		
		if (axis == axis1)
		{
			m_rotations.removeAt(i);
			return axis2;
		}
		else if (axis == axis2)
		{
			m_rotations.removeAt(i);
			return axis1;
		}
	}
	
	return -1u;
}

// CHANGES ////////////////////////////////////////////////////////////////////
QVector<JoystickChange> AxesRotator::changes()
{
	// recover original changes
	QVector<JoystickChange> chgts = m_j->changes();
	
	// add new axes changes according to rotations
	QVector<JoystickChange> newChanges;
	for (const JoystickChange &ch : chgts)
	{
		if (ch.type == ControlType::Axis)
		{
			int i = this->searchAxis(ch.numButtonAxisPov);
			if (i == -1) {continue;}
			
			uint axis1 = m_rotations[i].axis1;
			uint axis2 = m_rotations[i].axis2;
			float f1 = m_j->axisValue(axis1);
			float f2 = m_j->axisValue(axis2);
			float angle = piSur180 * m_rotations[i].rotAngleDegrees;
			
			float v1 = cos(angle) * f1 - sin(angle) * f2;
			float v2 = sin(angle) * f1 + cos(angle) * f2;
			
			newChanges << JoystickChange{m_j,ControlType::Axis,axis1,false,v1};
			newChanges << JoystickChange{m_j,ControlType::Axis,axis2,false,v2};
		}
	}
	chgts << newChanges;
	
	// remove duplicates
	QVector<uint> axesAlreadySeen;
	int nbChanges = chgts.size();
	for (int i=nbChanges-1; i>=0; --i)
	{
		JoystickChange &ch = chgts[i];
		if (ch.type == ControlType::Axis)
		{
			if (axesAlreadySeen.contains(ch.numButtonAxisPov)) {chgts.removeAt(i);}
			else {axesAlreadySeen << ch.numButtonAxisPov;}
		}
	}
	
	// end
	return chgts;
}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float AxesRotator::axisValue(uint axis) const
{
	int i = this->searchAxis(axis);
	if (i == -1) {return m_j->axisValue(axis);}
	
	uint axis1 = m_rotations[i].axis1;
	uint axis2 = m_rotations[i].axis2;
	float f1 = m_j->axisValue(axis1);
	float f2 = m_j->axisValue(axis2);
	float angle = piSur180 * m_rotations[i].rotAngleDegrees;
	
	float v = 0.0f;
	if (axis == axis1) {v = cos(angle) * f1 - sin(angle) * f2;}
	else {v = sin(angle) * f1 + cos(angle) * f2;}
	return v;
}

// SEARCH AXIS ////////////////////////////////////////////////////////////////
int AxesRotator::searchAxis(uint axis) const
{
	if (!m_rotatedAxes.contains(axis)) {return -1;}
	int n = m_rotations.size();
	for (int i=0; i<n; ++i)
	{
		if (axis == m_rotations[i].axis1 || axis == m_rotations[i].axis2) {return i;}
	}
	return -1;
}

