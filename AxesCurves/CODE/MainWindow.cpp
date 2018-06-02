#include "MainWindow.h"
#include "CurveChartView.h"
#include "AbstractRealJoystick.h"

#include "CURVES/JCurveGUI.h"
#include "CURVES/SCurveGUI.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QTimer>



///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  SETUP WIDGET
//  CURVES NAMES
//  CREATE CURVE
//  SLOT RUN ONE LOOP

//  SLOT JOYSTICK CHANGED
//  SLOT AXIS CHANGED
//  SLOT DIRECTION CHANGED
//  SLOT TRIM 1 CHANGED
//  SLOT TRIM 2 CHANGED
//  SLOT CURVE CHANGED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
	QWidget{parent}
{
	m_joyManager.loadPlugins(QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/");
	m_joyManager.searchForControllers();
	
	m_currentJoystick = nullptr;
	m_axis = 0;
	m_settingsWidget = nullptr;
	m_curve = nullptr;
	
	this->setupWidget();
	this->resize(600,700);
	
	m_timer = new QTimer(this);
	m_timer->setInterval(15);
	QObject::connect(m_timer, &QTimer::timeout, this, &MainWindow::slotRunOneLoop);
	m_timer->start();
}

MainWindow::~MainWindow()
{
	
}



// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	// create layouts
	layout = new QGridLayout{this};
	this->setLayout(layout);
	
	// labels
	labelJoystick  = new QLabel{"Joystick:",this};
	labelAxis      = new QLabel{"Axis:",this};
	labelDirection = new QLabel{"Mapping direction:",this};
	labelTrim1     = new QLabel{"Real axis trim:",this};
	labelTrim2     = new QLabel{"Virtual axis trim:",this};
	labelCurve     = new QLabel{"Curve:",this};
	
	// boxes
	boxJoystick  = new QComboBox{this};
	boxAxis      = new QComboBox{this};
	boxDirection = new QComboBox{this};
	boxTrim1     = new QDoubleSpinBox{this};
	boxTrim2     = new QDoubleSpinBox{this};
	boxCurve     = new QComboBox{this};
	
	// boxes modifications
	boxDirection->addItems({"Normal","Reversed"});
	boxCurve->addItems(this->curvesNames());
	boxTrim1->setRange(-1.0,1.0);
	boxTrim2->setRange(-1.0,1.0);
	boxTrim1->setDecimals(4);
	boxTrim2->setDecimals(4);
	boxTrim1->setSingleStep(0.002);
	boxTrim2->setSingleStep(0.002);
	boxTrim1->setValue(0.0);
	boxTrim2->setValue(0.0);
	
	// chart view
	chartView = new CurveChartView(this);
	
	// addition in layout
	layout->addWidget(labelJoystick, 0,0,1,1);
	layout->addWidget(labelAxis,     1,0,1,1);
	layout->addWidget(labelDirection,2,0,1,1);
	layout->addWidget(labelTrim1,    3,0,1,1);
	layout->addWidget(labelTrim2,    4,0,1,1);
	layout->addWidget(labelCurve,    5,0,1,1);
	layout->addWidget(boxJoystick,   0,2,1,1);
	layout->addWidget(boxAxis,       1,2,1,1);
	layout->addWidget(boxDirection,  2,2,1,1);
	layout->addWidget(boxTrim1,      3,2,1,1);
	layout->addWidget(boxTrim2,      4,2,1,1);
	layout->addWidget(boxCurve,      5,2,1,1);
	layout->addItem(new QSpacerItem{20,0,QSizePolicy::Fixed,QSizePolicy::Minimum},   0,1,1,1);
	layout->addItem(new QSpacerItem{0,0,QSizePolicy::Expanding,QSizePolicy::Minimum},0,3,1,1);
	layout->addWidget(chartView,7,0,1,4);
	
	
	// connections
	QObject::connect(boxJoystick,SIGNAL(currentIndexChanged(int)),this,SLOT(slotJoystickChanged(int)));
	QObject::connect(boxAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slotAxisChanged(int)));
	QObject::connect(boxDirection,SIGNAL(currentIndexChanged(int)),this,SLOT(slotDirectionChanged(int)));
	QObject::connect(boxTrim1,SIGNAL(valueChanged(double)),this,SLOT(slotTrim1Changed(double)));
	QObject::connect(boxTrim2,SIGNAL(valueChanged(double)),this,SLOT(slotTrim2Changed(double)));
	QObject::connect(boxCurve,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCurveChanged(int)));
	boxJoystick->addItems(m_joyManager.joysticksNames());
	
	// end
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/curve.png"));
}

// CURVES NAMES ///////////////////////////////////////////////////////////////
QStringList MainWindow::curvesNames() const
{
	return {"No curve","J curve","S curve"};
}

// CREATE CURVE ///////////////////////////////////////////////////////////////
AbstractAxisCurve* MainWindow::createCurve(const QString &curveName) const
{
	if (curveName == "No curve")     {return nullptr;}
	else if (curveName == "J curve") {return new JCurveGUI{};}
	else if (curveName == "S curve") {return new SCurveGUI{};}
	else                             {return nullptr;}
}

// SLOT RUN ONE LOOP //////////////////////////////////////////////////////////
void MainWindow::slotRunOneLoop()
{
	if (m_axis == -1 || !m_currentJoystick) {return;}
	
	m_currentJoystick->readGameController();
	QVector<JoystickChange> changes = m_currentJoystick->changes();
	
	for (const JoystickChange &ch : changes)
	{
		if (ch.type == ControlType::Axis && ch.numButtonOrAxis == (uint)m_axis)
		{chartView->updateCurrent();}
	}
}








// SLOT JOYSTICK CHANGED //////////////////////////////////////////////////////
void MainWindow::slotJoystickChanged(int index)
{
	QObject::disconnect(boxAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slotAxisChanged(int)));
	
	boxAxis->clear();
	AbstractRealJoystick *joystick = m_joyManager.joystick(index);
	if (joystick)
	{
		m_currentJoystick = joystick;
		boxAxis->addItems(m_currentJoystick->axesNames());
	}
	
	QObject::connect(boxAxis,SIGNAL(currentIndexChanged(int)),this,SLOT(slotAxisChanged(int)));
	chartView->changeJoystickOrAxis(m_currentJoystick,0);
}

// SLOT AXIS CHANGED //////////////////////////////////////////////////////////
void MainWindow::slotAxisChanged(int axis)
{
	m_axis = axis;
	chartView->changeJoystickOrAxis(m_currentJoystick,m_axis);
}

// SLOT DIRECTION CHANGED /////////////////////////////////////////////////////
void MainWindow::slotDirectionChanged(int index)
{
	double kdirection = 1.0;
	if (index != 0) {kdirection = -1.0;}
	chartView->changeDirection(kdirection);
}

// SLOT TRIM 1 CHANGED ////////////////////////////////////////////////////////
void MainWindow::slotTrim1Changed(double trim1)
{
	chartView->changeTrim1(trim1);
}

// SLOT TRIM 2 CHANGED ////////////////////////////////////////////////////////
void MainWindow::slotTrim2Changed(double trim2)
{
	chartView->changeTrim2(trim2);
}

// SLOT CURVE CHANGED /////////////////////////////////////////////////////////
void MainWindow::slotCurveChanged(int index)
{
	Q_UNUSED(index)
	AbstractAxisCurve *curve = this->createCurve(boxCurve->currentText());
	
	if (m_settingsWidget)
	{
		layout->removeWidget(m_settingsWidget);
		m_settingsWidget = nullptr;
	}
	
	if (m_curve) {delete m_curve;}
	m_curve = curve;
	
	if (m_curve)
	{
		if (QWidget *w = m_curve->settingsWidget())
		{
			m_settingsWidget = w;
			layout->addWidget(m_settingsWidget,6,0,1,4);
		}
	}
	
	chartView->changeCurve(m_curve);
}


