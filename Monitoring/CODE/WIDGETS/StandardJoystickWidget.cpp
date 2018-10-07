#include "StandardJoystickWidget.h"
#include "AbstractRealJoystick.h"
#include "AxesWidget.h"
#include "ButtonWidget.h"
#include "PovWidgetDecorated.h"
#include "MyChartWidget.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  SETUP WIDGET
//
//  INIT STATE
//  SLOT RUN ONE LOOP
//  JOYSTICK BUTTON STATE CHANGED
//  JOYSTICK AXIS VALUE CHANGED
//  JOYSTICK POV ANGLE CHANGED
//
//  SLOT UPDATE TEMPO CURVES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
StandardJoystickWidget::StandardJoystickWidget(AbstractRealJoystick *j, bool own, QWidget *parent) : QWidget{parent}
{
	Q_ASSERT(j);
	m_joystick = j;
	m_own = own;
	compteur = -1;
	
	this->setupWidget();
	this->initState();
	
	m_timer = new QTimer{this};
	m_timer->setInterval(15);
	
	QObject::connect(boxAxes, SIGNAL(axisDisplayChanged(uint,bool)), this, SLOT(slotUpdateTempoCurves(uint,bool)));
	QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(slotRunOneLoop()));
	m_timer->start();
}

StandardJoystickWidget::~StandardJoystickWidget()
{
	//delete layout2;
	//delete layout3;
	//delete layout4;
	
	if (m_own && m_joystick)
	{
		delete m_joystick;
		m_joystick = nullptr;
	}
}






// SETUP WIDGET ///////////////////////////////////////////////////////////////
void StandardJoystickWidget::setupWidget()
{
	layout1 = new QVBoxLayout{this};
	this->setLayout(layout1);
	layout2 = new QHBoxLayout{};
	layout3 = new QVBoxLayout{};
	
	// axes
	QStringList names;
	for (uint i=0; i<m_joystick->axesCount(); ++i) {names << m_joystick->axisName(i);}
	boxAxes = new AxesWidget{names,this};
	layout3->addWidget(boxAxes);
	
	// pov
	layout4 = new QHBoxLayout{};
	for (uint i=0; i<m_joystick->povsCount(); ++i)
	{
		PovWidgetDecorated *p = new PovWidgetDecorated{m_joystick->povName(i),this};
		layout4->addWidget(p);
		povWidgets << p;
	}
	layout4->addStretch();
	layout3->addLayout(layout4);
	layout2->addLayout(layout3);
	
	// buttons
	boxButtons = new QGroupBox{"Buttons",this};
	buttonsLayout = new QGridLayout{boxButtons};
	buttonsLayout->setVerticalSpacing(5);
	boxButtons->setLayout(buttonsLayout);
	int nbButtons = m_joystick->buttonsCount();
	for (int i=0; i<qMax(32,nbButtons); ++i)
	{
		ButtonWidget *b = new ButtonWidget{i+1,i<nbButtons,this};
		if (i < nbButtons) {b->setToolTip(m_joystick->buttonName(i));}
		buttonsLayout->addWidget(b,i/8,i%8,1,1);
		buttonsWidgets << b;
	}
	layout2->addWidget(boxButtons);
	layout1->addLayout(layout2);
	
	// temporal chart
	tempoChart = new MyChartWidget{1+1000/ratioTempoChart,15*ratioTempoChart,this};
	tempoChart->setMinimumHeight(200);
	tempoChart->setSizePolicy(QSizePolicy{QSizePolicy::Preferred,QSizePolicy::MinimumExpanding});
	layout1->addWidget(tempoChart);
	tempoChart->hide();
}






// INIT STATE /////////////////////////////////////////////////////////////////
void StandardJoystickWidget::initState()
{
	for (uint i=0; i<m_joystick->buttonsCount(); ++i)
		this->joystickButtonStateChanged(i,m_joystick->buttonPressed(i));
	
	for (uint i=0; i<m_joystick->axesCount(); ++i)
		this->joystickAxisValueChanged(i,m_joystick->axisValue(i));
	
	for (uint i=0; i<m_joystick->povsCount(); ++i)
		this->joystickPovAngleChanged(i,m_joystick->povValue(i));
}

// SLOT RUN ONE LOOP //////////////////////////////////////////////////////////
void StandardJoystickWidget::slotRunOneLoop()
{
	// read controller state and recover changes
	m_joystick->readGameController();
	QVector<JoystickChange> changes = m_joystick->changes();
	
	// update widgets to reflect changes
	for (const JoystickChange &ch : changes)
	{
		if (ch.type == ControlType::Button)
			this->joystickButtonStateChanged(ch.numButtonAxisPov,ch.bButtonPressed);
		else if (ch.type == ControlType::Axis)
			this->joystickAxisValueChanged(ch.numButtonAxisPov,ch.axisOrPovValue);
		else if (ch.type == ControlType::Pov)
			this->joystickPovAngleChanged(ch.numButtonAxisPov,ch.axisOrPovValue);
	}
	
	// feed tempo chart (even if no change)
	++compteur;
	if (compteur % ratioTempoChart == 0)
	{
		QVector<uint> axes = boxAxes->axesToDisplay();
		for (uint axis : axes) {tempoChart->slotPushValue(axis,m_joystick->axisValue(axis));}
	}
}

// JOYSTICK BUTTON STATE CHANGED //////////////////////////////////////////////
void StandardJoystickWidget::joystickButtonStateChanged(uint button, bool bPressed)
{
	buttonsWidgets[button]->slotSetChecked(bPressed);
}

// JOYSTICK AXIS VALUE CHANGED ////////////////////////////////////////////////
void StandardJoystickWidget::joystickAxisValueChanged(uint axis, float value)
{
	boxAxes->slotSetValue(axis,value);
}

// JOYSTICK POV ANGLE CHANGED /////////////////////////////////////////////////
void StandardJoystickWidget::joystickPovAngleChanged(uint pov, float value)
{
	povWidgets[pov]->slotSetAngle(value);
}






// SLOT UPDATE TEMPO CURVES ///////////////////////////////////////////////////
void StandardJoystickWidget::slotUpdateTempoCurves(uint axis, bool bDisplay)
{
	QVector<uint> axes = boxAxes->axesToDisplay();
	
	if (bDisplay) {tempoChart->slotAddCurve(axis,m_joystick->axisName(axis));}
	else {tempoChart->slotRemoveCurve(axis);}
	
	if (axes.size() == 0) {tempoChart->hide();}
	else {tempoChart->show();}
}

