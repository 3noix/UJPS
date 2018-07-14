#include "MainWindow.h"
#include "GameControllerDirectInput.h"
#include "GameControllerXInput.h"
#include "WIDGETS/StandardJoystickWidget.h"
const int NB_JOYSTICKS_MAX_DIRECTINPUT = 16;
const int NB_JOYSTICKS_MAX_XINPUT = 4;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	mainTabWidget = new QTabWidget(this);
	this->setCentralWidget(mainTabWidget);
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/eyes.png"));
	this->setMinimumWidth(500.0);
	
	// search for DirectInput controllers
	for (int i=0; i<NB_JOYSTICKS_MAX_DIRECTINPUT; ++i)
	{
		GameController *j = new GameControllerDirectInput(i);
		if (j->isValid() && j->description() != "Controller (XBOX 360 For Windows)")
		{
			joysticks << j;
		}
		else {delete j;}
	}
	
	// search for XInput controllers
	for (int i=0; i<NB_JOYSTICKS_MAX_XINPUT; ++i)
	{
		GameController *j = new GameControllerXInput(i);
		if (j->isValid())
		{
			joysticks << j;
		}
		else {delete j;}
	}
	
	// add a tab for each controller
	for (GameController *j : joysticks)
	{
		QWidget *w = new StandardJoystickWidget{j};
		QWidget *temp = new QWidget(this);
		QVBoxLayout *layout = new QVBoxLayout(temp);
		temp->setLayout(layout);
		layout->addWidget(w);
		layout->addStretch();
		int index = mainTabWidget->addTab(temp,j->description());
		mainTabWidget->setTabToolTip(index,j->hardwareId());
		joysticksWidgets << w;
	}
}

MainWindow::~MainWindow()
{
	
}

