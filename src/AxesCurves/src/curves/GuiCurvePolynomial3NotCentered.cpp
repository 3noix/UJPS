#include "GuiCurvePolynomial3NotCentered.h"
#include "Other/Lim.h"

#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>


///////////////////////////////////////////////////////////////////////////////
// CURVE POLYNOMIAL 3 NOT CENTERED
//  CONSTRUCTEUR ET DESTRUCTEUR
//  RUN
//  SETTINGS WIDGET
//
//  SLOT LEFT DZ MODIFIED
//  SLOT RIGHT DZ MODIFIED
//  SLOT CURVE PARAM MODIFIED
//
// CURVE POLYNOMIAL 3 NOT CENTERED WIDGET
//  CONTRUCTEUR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GuiCurvePolynomial3NotCentered::GuiCurvePolynomial3NotCentered(float leftDZ, float rightDZ, float curve) : AbstractAxisCurve{}
{
	m_leftDZ = leftDZ;
	m_rightDZ = rightDZ;
	
	m_m = 0.02f * m_leftDZ - 1.0f;
	m_M = 1.0f - 0.02f * m_rightDZ;
	
	m_curveParam = curve;
	
	m_widget = new CurvePolynomial3NotCenteredWidget{};
	QObject::connect(m_widget, SIGNAL(leftDZModified(double)),     this, SLOT(slotLeftDZModified(double)));
	QObject::connect(m_widget, SIGNAL(rightDZModified(double)),    this, SLOT(slotRightDZModified(double)));
	QObject::connect(m_widget, SIGNAL(curveParamModified(double)), this, SLOT(slotCurveParamModified(double)));
}

GuiCurvePolynomial3NotCentered::~GuiCurvePolynomial3NotCentered()
{
	delete m_widget;
}

// RUN ////////////////////////////////////////////////////////////////////////
float GuiCurvePolynomial3NotCentered::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_M)
	{
		in = (in-m_m) / (m_M-m_m);
		in = m_curveParam * (in*in*in) + (1-m_curveParam) * in;
		in = 2.0f * in - 1.0f;
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(in,-1.0f,1.0f);
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* GuiCurvePolynomial3NotCentered::settingsWidget()
{
	return m_widget;
}






// SLOT LEFT DZ MODIFIED //////////////////////////////////////////////////////
void GuiCurvePolynomial3NotCentered::slotLeftDZModified(double ldz)
{
	m_leftDZ = ldz;
	m_m =  0.02f * m_leftDZ - 1.0f;
	emit curveModified();
}

// SLOT RIGHT DZ MODIFIED /////////////////////////////////////////////////////
void GuiCurvePolynomial3NotCentered::slotRightDZModified(double rdz)
{
	m_rightDZ = rdz;
	m_M = 1.0f - 0.02f * m_rightDZ;
	emit curveModified();
}

// SLOT CURVE PARAM MODIFIED //////////////////////////////////////////////////
void GuiCurvePolynomial3NotCentered::slotCurveParamModified(double curveParam)
{
	m_curveParam = curveParam;
	emit curveModified();
}






// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurvePolynomial3NotCenteredWidget::CurvePolynomial3NotCenteredWidget() : QGroupBox{"Exponential curve (centered): parameters"}
{
	layout = new QGridLayout{this};
	this->setLayout(layout);
	
	labelLDZ   = new QLabel{"Left dead-zone:",this};
	labelRDZ   = new QLabel{"Right dead-zone:",this};
	labelCurve = new QLabel{"Curve:",this};
	
	boxLDZ   = new QDoubleSpinBox{this};
	boxRDZ   = new QDoubleSpinBox{this};
	boxCurve = new QDoubleSpinBox{this};
	boxLDZ->setRange(0.0,20.0);
	boxRDZ->setRange(0.0,20.0);
	boxCurve->setRange(-0.5,1.0);
	boxLDZ->setDecimals(1);
	boxRDZ->setDecimals(1);
	boxCurve->setDecimals(2);
	boxLDZ->setSingleStep(0.5);
	boxRDZ->setSingleStep(0.5);
	boxCurve->setSingleStep(0.05);
	boxLDZ->setValue(0.0);
	boxRDZ->setValue(0.0);
	boxCurve->setValue(0.0);
	boxLDZ->setSuffix(" %");
	boxRDZ->setSuffix(" %");
	
	layout->addWidget(labelLDZ,0,0,1,1);
	layout->addWidget(labelRDZ,1,0,1,1);
	layout->addWidget(labelCurve,2,0,1,1);
	layout->addWidget(boxLDZ,0,1,1,1);
	layout->addWidget(boxRDZ,1,1,1,1);
	layout->addWidget(boxCurve,2,1,1,1);
	layout->addItem(new QSpacerItem{0,0,QSizePolicy::Expanding,QSizePolicy::Minimum},0,2,1,1);
	
	QObject::connect(boxLDZ,   SIGNAL(valueChanged(double)), this, SIGNAL(leftDZModified(double)));
	QObject::connect(boxRDZ,   SIGNAL(valueChanged(double)), this, SIGNAL(rightDZModified(double)));
	QObject::connect(boxCurve, SIGNAL(valueChanged(double)), this, SIGNAL(curveParamModified(double)));
}

