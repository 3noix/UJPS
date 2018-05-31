#include "StandardJoystickWidget.h"
#include "AbstractRealJoystick.h"
#include "ButtonWidget.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  SETUP WIDGET
//  INIT STATE
//  JOYSTICK BUTTON STATE CHANGED
//  JOYSTICK AXIS VALUE CHANGED
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
	layout = new QHBoxLayout(this);
	this->setLayout(layout);
	
	// axes
	boxAxes = new QGroupBox("Axes",this);
	axesLayout = new QGridLayout(boxAxes);
	boxAxes->setLayout(axesLayout);
	layout->addWidget(boxAxes);
	for (uint i=0; i<m_joystick->axesCount(); ++i)
	{
		QLabel *l1 = new QLabel(m_joystick->axisName(i),this);
		l1->setMinimumWidth(20);
		QSlider *s = new QSlider(Qt::Horizontal,this);
		s->setEnabled(false);
		s->setTickPosition(QSlider::TicksBothSides);
		s->setTickInterval(1000/5);
		s->setMinimum(-1000);
		s->setMaximum(1000);
		s->setValue(0);
		s->setMinimumWidth(150);
		QLabel *l2 = new QLabel("0",this);
		l2->setFixedWidth(50);
		l2->setAlignment(Qt::AlignCenter);
		axesLayout->addWidget(l1,i,0,1,1);
		axesLayout->addWidget(s,i,1,1,1);
		axesLayout->addWidget(l2,i,2,1,1);
		axesLabels << l1;
		axesSliders << s;
		axesValues << l2;
	}
	
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
		buttonsChecks << b;
	}
	
	// fin
	layout->addWidget(boxButtons);
}

// INIT STATE /////////////////////////////////////////////////////////////////
void StandardJoystickWidget::initState()
{
	for (uint i=0; i<m_joystick->axesCount(); ++i) {this->joystickAxisValueChanged(i,m_joystick->axisValue(i));}
	for (uint i=0; i<m_joystick->buttonsCount(); ++i) {buttonsChecks[i]->slotSetChecked(m_joystick->buttonPressed(i));}
}

// JOYSTICK BUTTON STATE CHANGED //////////////////////////////////////////////
void StandardJoystickWidget::joystickButtonStateChanged(uint button, bool bPressed)
{
	buttonsChecks[button]->slotSetChecked(bPressed);
}

// JOYSTICK AXIS VALUE CHANGED ////////////////////////////////////////////////
void StandardJoystickWidget::joystickAxisValueChanged(uint axis, float value)
{
	axesSliders[axis]->setValue(qRound(1000.0*value));
	axesValues[axis]->setText(QString::number(qRound(1000.0*value)));
}

// SLOT RUN ONE LOOP //////////////////////////////////////////////////////////
void StandardJoystickWidget::slotRunOneLoop()
{
	m_joystick->readGameController();
	QVector<JoystickChange> changes = m_joystick->changes();
	
	for (const JoystickChange &ch : changes)
	{
		if (ch.type == ControlType::Button)
		{
			buttonsChecks[ch.numButtonOrAxis]->slotSetChecked(ch.bButtonPressed);
		}
		else
		{
			axesSliders[ch.numButtonOrAxis]->setValue(qRound(1000.0*ch.axisValue));
			axesValues[ch.numButtonOrAxis]->setText(QString::number(qRound(1000.0*ch.axisValue)));
		}
	}
}


