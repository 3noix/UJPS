#include "SCurve.h"
#include "Lim.h"

#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>


///////////////////////////////////////////////////////////////////////////////
// SCURVE
//  CONSTRUCTEUR ET DESTRUCTEUR
//  RUN
//  SETTINGS WIDGET
//
//  SLOT LEFT DZ MODIFIED
//  SLOT CENTER DZ MODIFIED
//  SLOT RIGHT DZ MODIFIED
//  SLOT CURVE PARAM MODIFIED
//  SLOT ZOOM MODIFIED
//
// SCURVE WIDGET
//  CONTRUCTEUR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
SCurve::SCurve(float leftDZ, float centerDZ, float rightDZ, float curve, float zoom) : AbstractAxisCurve()
{
	m_leftDZ = leftDZ;
	m_centerDZ = centerDZ;
	m_rightDZ = rightDZ;
	
	m_m = m_leftDZ + m_leftDZ - 1;
	m_M = 1 - m_rightDZ - m_rightDZ;
	m_cM = m_centerDZ;
	m_cm = -m_cM;
	
	m_curveParam = curve;
	m_zoom = zoom;
	
	m_widget = new SCurveWidget{};
	QObject::connect(m_widget,SIGNAL(leftDZModified(double)),this,SLOT(slotLeftDZModified(double)));
	QObject::connect(m_widget,SIGNAL(centerDZModified(double)),this,SLOT(slotCenterDZModified(double)));
	QObject::connect(m_widget,SIGNAL(rightDZModified(double)),this,SLOT(slotRightDZModified(double)));
	QObject::connect(m_widget,SIGNAL(curveParamModified(double)),this,SLOT(slotCurveParamModified(double)));
	QObject::connect(m_widget,SIGNAL(zoomModified(double)),this,SLOT(slotZoomModified(double)));
}

SCurve::~SCurve()
{
	delete m_widget;
}

// RUN ////////////////////////////////////////////////////////////////////////
float SCurve::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_cm)
	{
		if (qAbs(m_curveParam) < 0.01f)
			in = (in-m_cm) / (m_cm-m_m);
		else
			in = (1.0f-exp((m_cm-in)*m_curveParam)) / (exp((m_cm-m_m)*m_curveParam)-1.0f);
	}
	else if (in < m_cM)
	{
		in = 0.0f;
	}
	else if (in < m_M)
	{
		if (qAbs(m_curveParam) < 0.01f)
		{
			in = (in-m_cM) / (m_M-m_cM);
		}
		else
		{
			in = (exp((in-m_cM)*m_curveParam)-1.0f) / (exp((m_M-m_cM)*m_curveParam)-1.0f);
		}
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(pow(1.41,m_zoom)*in,-1.0f,1.0f);
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* SCurve::settingsWidget()
{
	return m_widget;
}





// SLOT LEFT DZ MODIFIED //////////////////////////////////////////////////////
void SCurve::slotLeftDZModified(double ldz)
{
	m_leftDZ = ldz;
	m_m = m_leftDZ + m_leftDZ - 1;
	emit curveModified();
}

// SLOT CENTER DZ MODIFIED ////////////////////////////////////////////////////
void SCurve::slotCenterDZModified(double cdz)
{
	m_centerDZ = cdz;
	m_cM = m_centerDZ;
	m_cm = -m_cM;
	emit curveModified();
}

// SLOT RIGHT DZ MODIFIED /////////////////////////////////////////////////////
void SCurve::slotRightDZModified(double rdz)
{
	m_rightDZ = rdz;
	m_M = 1 - m_rightDZ - m_rightDZ;
	emit curveModified();
}

// SLOT CURVE PARAM MODIFIED //////////////////////////////////////////////////
void SCurve::slotCurveParamModified(double curveParam)
{
	m_curveParam = curveParam;
	emit curveModified();
}

// SLOT ZOOM MODIFIED /////////////////////////////////////////////////////////
void SCurve::slotZoomModified(double zoom)
{
	m_zoom = zoom;
	emit curveModified();
}





// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
SCurveWidget::SCurveWidget() : QGroupBox{"S curve settings"}
{
	layout = new QGridLayout(this);
	this->setLayout(layout);
	
	labelLDZ   = new QLabel("Left dead-zone:",this);
	labelCDZ   = new QLabel("Center dead-zone:",this);
	labelRDZ   = new QLabel("Right dead-zone:",this);
	labelCurve = new QLabel("Curve:",this);
	labelZoom  = new QLabel("Zoom:",this);
	
	
	boxLDZ   = new QDoubleSpinBox(this);
	boxCDZ   = new QDoubleSpinBox(this);
	boxRDZ   = new QDoubleSpinBox(this);
	boxCurve = new QDoubleSpinBox(this);
	boxZoom  = new QDoubleSpinBox(this);
	boxLDZ->setRange(0.0,0.2);
	boxCDZ->setRange(0.0,0.2);
	boxRDZ->setRange(0.0,0.2);
	boxCurve->setRange(-10.0,10.0);
	boxZoom->setRange(-10.0,10.0);
	boxLDZ->setDecimals(3);
	boxCDZ->setDecimals(3);
	boxRDZ->setDecimals(3);
	boxCurve->setDecimals(1);
	boxZoom->setDecimals(1);
	boxLDZ->setSingleStep(0.005);
	boxCDZ->setSingleStep(0.005);
	boxRDZ->setSingleStep(0.005);
	boxCurve->setSingleStep(0.1);
	boxZoom->setSingleStep(0.1);
	boxLDZ->setValue(0.0);
	boxCDZ->setValue(0.0);
	boxRDZ->setValue(0.0);
	boxCurve->setValue(0.0);
	boxZoom->setValue(0.0);
	
	layout->addWidget(labelLDZ,0,0,1,1);
	layout->addWidget(labelCDZ,1,0,1,1);
	layout->addWidget(labelRDZ,2,0,1,1);
	layout->addWidget(labelCurve,3,0,1,1);
	layout->addWidget(labelZoom,4,0,1,1);
	layout->addWidget(boxLDZ,0,1,1,1);
	layout->addWidget(boxCDZ,1,1,1,1);
	layout->addWidget(boxRDZ,2,1,1,1);
	layout->addWidget(boxCurve,3,1,1,1);
	layout->addWidget(boxZoom,4,1,1,1);
	layout->addItem(new QSpacerItem{0,0,QSizePolicy::Expanding,QSizePolicy::Minimum},0,2,1,1);
	
	QObject::connect(boxLDZ,SIGNAL(valueChanged(double)),this,SIGNAL(leftDZModified(double)));
	QObject::connect(boxCDZ,SIGNAL(valueChanged(double)),this,SIGNAL(centerDZModified(double)));
	QObject::connect(boxRDZ,SIGNAL(valueChanged(double)),this,SIGNAL(rightDZModified(double)));
	QObject::connect(boxCurve,SIGNAL(valueChanged(double)),this,SIGNAL(curveParamModified(double)));
	QObject::connect(boxZoom,SIGNAL(valueChanged(double)),this,SIGNAL(zoomModified(double)));
}

