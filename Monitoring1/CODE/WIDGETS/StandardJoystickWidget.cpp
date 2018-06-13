#include "StandardJoystickWidget.h"
#include "AbstractRealJoystick.h"
#include "AxesWidget.h"
#include "ButtonWidget.h"
#include "PovWidgetDecorated.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  SETUP WIDGET
//  INIT STATE
//  JOYSTICK BUTTON STATE CHANGED
//  JOYSTICK AXIS VALUE CHANGED
//  JOYSTICK POV ANGLE CHANGED
//  SLOT RUN ONE LOOP
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
StandardJoystickWidget::StandardJoystickWidget(AbstractRealJoystick *j, bool own)
{
	Q_ASSERT(j);
	m_joystick = j;
	m_own = own;
	
	this->setupWidget();
	this->initState();
	
	m_timer = new QTimer(this);
	m_timer->setInterval(15);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(slotRunOneLoop()));
	m_timer->start();
}

StandardJoystickWidget::~StandardJoystickWidget()
{
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
	for (uint i=0; i<m_joystick->axesCount(); ++i) {names << m_joystick->axisName(i);}
	boxAxes = new AxesWidget(names,this);
	layout2->addWidget(boxAxes);
	
	// pov
	layout3 = new QHBoxLayout();
	for (uint i=0; i<m_joystick->povsCount(); ++i)
	{
		PovWidgetDecorated *p = new PovWidgetDecorated{m_joystick->povName(i),this};
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
		if (i < nbButtons) {b->setToolTip(m_joystick->buttonName(i));}
		buttonsLayout->addWidget(b,i/8,i%8,1,1);
		buttonsWidgets << b;
	}
	
	// fin
	layout1->addWidget(boxButtons);
}

// INIT STATE /////////////////////////////////////////////////////////////////
void StandardJoystickWidget::initState()
{
	for (uint i=0; i<m_joystick->buttonsCount(); ++i) {this->joystickButtonStateChanged(i,m_joystick->buttonPressed(i));}
	for (uint i=0; i<m_joystick->axesCount(); ++i)    {this->joystickAxisValueChanged(i,m_joystick->axisValue(i));}
	for (uint i=0; i<m_joystick->povsCount(); ++i)    {this->joystickPovAngleChanged(i,m_joystick->povValue(i));}
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

// SLOT RUN ONE LOOP //////////////////////////////////////////////////////////
void StandardJoystickWidget::slotRunOneLoop()
{
	m_joystick->readGameController();
	QVector<JoystickChange> changes = m_joystick->changes();
	
	for (const JoystickChange &ch : changes)
	{
		if (ch.type == ControlType::Button)
			this->joystickButtonStateChanged(ch.numButtonAxisPov,ch.bButtonPressed);
		else if (ch.type == ControlType::Axis)
			this->joystickAxisValueChanged(ch.numButtonAxisPov,ch.axisOrPovValue);
		else if (ch.type == ControlType::Pov)
			this->joystickPovAngleChanged(ch.numButtonAxisPov,ch.axisOrPovValue);
	}
}


