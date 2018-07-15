#include "MainWindow.h"
#include "GameController.h"
#include "WIDGETS/StandardJoystickWidget.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	mainTabWidget = new QTabWidget(this);
	this->setCentralWidget(mainTabWidget);
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/eyes.png"));
	this->setMinimumWidth(500.0);
	
	// search for DirectInput and XInput controllers
	QVector<GameController*> joysticks = GameController::enumerateControllers(this);
	
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

