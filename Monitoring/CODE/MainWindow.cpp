#include "MainWindow.h"
#include "GameController.h"
#include "AbstractRealJoystick.h"
#include "RealJoysticksManager.h"
#include "WIDGETS/StandardJoystickWidget.h"
#include "WIDGETS/StandardJoystickWidgetRaw.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  CREATE ACTIONS
//  CREATE MENUS
//  SETUP WIDGET
//  CLEAR TABS
//
//  SLOT MODE CHANGED
//  SLOT UPDATE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}
{
	tabs = nullptr;
	labelNoController = nullptr;
	
	this->createActions();
	this->createMenus();
	this->setupWidget();
	
	QObject::connect(boxMode,      SIGNAL(currentIndexChanged(int)), this, SLOT(slotModeChanged(int)));
	QObject::connect(actionUpdate, &QAction::triggered,              this, &MainWindow::slotUpdate);
	QObject::connect(actionQuit,   &QAction::triggered,              qApp, &QCoreApplication::quit);
	
	this->slotModeChanged(2);
}

MainWindow::~MainWindow()
{
	delete layoutUp;
}






// CREATE ACTIONS /////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
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
	fileMenu->addAction(actionUpdate);
	fileMenu->addSeparator();
	fileMenu->addAction(actionQuit);
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	mainWidget = new QWidget{this};
	layout = new QVBoxLayout{mainWidget};
	layout->setSpacing(10);
	mainWidget->setLayout(layout);
	
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
	
	this->setCentralWidget(mainWidget);
	this->setWindowIcon(QIcon{":/RESOURCES/ICONES/eyes.png"});
	this->setMinimumWidth(700.0);
}

// CLEAR TABS /////////////////////////////////////////////////////////////////
void MainWindow::clearTabs()
{
	if (tabs)
	{
		layout->removeWidget(tabs);
		delete tabs;
		tabs = nullptr;
	}
	
	if (labelNoController)
	{
		layout->removeWidget(labelNoController);
		delete labelNoController;
		labelNoController = nullptr;
	}
}

// SLOT MODE CHANGED //////////////////////////////////////////////////////////
void MainWindow::slotModeChanged(int index)
{
	this->clearTabs();
	
	if (index == 0) // raw, i.e. using QtGameControllerModif
	{
		// search for DirectInput and XInput controllers
		QVector<GameController*> joysticks = GameController::enumerateControllers(this);
		
		// case there is no controller
		if (joysticks.size() == 0)
		{
			labelNoController = new QLabel{"No controller detected",this};
			labelNoController->setAlignment(Qt::AlignCenter);
			layout->addWidget(labelNoController);
			return;
		}
		
		// add a tab for each controller
		tabs = new QTabWidget{this};
		for (GameController *j : joysticks)
		{
			QWidget *temp = new QWidget{tabs};
			QWidget *w = new StandardJoystickWidgetRaw{j,true,temp};
			QVBoxLayout *layout = new QVBoxLayout{temp};
			temp->setLayout(layout);
			layout->addWidget(w);
			layout->addStretch();
			int index = tabs->addTab(temp,j->description());
			tabs->setTabToolTip(index,j->hardwareId());
		}
		layout->addWidget(tabs);
	}
	else if (index == 1 || index == 2)
	{
		// search controllers
		RealJoysticksManager jm;
		if (index == 2) {jm.loadPlugins(QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/");}
		jm.searchForControllers();
		int nbOtherJoy = jm.nbJoysticks();
		
		// case there is no controller
		if (nbOtherJoy == 0)
		{
			labelNoController = new QLabel{"No controller detected",this};
			labelNoController->setAlignment(Qt::AlignCenter);
			layout->addWidget(labelNoController);
			return;
		}
		
		// add a tab for each controller
		tabs = new QTabWidget{this};
		for (int i=0; i<nbOtherJoy; ++i)
		{
			if (AbstractRealJoystick *j = jm.releaseJoystick(0))
			{
				QWidget *temp = new QWidget{tabs};
				QWidget *w = new StandardJoystickWidget{j,true,temp};
				QVBoxLayout *layout = new QVBoxLayout{temp};
				temp->setLayout(layout);
				layout->addWidget(w);
				layout->addStretch();
				int index = tabs->addTab(temp,j->description());
				tabs->setTabToolTip(index,j->hardwareId());
			}
		}
		layout->addWidget(tabs);
	}
}

// SLOT UPDATE ////////////////////////////////////////////////////////////////
void MainWindow::slotUpdate()
{
	this->slotModeChanged(boxMode->currentIndex());
}

