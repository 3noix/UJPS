#include "MainWindow.h"

#include "REAL_JOYSTICKS/RealJoysticksManager.h"
#include "REAL_JOYSTICKS/RealJoystick.h"
#include "WIDGETS/StandardJoystickWidget.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	mainTabWidget = new QTabWidget(this);
	this->setCentralWidget(mainTabWidget);
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/eyes.png"));
	this->setMinimumWidth(500.0);
	
	RealJoysticksManager jm;
	int nbOtherJoy = jm.nbJoysticks();
	for (int i=0; i<nbOtherJoy; ++i)
	{
		AbstractRealJoystick *j = jm.releaseJoystick(0);
		if (j)
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
			joysticks << j;
		}
	}
}

MainWindow::~MainWindow()
{
	
}

