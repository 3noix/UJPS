#include "StandardJoystickWidgetRaw.h"
#include "GameController.h"
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
//  SLOT JOYSTICK BUTTON STATE CHANGED
//  SLOT JOYSTICK AXIS VALUE CHANGED
//  SLOT JOYSTICK POV ANGLE CHANGED
//
//  SLOT UPDATE TEMPO CURVES
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
StandardJoystickWidgetRaw::StandardJoystickWidgetRaw(GameController *j, bool own, QWidget *parent) : QWidget{parent}
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
	QObject::connect(m_timer, &QTimer::timeout, this, &StandardJoystickWidgetRaw::slotRunOneLoop);
	m_timer->start();
	
	QObject::connect(j, SIGNAL(gameControllerAxisEvent(GameControllerAxisEvent)),     this, SLOT(slotJoystickAxisValueChanged(GameControllerAxisEvent)));
	QObject::connect(j, SIGNAL(gameControllerButtonEvent(GameControllerButtonEvent)), this, SLOT(slotJoystickButtonStateChanged(GameControllerButtonEvent)));
	QObject::connect(j, SIGNAL(gameControllerPovEvent(GameControllerPovEvent)),       this, SLOT(slotJoystickPovAngleChanged(GameControllerPovEvent)));
}

StandardJoystickWidgetRaw::~StandardJoystickWidgetRaw()
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
void StandardJoystickWidgetRaw::setupWidget()
{
	layout1 = new QVBoxLayout{this};
	this->setLayout(layout1);
	layout2 = new QHBoxLayout{};
	layout3 = new QVBoxLayout{};
	
	// axes
	QStringList names;
	for (uint i=0; i<m_joystick->axesCount(); ++i) {names << "Axis "+QString::number(i+1);}
	boxAxes = new AxesWidget{names,this};
	layout3->addWidget(boxAxes);
	
	// pov
	layout4 = new QHBoxLayout{};
	for (uint i=0; i<m_joystick->povsCount(); ++i)
	{
		PovWidgetDecorated *p = new PovWidgetDecorated{"POV"+QString::number(i+1),this};
		layout4->addWidget(p);
		povWidgets.push_back(p);
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
		buttonsLayout->addWidget(b,i/8,i%8,1,1);
		buttonsWidgets.push_back(b);
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
void StandardJoystickWidgetRaw::initState()
{
	for (uint axis=0; axis<m_joystick->axesCount(); ++axis)
		boxAxes->slotSetValue(axis,m_joystick->axisValue(axis));
	
	for (uint button=0; button<m_joystick->buttonsCount(); ++button)
		buttonsWidgets[button]->slotSetChecked(m_joystick->buttonValue(button));
	
	for (uint pov=0; pov<m_joystick->povsCount(); ++pov)
		povWidgets[pov]->slotSetAngle(m_joystick->povValue(pov));
}

// SLOT RUN ONE LOOP //////////////////////////////////////////////////////////
void StandardJoystickWidgetRaw::slotRunOneLoop()
{
	// read controller state, signals will be emited, they are connected to the 3 following slots
	m_joystick->readGameController();
	
	// feed tempo chart (even if no change)
	++compteur;
	if (compteur % ratioTempoChart == 0)
	{
		std::vector<uint> axes = boxAxes->axesToDisplay();
		for (uint axis : axes) {tempoChart->slotPushValue(axis,m_joystick->axisValue(axis));}
	}
}

// SLOT JOYSTICK BUTTON STATE CHANGED /////////////////////////////////////////
void StandardJoystickWidgetRaw::slotJoystickButtonStateChanged(GameControllerButtonEvent event)
{
	buttonsWidgets[event.button]->slotSetChecked(event.pressed);
}

// SLOT JOYSTICK AXIS VALUE CHANGED ///////////////////////////////////////////
void StandardJoystickWidgetRaw::slotJoystickAxisValueChanged(GameControllerAxisEvent event)
{
	boxAxes->slotSetValue(event.axis,event.value);
}

// SLOT JOYSTICK POV ANGLE CHANGED ////////////////////////////////////////////
void StandardJoystickWidgetRaw::slotJoystickPovAngleChanged(GameControllerPovEvent event)
{
	povWidgets[event.pov]->slotSetAngle(event.angle);
}






// SLOT UPDATE TEMPO CURVES ///////////////////////////////////////////////////
void StandardJoystickWidgetRaw::slotUpdateTempoCurves(uint axis, bool bDisplay)
{
	std::vector<uint> axes = boxAxes->axesToDisplay();
	
	if (bDisplay) {tempoChart->slotAddCurve(axis,"Axis"+QString::number(axis+1));}
	else {tempoChart->slotRemoveCurve(axis);}
	
	if (axes.size() == 0) {tempoChart->hide();}
	else {tempoChart->show();}
}

