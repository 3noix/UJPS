#include "MainWindow.h"
#include "GameController.h"
#include "AbstractRealJoystick.h"
#include "RealJoysticksManager.h"
#include "GameControllersEnumThread.h"
#include "WIDGETS/StandardJoystickWidget.h"
#include "WIDGETS/StandardJoystickWidgetRaw.h"

#include "ApplicationSettings.h"
#include "SettingsDialog.h"
#include "VigemSettingsWidget.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  CREATE ACTIONS
//  CREATE MENUS
//  SETUP WIDGET
//
//  CLEAR TABS
//  SET DATA
//
//  SLOT QUIT
//  SLOT SETTINGS
//  SLOT UPDATE
//  SLOT MODE CHANGED
//  START UPDATE
//  END UPDATE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}
{
	// read settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	settings.readFile();
	bool bWhiteList = settings.property("bWhiteListPid").toBool();
	
	// widgets
	this->createActions();
	this->createMenus();
	this->setupWidget();
	
	m_thread = new GameControllersEnumThread{this};
	m_index = 2;
	
	// connections
	QObject::connect(boxMode,        SIGNAL(currentIndexChanged(int)), this, SLOT(slotModeChanged(int)));
	QObject::connect(actionSettings, &QAction::triggered,              this, &MainWindow::slotSettings);
	QObject::connect(actionUpdate,   &QAction::triggered,              this, &MainWindow::slotUpdate);
	QObject::connect(m_thread,       &QThread::finished,               this, &MainWindow::slotEndUpdate);
	QObject::connect(actionQuit,     &QAction::triggered,              this, &MainWindow::slotQuit);
	
	// ViGEm white-listing
	if (bWhiteList && m_vigemInterface.vigemIsReady())
		m_vigemInterface.whiteList(QCoreApplication::applicationPid());
	
	// fetch joysticks info
	this->slotModeChanged(2);
}

MainWindow::~MainWindow()
{
	delete layoutUp;
	
	// remove this application from the white list
	// (to avoid to pollute the white list with many invalid pids)
	if (m_vigemInterface.vigemIsReady())
		m_vigemInterface.blackList(QCoreApplication::applicationPid());
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

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	// main widget and its vertical layout
	mainWidget = new QWidget{this};
	layout = new QVBoxLayout{mainWidget};
	layout->setSpacing(10);
	mainWidget->setLayout(layout);
	
	// combo box to choose the mode
	layoutUp = new QHBoxLayout{};
	labelMode = new QLabel{"Mode:",mainWidget};
	boxMode = new QComboBox{mainWidget};
	boxMode->addItem("Using DirectInput / XInput");
	boxMode->addItem("Using RealJoystick class with no plugin");
	boxMode->addItem("Using RealJoystick class with plugins");
	boxMode->setCurrentIndex(2);
	layoutUp->addWidget(labelMode);
	layoutUp->addWidget(boxMode);
	layoutUp->addStretch();
	layout->addLayout(layoutUp);
	
	// stack and pages 1 (default) and 2 (no controller)
	stack = new QStackedWidget{this};
	tabs = new QTabWidget{this};
	labelNoController = new QLabel{"No controller detected",this};
	labelNoController->setAlignment(Qt::AlignCenter);
	
	// page 3 (loading)
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
	
	// add pages
	stack->addWidget(tabs);
	stack->addWidget(labelNoController);
	stack->addWidget(widgetLoading);
	stack->setCurrentWidget(tabs);
	layout->addWidget(stack);
	
	// end
	this->setCentralWidget(mainWidget);
	this->setWindowIcon(QIcon{":/RESOURCES/ICONES/eyes.png"});
	this->setMinimumWidth(700.0);
}






// CLEAR TABS /////////////////////////////////////////////////////////////////
void MainWindow::clearTabs()
{
	int n = tabs->count();
	for (int i=0; i<n; i++)
	{
		QWidget *w = tabs->widget(0);
		tabs->removeTab(0);
		delete w;
	}
}

// SET DATA ///////////////////////////////////////////////////////////////////
void MainWindow::setData(const QVector<GameController*> joysticks)
{
	// case there is no controller
	if (joysticks.size() == 0)
	{
		stack->setCurrentWidget(labelNoController);
	}
	else
	{
		// get list of joysticks hidden by ViGEm
		bool bVigem = m_vigemInterface.vigemIsReady();
		QStringList affectedDevices;
		if (bVigem)
		{
			affectedDevices = m_vigemInterface.affectedDevices();
			for (QString &str : affectedDevices) {str.remove("HID\\");}
		}
		
		// add a tab for each controller
		for (GameController *j : joysticks)
		{
			QWidget *temp = new QWidget{tabs};
			QWidget *w = new StandardJoystickWidgetRaw{j,true,temp};
			QVBoxLayout *layout = new QVBoxLayout{temp};
			temp->setLayout(layout);
			layout->addWidget(w);
			layout->addStretch();
			
			QString desc = j->description();
			if (bVigem && affectedDevices.contains(j->hardwareId())) {desc += " (hidden)";}
			int index = tabs->addTab(temp,desc);
			tabs->setTabToolTip(index,j->hardwareId());
		}
		stack->setCurrentWidget(tabs);
	}
}

void MainWindow::setData(const QVector<AbstractRealJoystick*> joysticks)
{
	// case there is no controller
	if (joysticks.size() == 0)
	{
		stack->setCurrentWidget(labelNoController);
	}
	else
	{
		// get list of joysticks hidden by ViGEm
		bool bVigem = m_vigemInterface.vigemIsReady();
		QStringList affectedDevices;
		if (bVigem)
		{
			affectedDevices = m_vigemInterface.affectedDevices();
			for (QString &str : affectedDevices) {str.remove("HID\\");}
		}
		
		// add a tab for each controller
		for (AbstractRealJoystick *j : joysticks)
		{
			QWidget *temp = new QWidget{tabs};
			QWidget *w = new StandardJoystickWidget{j,true,temp};
			QVBoxLayout *layout = new QVBoxLayout{temp};
			temp->setLayout(layout);
			layout->addWidget(w);
			layout->addStretch();
			
			QString desc = j->description();
			if (bVigem && affectedDevices.contains(j->hardwareId())) {desc += " (hidden)";}
			int index = tabs->addTab(temp,desc);
			tabs->setTabToolTip(index,j->hardwareId());
		}
		stack->setCurrentWidget(tabs);
	}
}






// SLOT QUIT //////////////////////////////////////////////////////////////////
void MainWindow::slotQuit()
{
	if (m_thread->isRunning()) {return;}
	qApp->quit();
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
	this->slotModeChanged(boxMode->currentIndex());
}

// SLOT MODE CHANGED //////////////////////////////////////////////////////////
void MainWindow::slotModeChanged(int index)
{
	if (m_thread->isRunning()) {return;}
	
	// widgets
	this->clearTabs();
	boxMode->setEnabled(false);
	actionSettings->setEnabled(false);
	actionUpdate->setEnabled(false);
	actionQuit->setEnabled(false);
	stack->setCurrentWidget(widgetLoading);
	movieGif->start();
	
	// search for DirectInput and XInput controllers
	m_thread->enumerateControllersAllAtOnce();
	m_index = index;
}

// SLOT END UPDATE ////////////////////////////////////////////////////////////
void MainWindow::slotEndUpdate()
{
	QVector<GameController*> gcv = m_thread->releaseGameControllers();
	
	if (m_index == 0) {this->setData(gcv);}
	else if (m_index == 1 || m_index == 2)
	{
		RealJoysticksManager jm;
		if (m_index == 2) {jm.loadPlugins(QCoreApplication::applicationDirPath() + "/ControllersPlugins/");}
		jm.fromGameControllers(gcv);
		this->setData(jm.releaseAll());
	}
	
	// widgets
	movieGif->stop();
	stack->setCurrentWidget(tabs);
	actionSettings->setEnabled(true);
	actionUpdate->setEnabled(true);
	actionQuit->setEnabled(true);
	boxMode->setEnabled(true);
}

