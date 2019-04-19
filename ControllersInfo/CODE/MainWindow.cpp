#include "MainWindow.h"
#include "GameController.h"
#include "GameControllersEnumThread.h"
#include <QCoreApplication>

#include "ApplicationSettings.h"
#include "SettingsDialog.h"
#include "VigemSettingsWidget.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  CREATE ACTIONS
//  CREATE MENUS
//  SETUP WIDGET
//  CREATE HEADERS
//  CLEAR LAYOUT
//  SET DATA
//
//  SLOT SETTINGS
//  SLOT START UPDATE
//  SLOT END UPDATE
//  SLOT QUIT
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
	
	// connections
	QObject::connect(actionSettings, &QAction::triggered, this, &MainWindow::slotSettings);
	QObject::connect(actionUpdate,   &QAction::triggered, this, &MainWindow::slotStartUpdate);
	QObject::connect(actionQuit,     &QAction::triggered, this, &MainWindow::slotQuit);
	QObject::connect(m_thread,       &QThread::finished,  this, &MainWindow::slotEndUpdate);
	
	// ViGEm white-listing
	if (bWhiteList && m_vigemInterface.vigemIsReady())
		m_vigemInterface.whiteList(QCoreApplication::applicationPid());
	
	// fetch joysticks info
	this->slotStartUpdate();
}

MainWindow::~MainWindow()
{
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
	
	actionUpdate = new QAction{"Update",this};
	actionUpdate->setStatusTip("Update controllers info");
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
	gridWidget = new QWidget{this};
	layout = new QGridLayout{gridWidget};
	gridWidget->setLayout(layout);
	layout->setContentsMargins(10,20,10,20);
	layout->setVerticalSpacing(15);
	
	widgetLoading = new QWidget{this};
	layoutLoading = new QVBoxLayout{widgetLoading};
	widgetLoading->setLayout(layoutLoading);
	labelLoading = new QLabel{"Enumerating controllers...",this};
	labelGif = new QLabel{this};
	movieGif = new QMovie{":/RESOURCES/ICONES/loading.gif",{},this};
	labelGif->setMovie(movieGif);
	layoutLoading->addWidget(labelLoading);
	layoutLoading->addWidget(labelGif);
	
	stack = new QStackedWidget{this};
	stack->addWidget(gridWidget);
	stack->addWidget(widgetLoading);
	stack->setCurrentWidget(gridWidget);
	
	this->setCentralWidget(stack);
	this->resize(700,250);
	this->setWindowIcon(QIcon{":/RESOURCES/ICONES/info.png"});
	this->setWindowTitle("Controllers info");
}

// CREATE HEADERS /////////////////////////////////////////////////////////////
void MainWindow::createHeaders(bool bVigemColumn)
{
	QLabel *labelDescription = new QLabel{"Description",this};
	QLabel *labelId          = new QLabel{"ID",this};
	QLabel *labelButtons     = new QLabel{"Buttons",this};
	QLabel *labelAxes        = new QLabel{"Axes",this};
	QLabel *labelPovs        = new QLabel{"Povs",this};
	QLabel *labelHardwareId  = new QLabel{"Hardware ID",this};
	
	labelDescription->setAlignment(Qt::AlignCenter);
	labelId->setAlignment(Qt::AlignCenter);
	labelButtons->setAlignment(Qt::AlignCenter);
	labelAxes->setAlignment(Qt::AlignCenter);
	labelPovs->setAlignment(Qt::AlignCenter);
	labelHardwareId->setAlignment(Qt::AlignCenter);
	
	layout->addWidget(labelDescription,0,0,1,1);
	layout->addWidget(labelId,0,1,1,1);
	layout->addWidget(labelButtons,0,2,1,1);
	layout->addWidget(labelAxes,0,3,1,1);
	layout->addWidget(labelPovs,0,4,1,1);
	layout->addWidget(labelHardwareId,0,5,1,1);
	
	if (bVigemColumn)
	{
		QLabel *labelHidden = new QLabel{"Hidden by ViGEm",this};
		labelHidden->setAlignment(Qt::AlignCenter);
		layout->addWidget(labelHidden,0,6,1,1);
	}
}

// CLEAR LAYOUT ///////////////////////////////////////////////////////////////
void MainWindow::clearLayout()
{
	QLayoutItem *child = nullptr;
	while ((child = layout->takeAt(0))) {delete child->widget();}
}

// SET DATA ///////////////////////////////////////////////////////////////////
void MainWindow::setData(const QVector<GameController*> joysticks)
{
	this->clearLayout();
	
	// get list of joysticks hidden by ViGEm
	bool bVigem = m_vigemInterface.vigemIsReady();
	QStringList affectedDevices;
	if (bVigem)
	{
		affectedDevices = m_vigemInterface.affectedDevices();
		for (QString &str : affectedDevices) {str.remove("HID\\");}
	}
	
	// an additional column only if we white-list this app
	ApplicationSettings& settings = ApplicationSettings::instance();
	bool bVigemColumn = settings.property("bWhiteListPid").toBool();
	
	// populate the grid
	this->createHeaders(bVigemColumn);
	int iLine = 1;
	for (GameController *gc : joysticks)
	{
		uint id = gc->id();
		QString idString;
		if (id < 100) {idString = QString::number(id) + " (DirectInput)";}
		else {idString = QString::number(id-100) + " (XInput)";}
		
		QLabel *item0 = new QLabel{gc->description(),this};
		QLabel *item1 = new QLabel{idString,this};
		QLabel *item2 = new QLabel{QString::number(gc->buttonsCount()),this};
		QLabel *item3 = new QLabel{QString::number(gc->axesCount()),this};
		QLabel *item4 = new QLabel{QString::number(gc->povsCount()),this};
		QLabel *item5 = new QLabel{gc->hardwareId(),this};
		
		item0->setAlignment(Qt::AlignCenter);
		item1->setAlignment(Qt::AlignCenter);
		item2->setAlignment(Qt::AlignCenter);
		item3->setAlignment(Qt::AlignCenter);
		item4->setAlignment(Qt::AlignCenter);
		item5->setAlignment(Qt::AlignCenter);
		
		layout->addWidget(item0,iLine,0,1,1);
		layout->addWidget(item1,iLine,1,1,1);
		layout->addWidget(item2,iLine,2,1,1);
		layout->addWidget(item3,iLine,3,1,1);
		layout->addWidget(item4,iLine,4,1,1);
		layout->addWidget(item5,iLine,5,1,1);
		
		if (bVigemColumn)
		{
			QString hiddenOrNot = affectedDevices.contains(gc->hardwareId()) ? "Yes" : "No";
			QLabel *item6 = new QLabel{hiddenOrNot,this};
			item6->setAlignment(Qt::AlignCenter);
			layout->addWidget(item6,iLine,6,1,1);
		}
		
		++iLine;
	}
	
	layout->addItem(new QSpacerItem{0,0,QSizePolicy::Minimum,QSizePolicy::Expanding},iLine,0,1,1);
}






// SLOT SETTINGS //////////////////////////////////////////////////////////////
void MainWindow::slotSettings()
{
	SettingsDialog settingsDialog{this};
	settingsDialog.addSettingsWidget(new VigemSettingsWidget{&settingsDialog});
	
	int result = settingsDialog.exec();
	if (result == QDialog::Rejected) {return;}
}

// SLOT START UPDATE //////////////////////////////////////////////////////////
void MainWindow::slotStartUpdate()
{
	if (m_thread->isRunning()) {return;}
	
	// widgets
	actionSettings->setEnabled(false);
	actionUpdate->setEnabled(false);
	actionQuit->setEnabled(false);
	stack->setCurrentWidget(widgetLoading);
	movieGif->start();
	
	// search for DirectInput and XInput controllers
	m_thread->enumerateControllersAllAtOnce();
}

// SLOT END UPDATE ////////////////////////////////////////////////////////////
void MainWindow::slotEndUpdate()
{
	// retrieve results and update the table
	this->setData(m_thread->gameControllers());
	
	// widgets
	movieGif->stop();
	stack->setCurrentWidget(gridWidget);
	actionSettings->setEnabled(true);
	actionUpdate->setEnabled(true);
	actionQuit->setEnabled(true);
}

// SLOT QUIT //////////////////////////////////////////////////////////////////
void MainWindow::slotQuit()
{
	if (m_thread->isRunning()) {return;}
	qApp->quit();
}

