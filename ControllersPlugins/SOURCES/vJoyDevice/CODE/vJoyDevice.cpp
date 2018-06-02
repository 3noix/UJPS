#include "vJoyDevice.h"
#include "qgamecontroller.h"
#include "Lim.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  DESCRIPTION
//
//  BUTTON NAME
//  BUTTON NAMES
//
//  AXIS NAME
//  AXES NAMES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
vJoyDevice::vJoyDevice(QGameController *c) : RealJoystick{c}
{
	m_axesNames << "X" << "Y" << "Z" << "ROTX" << "ROTY" << "ROTZ" << "SLIDER0" << "SLIDER1";
}

// DESCRIPTION ////////////////////////////////////////////////////////////////
QString vJoyDevice::description() const
{
	return vJoyDevice_::Description;
}





// BUTTON NAME ////////////////////////////////////////////////////////////////
QString vJoyDevice::buttonName(uint button) const
{
	return "DX" + QString::number(button+1);
}

// BUTTON NAMES ///////////////////////////////////////////////////////////////
QStringList vJoyDevice::buttonsNames() const
{
	QStringList list;
	for (uint i=0; i<this->buttonsCount(); ++i) {list << "DX" + QString::number(i+1);}
	return list;
}




// AXIS NAME //////////////////////////////////////////////////////////////////
QString vJoyDevice::axisName(uint axis) const
{
	if (axis < this->axesCount())
		return m_axesNames[axis];
	else
		return QString();
}

// AXES NAMES /////////////////////////////////////////////////////////////////
QStringList vJoyDevice::axesNames() const
{
	return m_axesNames;
}


