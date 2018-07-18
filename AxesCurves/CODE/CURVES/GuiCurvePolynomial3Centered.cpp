#include "GuiCurvePolynomial3Centered.h"
#include "Lim.h"

#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>


///////////////////////////////////////////////////////////////////////////////
// CURVE POLYNOMIAL 3 CENTERED
//  CONSTRUCTEUR ET DESTRUCTEUR
//  RUN
//  SETTINGS WIDGET
//
//  SLOT LEFT DZ MODIFIED
//  SLOT CENTER DZ MODIFIED
//  SLOT RIGHT DZ MODIFIED
//  SLOT CURVE PARAM MODIFIED
//
// CURVE POLYNOMIAL 3 CENTERED WIDGET
//  CONTRUCTEUR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GuiCurvePolynomial3Centered::GuiCurvePolynomial3Centered(float leftDZ, float centerDZ, float rightDZ, float curve) : AbstractAxisCurve()
{
	m_leftDZ = leftDZ;
	m_centerDZ = centerDZ;
	m_rightDZ = rightDZ;
	
	m_m = 0.02f * m_leftDZ - 1.0f;
	m_M = 1.0f - 0.02f * m_rightDZ;
	m_cM = 0.01f * m_centerDZ;
	m_cm = -m_cM;
	
	m_curveParam = curve;
	
	m_widget = new CurvePolynomial3CenteredWidget{};
	QObject::connect(m_widget,SIGNAL(leftDZModified(double)),this,SLOT(slotLeftDZModified(double)));
	QObject::connect(m_widget,SIGNAL(centerDZModified(double)),this,SLOT(slotCenterDZModified(double)));
	QObject::connect(m_widget,SIGNAL(rightDZModified(double)),this,SLOT(slotRightDZModified(double)));
	QObject::connect(m_widget,SIGNAL(curveParamModified(double)),this,SLOT(slotCurveParamModified(double)));
}

GuiCurvePolynomial3Centered::~GuiCurvePolynomial3Centered()
{
	delete m_widget;
}

// RUN ////////////////////////////////////////////////////////////////////////
float GuiCurvePolynomial3Centered::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_cm)
	{
		in = (in-m_cm)/(m_cm-m_m);
		in = m_curveParam * (in*in*in) + (1-m_curveParam) * in;
	}
	else if (in < m_cM)
	{
		in = 0.0f;
	}
	else if (in < m_M)
	{
		in = (in-m_cM)/(m_M-m_cM);
		in = m_curveParam * (in*in*in) + (1-m_curveParam) * in;
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(in,-1.0f,1.0f);
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* GuiCurvePolynomial3Centered::settingsWidget()
{
	return m_widget;
}





// SLOT LEFT DZ MODIFIED //////////////////////////////////////////////////////
void GuiCurvePolynomial3Centered::slotLeftDZModified(double ldz)
{
	m_leftDZ = ldz;
	m_m =  0.02f * m_leftDZ - 1.0f;
	emit curveModified();
}

// SLOT CENTER DZ MODIFIED ////////////////////////////////////////////////////
void GuiCurvePolynomial3Centered::slotCenterDZModified(double cdz)
{
	m_centerDZ = 0.01f * cdz;
	m_cM = m_centerDZ;
	m_cm = -m_cM;
	emit curveModified();
}

// SLOT RIGHT DZ MODIFIED /////////////////////////////////////////////////////
void GuiCurvePolynomial3Centered::slotRightDZModified(double rdz)
{
	m_rightDZ = rdz;
	m_M = 1.0f - 0.02f * m_rightDZ;
	emit curveModified();
}

// SLOT CURVE PARAM MODIFIED //////////////////////////////////////////////////
void GuiCurvePolynomial3Centered::slotCurveParamModified(double curveParam)
{
	m_curveParam = curveParam;
	emit curveModified();
}





// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurvePolynomial3CenteredWidget::CurvePolynomial3CenteredWidget() : QGroupBox{"Polynomial 3rd degree curve (centered): parameters"}
{
	layout = new QGridLayout(this);
	this->setLayout(layout);
	
	labelLDZ   = new QLabel("Left dead-zone:",this);
	labelCDZ   = new QLabel("Center dead-zone:",this);
	labelRDZ   = new QLabel("Right dead-zone:",this);
	labelCurve = new QLabel("Curve:",this);
	
	boxLDZ   = new QDoubleSpinBox(this);
	boxCDZ   = new QDoubleSpinBox(this);
	boxRDZ   = new QDoubleSpinBox(this);
	boxCurve = new QDoubleSpinBox(this);
	boxLDZ->setRange(0.0,20.0);
	boxCDZ->setRange(0.0,20.0);
	boxRDZ->setRange(0.0,20.0);
	boxCurve->setRange(-0.5,1.0);
	boxLDZ->setDecimals(1);
	boxCDZ->setDecimals(1);
	boxRDZ->setDecimals(1);
	boxCurve->setDecimals(2);
	boxLDZ->setSingleStep(0.5);
	boxCDZ->setSingleStep(0.5);
	boxRDZ->setSingleStep(0.5);
	boxCurve->setSingleStep(0.05);
	boxLDZ->setValue(0.0);
	boxCDZ->setValue(0.0);
	boxRDZ->setValue(0.0);
	boxCurve->setValue(0.0);
	boxLDZ->setSuffix(" %");
	boxCDZ->setSuffix(" %");
	boxRDZ->setSuffix(" %");
	
	layout->addWidget(labelLDZ,0,0,1,1);
	layout->addWidget(labelCDZ,1,0,1,1);
	layout->addWidget(labelRDZ,2,0,1,1);
	layout->addWidget(labelCurve,3,0,1,1);
	layout->addWidget(boxLDZ,0,1,1,1);
	layout->addWidget(boxCDZ,1,1,1,1);
	layout->addWidget(boxRDZ,2,1,1,1);
	layout->addWidget(boxCurve,3,1,1,1);
	layout->addItem(new QSpacerItem{0,0,QSizePolicy::Expanding,QSizePolicy::Minimum},0,2,1,1);
	
	QObject::connect(boxLDZ,SIGNAL(valueChanged(double)),this,SIGNAL(leftDZModified(double)));
	QObject::connect(boxCDZ,SIGNAL(valueChanged(double)),this,SIGNAL(centerDZModified(double)));
	QObject::connect(boxRDZ,SIGNAL(valueChanged(double)),this,SIGNAL(rightDZModified(double)));
	QObject::connect(boxCurve,SIGNAL(valueChanged(double)),this,SIGNAL(curveParamModified(double)));
}

