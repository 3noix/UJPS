#include "MainWindow.h"
#include "CurveChartView.h"
#include "AbstractRealJoystick.h"
#include "RealJoysticksManager.h"
#include "GameControllersEnumThread.h"

#include "CURVES/GuiCurvePolynomial2.h"
#include "CURVES/GuiCurvePolynomial3Centered.h"
#include "CURVES/GuiCurvePolynomial3NotCentered.h"
#include "CURVES/GuiCurveExpCentered.h"
#include "CURVES/GuiCurveExpNotCentered.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QTimer>
#include <QMenu>
#include <QMenuBar>
#include <QMovie>

#include "ApplicationSettings.h"
#include "SettingsDialog.h"
#include "VigemSettingsWidget.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  SETUP WIDGET
//  CREATE ACTIONS
//  CREATE MENUS
//
//  CURVES NAMES
//  CREATE CURVE
//
//  SLOT SETTINGS
//  SLOT UPDATE
//  SLOT END UPDATE
//  SLOT QUIT
//  SLOT RUN ONE LOOP
//
//  SLOT JOYSTICK CHANGED
//  SLOT AXIS CHANGED
//  SLOT DIRECTION CHANGED
//  SLOT TRIM 1 CHANGED
//  SLOT TRIM 2 CHANGED
//  SLOT CURVE CHANGED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}
{
	// read settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	settings.readFile();
	bool bWhiteList = settings.property("bWhiteListPid").toBool();
	
	m_currentJoystick = nullptr;
	m_axis = 0;
	m_settingsWidget = nullptr;
	m_curve = nullptr;
	
	// widgets
	this->setupWidget();
	this->createActions();
	this->createMenus();
	this->resize(600,700);
	
	m_thread = new GameControllersEnumThread{this};
	m_jm.loadPlugins(QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/");
	
	// connections
	QObject::connect(actionSettings, &QAction::triggered, this, &MainWindow::slotSettings);
	QObject::connect(actionUpdate,   &QAction::triggered, this, &MainWindow::slotUpdate);
	QObject::connect(actionQuit,     &QAction::triggered, this, &MainWindow::slotQuit);
	QObject::connect(m_thread,       &QThread::finished,  this, &MainWindow::slotEndUpdate);
	
	m_timer = new QTimer{this};
	m_timer->setInterval(15);
	QObject::connect(m_timer, &QTimer::timeout, this, &MainWindow::slotRunOneLoop);
	
	// ViGEm white-listing
	if (bWhiteList && m_vigemInterface.vigemIsReady())
		m_vigemInterface.whiteList(QCoreApplication::applicationPid());
	
	// fetch joysticks info
	this->slotUpdate();
}

MainWindow::~MainWindow()
{
	// remove this application from the white list
	// (to avoid to pollute the white list with many invalid pids)
	if (m_vigemInterface.vigemIsReady())
		m_vigemInterface.blackList(QCoreApplication::applicationPid());
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	// create layouts
	mainWidget = new QWidget{this};
	layout = new QGridLayout{mainWidget};
	mainWidget->setLayout(layout);
	
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
	chartView = new CurveChartView{this};
	
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
	
	// page 2 (loading)
	widgetLoading = new QWidget{this};
	layoutLoading = new QVBoxLayout{widgetLoading};
	widgetLoading->setLayout(layoutLoading);
	labelLoading = new QLabel{"Enumerating controllers...",this};
	labelGif = new QLabel{this};
	movieGif = new QMovie{":/RESOURCES/ICONES/loading.gif",{},this};
	labelGif->setMovie(movieGif);
	layoutLoading->addWidget(labelLoading);
	layoutLoading->addWidget(labelGif);
	layoutLoading->addStretch();
	
	// stack and loading pages
	stack = new QStackedWidget{this};
	stack->addWidget(mainWidget);
	stack->addWidget(widgetLoading);
	this->setCentralWidget(stack);
	this->setWindowIcon(QIcon{":/RESOURCES/ICONES/curve.png"});
}

// CREATE ACTIONS /////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
	actionSettings = new QAction{"Settings",this};
	actionSettings->setStatusTip("Application settings");
	actionSettings->setIcon(QIcon{":/RESOURCES/ICONES/outils.png"});
	
	actionUpdate = new QAction{"Update controllers list",this};
	actionUpdate->setStatusTip("Update controllers list");
	actionUpdate->setShortcut(QKeySequence{"F5"});
	actionUpdate->setShortcutContext(Qt::WindowShortcut);
	actionUpdate->setIcon(QIcon{":/RESOURCES/ICONES/update.png"});
	
	actionQuit = new QAction{"Quit",this};
	actionQuit->setStatusTip("Quit");
	actionQuit->setShortcut(QKeySequence{"Ctrl+Q"});
	actionQuit->setShortcutContext(Qt::WindowShortcut);
	actionQuit->setIcon(QIcon{":/RESOURCES/ICONES/croixRouge.png"});
}

// CREATE MENUS ///////////////////////////////////////////////////////////////
void MainWindow::createMenus()
{
	fileMenu = this->menuBar()->addMenu("File");
	fileMenu->addAction(actionSettings);
	fileMenu->addAction(actionUpdate);
	fileMenu->addSeparator();
	fileMenu->addAction(actionQuit);
}






// CURVES NAMES ///////////////////////////////////////////////////////////////
QStringList MainWindow::curvesNames() const
{
	QStringList list;
	
	list << "No curve";
	list << "Polynomial 2 curve";
	list << "Polynomial 3 curve (centered)";
	list << "Polynomial 3 curve (not centered)";
	list << "Exponential curve (centered)";
	list << "Exponential curve (not centered)";
	
	return list;
}

// CREATE CURVE ///////////////////////////////////////////////////////////////
AbstractAxisCurve* MainWindow::createCurve(const QString &curveName) const
{
	if (curveName == "No curve")                               {return nullptr;}
	else if (curveName == "Polynomial 2 curve")                {return new GuiCurvePolynomial2{};}
	else if (curveName == "Polynomial 3 curve (centered)")     {return new GuiCurvePolynomial3Centered{};}
	else if (curveName == "Polynomial 3 curve (not centered)") {return new GuiCurvePolynomial3NotCentered{};}
	else if (curveName == "Exponential curve (centered)")      {return new GuiCurveExpCentered{};}
	else if (curveName == "Exponential curve (not centered)")  {return new GuiCurveExpNotCentered{};}
	else {return nullptr;}
}






// SLOT SETTINGS //////////////////////////////////////////////////////////////
void MainWindow::slotSettings()
{
	SettingsDialog settingsDialog{this};
	settingsDialog.addSettingsWidget(new VigemSettingsWidget{&settingsDialog});
	
	int result = settingsDialog.exec();
	if (result == QDialog::Rejected) {return;}
}

// SLOT UPDATE ////////////////////////////////////////////////////////////////
void MainWindow::slotUpdate()
{
	if (m_thread->isRunning()) {return;}
	m_timer->stop();
	
	QObject::disconnect(boxJoystick,  SIGNAL(currentIndexChanged(int)), this, SLOT(slotJoystickChanged(int)));
	QObject::disconnect(boxAxis,      SIGNAL(currentIndexChanged(int)), this, SLOT(slotAxisChanged(int)));
	QObject::disconnect(boxDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDirectionChanged(int)));
	QObject::disconnect(boxTrim1,     SIGNAL(valueChanged(double)),     this, SLOT(slotTrim1Changed(double)));
	QObject::disconnect(boxTrim2,     SIGNAL(valueChanged(double)),     this, SLOT(slotTrim2Changed(double)));
	QObject::disconnect(boxCurve,     SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurveChanged(int)));
	
	actionSettings->setEnabled(false);
	actionUpdate->setEnabled(false);
	actionQuit->setEnabled(false);
	stack->setCurrentWidget(widgetLoading);
	movieGif->start();
	
	boxJoystick->clear();
	boxAxis->clear();
	boxJoystick->setEnabled(false);
	boxAxis->setEnabled(false);
	boxDirection->setEnabled(false);
	boxTrim1->setEnabled(false);
	boxTrim2->setEnabled(false);
	boxCurve->setEnabled(false);
	
	m_currentJoystick = nullptr;
	m_axis = 0;
	m_settingsWidget = nullptr;
	m_curve = nullptr;
	
	m_thread->enumerateControllers();
}

// SLOT END UPDATE ////////////////////////////////////////////////////////////
void MainWindow::slotEndUpdate()
{
	// restore connections
	QObject::connect(boxJoystick,  SIGNAL(currentIndexChanged(int)), this, SLOT(slotJoystickChanged(int)));
	QObject::connect(boxAxis,      SIGNAL(currentIndexChanged(int)), this, SLOT(slotAxisChanged(int)));
	QObject::connect(boxDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDirectionChanged(int)));
	QObject::connect(boxTrim1,     SIGNAL(valueChanged(double)),     this, SLOT(slotTrim1Changed(double)));
	QObject::connect(boxTrim2,     SIGNAL(valueChanged(double)),     this, SLOT(slotTrim2Changed(double)));
	QObject::connect(boxCurve,     SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurveChanged(int)));
	
	// get list of joysticks hidden by ViGEm
	bool bVigem = m_vigemInterface.vigemIsReady();
	QStringList affectedDevices;
	if (bVigem)
	{
		affectedDevices = m_vigemInterface.affectedDevices();
		for (QString &str : affectedDevices) {str.remove("HID\\");}
	}
	
	// build joysticks items
	QVector<GameController*> gcv = m_thread->releaseGameControllers();
	m_jm.fromGameControllers(gcv);
	QStringList joysticksNames = m_jm.joysticksNames();
	int i = 0;
	for (QString &joystickName : joysticksNames)
	{
		if (affectedDevices.contains(m_jm.joystick(i)->hardwareId()))
		{joystickName += " (hidden)";}
	++i;
	}
	boxJoystick->addItems(joysticksNames);
	
	// reenable widgets and actions
	boxJoystick->setEnabled(true);
	boxAxis->setEnabled(true);
	boxDirection->setEnabled(true);
	boxTrim1->setEnabled(true);
	boxTrim2->setEnabled(true);
	boxCurve->setEnabled(true);
	
	movieGif->stop();
	stack->setCurrentWidget(mainWidget);
	actionSettings->setEnabled(true);
	actionUpdate->setEnabled(true);
	actionQuit->setEnabled(true);
	
	m_timer->start();
}

// SLOT QUIT //////////////////////////////////////////////////////////////////
void MainWindow::slotQuit()
{
	if (m_thread->isRunning()) {return;}
	qApp->quit();
}

// SLOT RUN ONE LOOP //////////////////////////////////////////////////////////
void MainWindow::slotRunOneLoop()
{
	if (m_axis == -1 || !m_currentJoystick) {return;}
	
	m_currentJoystick->readGameController();
	QVector<JoystickChange> changes = m_currentJoystick->changes();
	
	for (const JoystickChange &ch : changes)
	{
		if (ch.type == ControlType::Axis && ch.numButtonAxisPov == (uint)m_axis)
		{chartView->updateCurrent();}
	}
}






// SLOT JOYSTICK CHANGED //////////////////////////////////////////////////////
void MainWindow::slotJoystickChanged(int index)
{
	QObject::disconnect(boxAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(slotAxisChanged(int)));
	
	boxAxis->clear();
	if (AbstractRealJoystick *joystick = m_jm.joystick(index))
	{
		m_currentJoystick = joystick;
		boxAxis->addItems(m_currentJoystick->axesNames());
	}
	
	QObject::connect(boxAxis, SIGNAL(currentIndexChanged(int)), this, SLOT(slotAxisChanged(int)));
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

