#include "PovWidgetDecorated.h"
#include "PovWidget.h"
#include <QVBoxLayout>
#include <QLabel>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  ANGLE
//  SLOT SET ANGLE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
PovWidgetDecorated::PovWidgetDecorated(const QString &name, QWidget *parent) : QWidget(parent)
{
	layout = new QVBoxLayout{this};
	layout->setContentsMargins(0,0,0,0);
	this->setLayout(layout);
	
	p = new PovWidget{this};
	label = new QLabel{name,this};
	label->setAlignment(Qt::AlignCenter);
	layout->addWidget(p);
	layout->addWidget(label);
	layout->addStretch();
}

// ANGLE //////////////////////////////////////////////////////////////////////
float PovWidgetDecorated::angle() const
{
	return p->angle();
}

// SLOT SET ANGLE /////////////////////////////////////////////////////////////
void PovWidgetDecorated::slotSetAngle(float angle)
{
	p->slotSetAngle(angle);
}

