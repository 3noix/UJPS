#include "AxesWidget.h"
#include <QGridLayout>
#include <QSlider>
#include <QLabel>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  VALUE
//  SLOT SET VALUE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AxesWidget::AxesWidget(const QStringList &names, QWidget *parent) : QGroupBox("Axes",parent)
{
	layout = new QGridLayout{this};
	this->setLayout(layout);
	
	int i = 0;
	for (const QString &name : names)
	{
		QLabel *label1 = new QLabel{name,this};
		label1->setMinimumWidth(20);
		
		QSlider *slider = new QSlider{Qt::Horizontal,this};
		slider->setEnabled(false);
		slider->setTickPosition(QSlider::TicksBothSides);
		slider->setTickInterval(1000/5);
		slider->setMinimum(-1000);
		slider->setMaximum(1000);
		slider->setValue(0);
		slider->setMinimumWidth(150);
		
		QLabel *label2 = new QLabel("0",this);
		label2->setFixedWidth(50);
		label2->setAlignment(Qt::AlignCenter);
		
		layout->addWidget(label1,i,0,1,1);
		layout->addWidget(slider,i,1,1,1);
		layout->addWidget(label2,i,2,1,1);
		
		m_sliders << slider;
		m_labels2 << label2;
		++i;
	}
}

// VALUE //////////////////////////////////////////////////////////////////////
float AxesWidget::value(int i) const
{
	return m_sliders[i]->value();
}

// SLOT SET VALUE /////////////////////////////////////////////////////////////
void AxesWidget::slotSetValue(int i, float value)
{
	m_sliders[i]->setValue(qRound(1000.0f*value));
	m_labels2[i]->setText(QString::number(qRound(1000.0f*value)));
}

