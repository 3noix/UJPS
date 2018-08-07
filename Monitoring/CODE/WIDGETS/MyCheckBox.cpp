#include "MyCheckBox.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  SLOT THE SLOT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MyCheckBox::MyCheckBox(uint axis, QWidget *parent) : QCheckBox{parent}
{
	m_axis = axis;
	QObject::connect(this,&QCheckBox::stateChanged,this,&MyCheckBox::slotTheSlot);
}

// SLOT THE SLOT //////////////////////////////////////////////////////////////
void MyCheckBox::slotTheSlot(int checkState)
{
	emit axisDisplayChanged(m_axis,checkState==Qt::Checked);
}

