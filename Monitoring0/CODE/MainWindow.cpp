#include "MainWindow.h"
#include "QGameController.h"
#include "WIDGETS/StandardJoystickWidget.h"
const int NB_JOYSTICKS_MAX = 16;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	mainTabWidget = new QTabWidget(this);
	this->setCentralWidget(mainTabWidget);
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/eyes.png"));
	this->setMinimumWidth(500.0);
	
	for (int i=0; i<NB_JOYSTICKS_MAX; ++i)
	{
		QGameController *j = new QGameController(i);
		if (j->isValid())
		{
			joysticks << j;
		}
		else
		{
			delete j;
			break;
		}
	}
	
	
	for (QGameController *j : joysticks)
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

