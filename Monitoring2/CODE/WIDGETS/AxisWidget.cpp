#include "AxisWidget.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  VALUE
//  SLOT SET VALUE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AxisWidget::AxisWidget(const QString &name, QWidget *parent) : QWidget(parent)
{
	layout = new QHBoxLayout{this};
	layout->setContentsMargins(0,0,0,0);
	this->setLayout(layout);
	
	label1 = new QLabel{name,this};
	label1->setMinimumWidth(20);
	
	slider = new QSlider{Qt::Horizontal,this};
	slider->setEnabled(false);
	slider->setTickPosition(QSlider::TicksBothSides);
	slider->setTickInterval(1000/5);
	slider->setMinimum(-1000);
	slider->setMaximum(1000);
	slider->setValue(0);
	slider->setMinimumWidth(150);
	
	label2 = new QLabel("0",this);
	label2->setFixedWidth(50);
	label2->setAlignment(Qt::AlignCenter);
	
	layout->addWidget(label1);
	layout->addWidget(slider);
	layout->addWidget(label2);
}

// VALUE //////////////////////////////////////////////////////////////////////
float AxisWidget::value() const
{
	return m_value;
}

// SLOT SET VALUE /////////////////////////////////////////////////////////////
void AxisWidget::slotSetValue(float value)
{
	slider->setValue(qRound(1000.0f*value));
	label2->setText(QString::number(qRound(1000.0f*value)));
}

