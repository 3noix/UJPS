#include "GuiCurvePolynomial2.h"
#include "Other/Lim.h"

#include <math.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>


///////////////////////////////////////////////////////////////////////////////
// JCURVE
//  CONSTRUCTEUR ET DESTRUCTEUR
//  RUN
//  SETTINGS WIDGET
//  SLOT ZOOM MODIFIED
//
// JCURVE WIDGET
//  CONTRUCTEUR
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GuiCurvePolynomial2::GuiCurvePolynomial2(float zoom) : AbstractAxisCurve{}
{
	m_zoom = zoom;
	m_widget = new CurvePolynomial2Widget{};
	QObject::connect(m_widget, SIGNAL(zoomModified(double)), this, SLOT(slotZoomModified(double)));
}

GuiCurvePolynomial2::~GuiCurvePolynomial2()
{
	delete m_widget;
}

// RUN ////////////////////////////////////////////////////////////////////////
float GuiCurvePolynomial2::run(float in)
{
	return (-m_zoom*in*in + in + m_zoom*in);
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* GuiCurvePolynomial2::settingsWidget()
{
	return m_widget;
}

// SLOT ZOOM MODIFIED /////////////////////////////////////////////////////////
void GuiCurvePolynomial2::slotZoomModified(double zoom)
{
	m_zoom = zoom;
	emit curveModified();
}






// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurvePolynomial2Widget::CurvePolynomial2Widget() : QGroupBox{"Polynomial 2nd degree: parameters"}
{
	layout = new QHBoxLayout{this};
	this->setLayout(layout);
	
	labelZoom = new QLabel{"Zoom:",this};
	boxZoom = new QDoubleSpinBox{this};
	boxZoom->setRange(-10.0,10.0);
	boxZoom->setDecimals(1);
	boxZoom->setSingleStep(0.1);
	boxZoom->setValue(0.0);
	
	layout->addWidget(labelZoom);
	layout->addWidget(boxZoom);
	layout->addStretch();
	
	QObject::connect(boxZoom, SIGNAL(valueChanged(double)), this, SIGNAL(zoomModified(double)));
}

