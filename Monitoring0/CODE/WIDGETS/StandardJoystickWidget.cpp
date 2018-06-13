#include "StandardJoystickWidget.h"
#include "QGameController.h"
#include "AxesWidget.h"
#include "ButtonWidget.h"
#include "PovWidgetDecorated.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  SETUP WIDGET
//
//  INIT STATE
//  SLOT JOYSTICK AXIS VALUE CHANGED
//  SLOT JOYSTICK BUTTON STATE CHANGED
//  SLOT JOYSTICK POV ANGLE CHANGED
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
StandardJoystickWidget::StandardJoystickWidget(QGameController *j, bool own)
{
	Q_ASSERT(j);
	m_joystick = j;
	m_own = own;
	
	this->setupWidget();
	this->initState();
	
	m_timer = new QTimer(this);
	m_timer->setInterval(15);
	connect(m_timer, &QTimer::timeout, m_joystick, &QGameController::readGameController);
	m_timer->start();
	
	QObject::connect(j, &QGameController::gameControllerAxisEvent,   this, &StandardJoystickWidget::slotJoystickAxisValueChanged);
	QObject::connect(j, &QGameController::gameControllerButtonEvent, this, &StandardJoystickWidget::slotJoystickButtonStateChanged);
	QObject::connect(j, &QGameController::gameControllerPovEvent,    this, &StandardJoystickWidget::slotJoystickPovAngleChanged);
}

StandardJoystickWidget::~StandardJoystickWidget()
{
	//delete layout2;
	//delete layout3;
	
	if (m_own && m_joystick)
	{
		delete m_joystick;
		m_joystick = nullptr;
	}
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void StandardJoystickWidget::setupWidget()
{
	layout1 = new QHBoxLayout(this);
	this->setLayout(layout1);
	layout2 = new QVBoxLayout();
	
	// axes
	QStringList names;
	for (uint i=0; i<m_joystick->axesCount(); ++i) {names << "Axis "+QString::number(i+1);}
	boxAxes = new AxesWidget(names,this);
	layout2->addWidget(boxAxes);
	
	// pov
	layout3 = new QHBoxLayout();
	for (uint i=0; i<m_joystick->povsCount(); ++i)
	{
		PovWidgetDecorated *p = new PovWidgetDecorated{"POV"+QString::number(i+1),this};
		layout3->addWidget(p);
		povWidgets << p;
	}
	layout3->addStretch();
	layout2->addLayout(layout3);
	layout1->addLayout(layout2);
	
	// buttons
	boxButtons = new QGroupBox("Buttons",this);
	buttonsLayout = new QGridLayout(boxButtons);
	buttonsLayout->setVerticalSpacing(5);
	boxButtons->setLayout(buttonsLayout);
	int nbButtons = m_joystick->buttonsCount();
	for (int i=0; i<qMax(32,nbButtons); ++i)
	{
		ButtonWidget *b = new ButtonWidget(i+1,i<nbButtons,this);
		buttonsLayout->addWidget(b,i/8,i%8,1,1);
		buttonsWidgets << b;
	}
	layout1->addWidget(boxButtons);
}






// INIT STATE /////////////////////////////////////////////////////////////////
void StandardJoystickWidget::initState()
{
	for (uint axis=0; axis<m_joystick->axesCount(); ++axis)
		boxAxes->slotSetValue(axis,m_joystick->axisValue(axis));
	
	for (uint button=0; button<m_joystick->buttonsCount(); ++button)
		buttonsWidgets[button]->slotSetChecked(m_joystick->buttonValue(button));
	
	for (uint pov=0; pov<m_joystick->povsCount(); ++pov)
		povWidgets[pov]->slotSetAngle(m_joystick->povValue(pov));
}

// SLOT JOYSTICK AXIS VALUE CHANGED ///////////////////////////////////////////
void StandardJoystickWidget::slotJoystickAxisValueChanged(QGameControllerAxisEvent *event)
{
	boxAxes->slotSetValue(event->axis(),event->value());
}

// SLOT JOYSTICK BUTTON STATE CHANGED /////////////////////////////////////////
void StandardJoystickWidget::slotJoystickButtonStateChanged(QGameControllerButtonEvent *event)
{
	buttonsWidgets[event->button()]->slotSetChecked(event->pressed());
}

// SLOT JOYSTICK POV ANGLE CHANGED ////////////////////////////////////////////
void StandardJoystickWidget::slotJoystickPovAngleChanged(QGameControllerPovEvent *event)
{
	povWidgets[event->pov()]->slotSetAngle(event->angle());
}


