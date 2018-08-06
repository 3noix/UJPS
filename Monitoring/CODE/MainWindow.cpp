#include "MainWindow.h"
#include "GameController.h"
#include "AbstractRealJoystick.h"
#include "RealJoysticksManager.h"
#include "WIDGETS/StandardJoystickWidget.h"
#include "WIDGETS/StandardJoystickWidgetRaw.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  SETUP WIDGET
//  CLEAR TABS
//  SLOT MODE CHANGED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QWidget{parent}
{
	tabs = nullptr;
	this->setupWidget();
	QObject::connect(boxMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slotModeChanged(int)));
	this->slotModeChanged(2);
}

MainWindow::~MainWindow()
{
	delete layoutUp;
}



// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	layout = new QVBoxLayout{this};
	layout->setSpacing(10);
	this->setLayout(layout);
	
	layoutUp = new QHBoxLayout{};
	labelMode = new QLabel{"Mode:",this};
	boxMode = new QComboBox{this};
	boxMode->addItem("Using DirectInput / XInput");
	boxMode->addItem("Using RealJoystick class with no plugin");
	boxMode->addItem("Using RealJoystick class with plugins");
	boxMode->setCurrentIndex(2);
	layoutUp->addWidget(labelMode);
	layoutUp->addWidget(boxMode);
	layoutUp->addStretch();
	layout->addLayout(layoutUp);
	
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/eyes.png"));
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
}

// SLOT MODE CHANGED //////////////////////////////////////////////////////////
void MainWindow::slotModeChanged(int index)
{
	this->clearTabs();
	
	tabs = new QTabWidget{this};
	layout->addWidget(tabs);
	
	if (index == 0) // raw, i.e. using QtGameControllerModif
	{
		// search for DirectInput and XInput controllers
		QVector<GameController*> joysticks = GameController::enumerateControllers(this);
		
		// add a tab for each controller
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
	}
	else if (index == 1 || index == 2)
	{
		RealJoysticksManager jm;
		if (index == 2) {jm.loadPlugins(QCoreApplication::applicationDirPath() + "/../../ControllersPlugins/PLUGINS/");}
		jm.searchForControllers();
		int nbOtherJoy = jm.nbJoysticks();
		for (int i=0; i<nbOtherJoy; ++i)
		{
			AbstractRealJoystick *j = jm.releaseJoystick(0);
			if (j)
			{
				QWidget *temp = new QWidget{tabs};
				QWidget *w = new StandardJoystickWidget{j,true,temp};
				QVBoxLayout *layout = new QVBoxLayout(temp);
				temp->setLayout(layout);
				layout->addWidget(w);
				layout->addStretch();
				int index = tabs->addTab(temp,j->description());
				tabs->setTabToolTip(index,j->hardwareId());
			}
		}
	}
}


