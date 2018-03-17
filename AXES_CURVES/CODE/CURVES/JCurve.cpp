#include "JCurve.h"
#include "Lim.h"

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
JCurve::JCurve(float zoom) : AbstractAxisCurve()
{
	m_zoom = zoom;
	m_widget = new JCurveWidget{};
	QObject::connect(m_widget,SIGNAL(zoomModified(double)),this,SLOT(slotZoomModified(double)));
}

JCurve::~JCurve()
{
	delete m_widget;
}

// RUN ////////////////////////////////////////////////////////////////////////
float JCurve::run(float in)
{
	return (-m_zoom*in*in + in + m_zoom*in);
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* JCurve::settingsWidget()
{
	return m_widget;
}

// SLOT ZOOM MODIFIED /////////////////////////////////////////////////////////
void JCurve::slotZoomModified(double zoom)
{
	m_zoom = zoom;
	emit curveModified();
}




// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
JCurveWidget::JCurveWidget() : QGroupBox{"J curve settings"}
{
	layout = new QHBoxLayout(this);
	this->setLayout(layout);
	
	labelZoom = new QLabel("Zoom:",this);
	boxZoom = new QDoubleSpinBox(this);
	boxZoom->setRange(-10.0,10.0);
	boxZoom->setDecimals(1);
	boxZoom->setSingleStep(0.1);
	boxZoom->setValue(0.0);
	
	layout->addWidget(labelZoom);
	layout->addWidget(boxZoom);
	layout->addStretch();
	
	QObject::connect(boxZoom,SIGNAL(valueChanged(double)),this,SIGNAL(zoomModified(double)));
}


