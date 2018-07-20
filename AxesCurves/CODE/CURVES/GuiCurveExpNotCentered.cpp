#include "GuiCurveExpNotCentered.h"
#include "Lim.h"

#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>


///////////////////////////////////////////////////////////////////////////////
// CURVE EXP NOT CENTERED
//  CONSTRUCTEUR ET DESTRUCTEUR
//  RUN
//  SETTINGS WIDGET
//
//  SLOT LEFT DZ MODIFIED
//  SLOT RIGHT DZ MODIFIED
//  SLOT CURVE PARAM MODIFIED
//  SLOT ZOOM MODIFIED
//
// CURVE EXP NOT CENTERED WIDGET
//  CONTRUCTEUR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GuiCurveExpNotCentered::GuiCurveExpNotCentered(float leftDZ, float rightDZ, float curve, float zoom) : AbstractAxisCurve()
{
	m_leftDZ = leftDZ;
	m_rightDZ = rightDZ;
	
	m_m = 0.02f * m_leftDZ - 1.0f;
	m_M = 1.0f - 0.02f * m_rightDZ;
	
	m_curveParam = curve;
	m_zoom = zoom;
	
	m_widget = new CurveExpNotCenteredWidget{};
	QObject::connect(m_widget,SIGNAL(leftDZModified(double)),this,SLOT(slotLeftDZModified(double)));
	QObject::connect(m_widget,SIGNAL(rightDZModified(double)),this,SLOT(slotRightDZModified(double)));
	QObject::connect(m_widget,SIGNAL(curveParamModified(double)),this,SLOT(slotCurveParamModified(double)));
	QObject::connect(m_widget,SIGNAL(zoomModified(double)),this,SLOT(slotZoomModified(double)));
}

GuiCurveExpNotCentered::~GuiCurveExpNotCentered()
{
	delete m_widget;
}

// RUN ////////////////////////////////////////////////////////////////////////
float GuiCurveExpNotCentered::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_M)
	{
		if (qAbs(m_curveParam) < 0.01f)
		{
			in = (in-m_m) / (m_M-m_m);
		}
		else
		{
			in = (exp(m_curveParam*(in-m_m)/(m_M-m_m))-1.0f) / (exp(m_curveParam)-1.0f);
		}
		in = 2.0f * in - 1.0f;
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(pow(1.41,m_zoom)*in,-1.0f,1.0f);
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* GuiCurveExpNotCentered::settingsWidget()
{
	return m_widget;
}





// SLOT LEFT DZ MODIFIED //////////////////////////////////////////////////////
void GuiCurveExpNotCentered::slotLeftDZModified(double ldz)
{
	m_leftDZ = ldz;
	m_m =  0.02f * m_leftDZ - 1.0f;
	emit curveModified();
}

// SLOT RIGHT DZ MODIFIED /////////////////////////////////////////////////////
void GuiCurveExpNotCentered::slotRightDZModified(double rdz)
{
	m_rightDZ = rdz;
	m_M = 1.0f - 0.02f * m_rightDZ;
	emit curveModified();
}

// SLOT CURVE PARAM MODIFIED //////////////////////////////////////////////////
void GuiCurveExpNotCentered::slotCurveParamModified(double curveParam)
{
	m_curveParam = curveParam;
	emit curveModified();
}

// SLOT ZOOM MODIFIED /////////////////////////////////////////////////////////
void GuiCurveExpNotCentered::slotZoomModified(double zoom)
{
	m_zoom = zoom;
	emit curveModified();
}





// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurveExpNotCenteredWidget::CurveExpNotCenteredWidget() : QGroupBox{"Exponential curve (centered): parameters"}
{
	layout = new QGridLayout(this);
	this->setLayout(layout);
	
	labelLDZ   = new QLabel("Left dead-zone:",this);
	labelRDZ   = new QLabel("Right dead-zone:",this);
	labelCurve = new QLabel("Curve:",this);
	labelZoom  = new QLabel("Zoom:",this);
	
	boxLDZ   = new QDoubleSpinBox(this);
	boxRDZ   = new QDoubleSpinBox(this);
	boxCurve = new QDoubleSpinBox(this);
	boxZoom  = new QDoubleSpinBox(this);
	boxLDZ->setRange(0.0,20.0);
	boxRDZ->setRange(0.0,20.0);
	boxCurve->setRange(-10.0,10.0);
	boxZoom->setRange(-10.0,10.0);
	boxLDZ->setDecimals(1);
	boxRDZ->setDecimals(1);
	boxCurve->setDecimals(1);
	boxZoom->setDecimals(1);
	boxLDZ->setSingleStep(0.5);
	boxRDZ->setSingleStep(0.5);
	boxCurve->setSingleStep(0.1);
	boxZoom->setSingleStep(0.1);
	boxLDZ->setValue(0.0);
	boxRDZ->setValue(0.0);
	boxCurve->setValue(0.0);
	boxZoom->setValue(0.0);
	boxLDZ->setSuffix(" %");
	boxRDZ->setSuffix(" %");
	
	layout->addWidget(labelLDZ,0,0,1,1);
	layout->addWidget(labelRDZ,1,0,1,1);
	layout->addWidget(labelCurve,2,0,1,1);
	layout->addWidget(labelZoom,3,0,1,1);
	layout->addWidget(boxLDZ,0,1,1,1);
	layout->addWidget(boxRDZ,1,1,1,1);
	layout->addWidget(boxCurve,2,1,1,1);
	layout->addWidget(boxZoom,3,1,1,1);
	layout->addItem(new QSpacerItem{0,0,QSizePolicy::Expanding,QSizePolicy::Minimum},0,2,1,1);
	
	QObject::connect(boxLDZ,SIGNAL(valueChanged(double)),this,SIGNAL(leftDZModified(double)));
	QObject::connect(boxRDZ,SIGNAL(valueChanged(double)),this,SIGNAL(rightDZModified(double)));
	QObject::connect(boxCurve,SIGNAL(valueChanged(double)),this,SIGNAL(curveParamModified(double)));
	QObject::connect(boxZoom,SIGNAL(valueChanged(double)),this,SIGNAL(zoomModified(double)));
}

