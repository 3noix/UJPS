#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QPushButton>
#include <QLineEdit>
#include <QToolBar>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>
#include <QThread>
#include <QFileDialog>
#include <QPluginLoader>
#include <QCoreApplication>

#include "MainWindow.h"
#include "TextEdit.h"
#include "AbstractProfile.h"
#include "VirtualJoystick.h"
#include "../otherFunctions.h"
#include "../COMPILER/CompilationWidget.h"
#include "../SETTINGS/SettingsDialog.h"
#include "../SETTINGS/MyFileDialog.h"
#include "../SETTINGS/ApplicationSettings.h"
#include "../SETTINGS/GeneralSettingsWidget.h"
#include "../SETTINGS/VJoySettingsWidget.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  CREATE ACTIONS
//  SETUP WIDGET
//  SET STATE
//  CLOSE EVENT
//
//  LOAD PROFILE
//  UNLOAD PROFILE
//
//  SLOT BROWSE BUTTON CLICKED
//  SLOT SETTINGS
//  SLOT COMPILATION
//  SLOT PLAY
//  SLOT STOP
//  SLOT UNLOAD
//  SLOT ONE LOOP
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	// read settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	settings.readFile();
	bool bUseVJoyConfigBinary = settings.property("bUseVJoyConfigBinary").toBool();
	QString vJoyConfigBinary = settings.property("vJoyConfigBinary").toString();
	VirtualJoystick::setVJoyConfigOptions(bUseVJoyConfigBinary,vJoyConfigBinary);
	
	// init
	m_proFilePath = "";
	m_dllFilePath = "";
	m_dllFileName = "";
	m_profile = nullptr;
	m_loader = nullptr;
	m_bConfigOk = false;
	
	timer = new QTimer(this);
	m_compilWidget = new CompilationWidget{this};
	
	this->createActions();
	this->setupWidget();
	this->setState(HmiState::WaitingForDll);
	
	// connections
	QObject::connect(timer, &QTimer::timeout, this, &MainWindow::slotOneLoop);
	QObject::connect(actionCompilation,&QAction::triggered,this,&MainWindow::slotCompilation);
	QObject::connect(actionSettings,&QAction::triggered,this,&MainWindow::slotSettings);
	QObject::connect(actionPlay,&QAction::triggered,this,&MainWindow::slotPlay);
	QObject::connect(actionStop,&QAction::triggered,this,&MainWindow::slotStop);
	QObject::connect(actionUnload,&QAction::triggered,this,&MainWindow::slotUnload);
	QObject::connect(boutonBrowse,&QPushButton::clicked,this,&MainWindow::slotBrowseButtonClicked);
}

MainWindow::~MainWindow()
{
	timer->stop();
	this->unloadProfile(true);
	
	// write settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	if (!settings.isEmpty()) {settings.writeFile();}
}





// CREATE ACTIONS /////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
	actionSettings = new QAction("Settings",this);
	actionSettings->setStatusTip("Application settings");
	actionSettings->setIcon(QIcon(":/RESOURCES/ICONES/outils.png"));
	
	actionCompilation = new QAction("Compilation",this);
	actionCompilation->setStatusTip("Compile profile");
	actionCompilation->setIcon(QIcon(":/RESOURCES/ICONES/compilation.png"));
	
	actionPlay = new QAction("Run",this);
	actionPlay->setStatusTip("Load and run profile");
	actionPlay->setIcon(QIcon(":/RESOURCES/ICONES/play.png"));
	
	actionStop = new QAction("Stop",this);
	actionStop->setStatusTip("Stop profile");
	actionStop->setIcon(QIcon(":/RESOURCES/ICONES/stop.png"));
	
	actionUnload = new QAction("Unload",this);
	actionUnload->setStatusTip("Unload profile");
	actionUnload->setIcon(QIcon(":/RESOURCES/ICONES/eject.png"));
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	// create layouts
	layout = new QVBoxLayout(this);
	this->setLayout(layout);
	layoutDllChoice = new QHBoxLayout(this);
	layoutRefreshRate = new QHBoxLayout(this);
	
	// toolbar
	toolbar = new QToolBar("Session",this);
	toolbar->setFloatable(false);
	toolbar->setMovable(false);
	toolbar->addAction(actionSettings);
	toolbar->addAction(actionCompilation);
	toolbar->addAction(actionPlay);
	toolbar->addAction(actionStop);
	toolbar->addAction(actionUnload);
	
	// dll choice
	boutonBrowse = new QPushButton("Browse",this);
	lineDllPath = new QLineEdit(this);
	lineDllPath->setReadOnly(true);
	
	// refresh rate
	labelRefreshRate = new QLabel("Refresh rate:",this);
	boxRefreshRate = new QSpinBox(this);
	boxRefreshRate->setMinimum(5);
	boxRefreshRate->setMaximum(500);
	boxRefreshRate->setValue(15);
	boxRefreshRate->setSingleStep(500);
	boxRefreshRate->setSuffix(" ms");
	
	// text edit
	textEdit = new TextEdit(this);
	
	// add widgets to laytouts
	layoutDllChoice->addWidget(boutonBrowse);
	layoutDllChoice->addWidget(lineDllPath);
	layoutRefreshRate->addWidget(labelRefreshRate);
	layoutRefreshRate->addWidget(boxRefreshRate);
	layoutRefreshRate->addStretch();
	
	layout->addLayout(layoutDllChoice);
	layout->addSpacing(5);
	layout->addLayout(layoutRefreshRate);
	layout->addSpacing(5);
	layout->addWidget(toolbar);
	layout->addWidget(textEdit);
	
	// end
	this->resize(500,500);
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/gamepad.png"));
}

// SET STATE //////////////////////////////////////////////////////////////////
void MainWindow::setState(HmiState s)
{
	if (s == HmiState::WaitingForDll)
	{
		actionSettings->setEnabled(true);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(false);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(true);
		boxRefreshRate->setEnabled(false);
	}
	else if (s == HmiState::ReadyToPlayNotLoaded)
	{
		actionSettings->setEnabled(true);
		actionCompilation->setEnabled(true);
		actionPlay->setEnabled(true);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(true);
		boxRefreshRate->setEnabled(true);
	}
	else if (s == HmiState::ReadyToPlayLoaded)
	{
		actionSettings->setEnabled(false);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(true);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(true);
		boutonBrowse->setEnabled(true);
		boxRefreshRate->setEnabled(true);
	}
	else if (s == HmiState::Playing)
	{
		actionSettings->setEnabled(false);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(false);
		actionStop->setEnabled(true);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(false);
		boxRefreshRate->setEnabled(false);
	}
	else if (s == HmiState::Quitting)
	{
		actionSettings->setEnabled(false);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(false);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(false);
		boxRefreshRate->setEnabled(false);
	}
}

// CLOSE EVENT ////////////////////////////////////////////////////////////////
void MainWindow::closeEvent(QCloseEvent *event)
{
	textEdit->addMessage("Closing",Qt::black);
	timer->stop();
	this->setState(HmiState::Quitting);
	this->unloadProfile(true);
	
	QThread::sleep(1);
	event->accept();
}







// LOAD PROFILE ///////////////////////////////////////////////////////////////
bool MainWindow::loadProfile(const QString &dllFilePath)
{
	m_loader = new QPluginLoader(dllFilePath);
	if (QObject *plugin = m_loader->instance())
	{
		AbstractProfile* profile = qobject_cast<AbstractProfile*>(plugin);
		if (profile)
		{
			m_profile = profile;
			QObject::connect(m_profile,SIGNAL(message(QString,QColor)),textEdit,SLOT(addMessage(QString,QColor)));
			//QObject::connect(m_profile,&AbstractProfile::message,textEdit,&TextEdit::addMessage); // ne marche pas !!
			return true;
		}
	}
	
	delete m_loader;
	m_loader = nullptr;
	return false;
}

// UNLOAD PROFILE /////////////////////////////////////////////////////////////
bool MainWindow::unloadProfile(bool bResetPath)
{
	if (!m_loader) {return true;}
	
	m_profile->stop();
	bool b = m_loader->unload(); // delete m_profile
	delete m_loader;
	m_loader = nullptr;
	m_profile = nullptr;
	m_bConfigOk = false;
	if (bResetPath)
	{
		m_proFilePath = "";
		m_dllFilePath = "";
		m_dllFileName = "";
	}
	return b;
}







// SLOT BROWSE BUTTON CLICKED /////////////////////////////////////////////////
void MainWindow::slotBrowseButtonClicked()
{
	QString proFilePath = MyFileDialog::getOpenFileName(this, "Select profile plugin", "defaultDirectory", "*.pro");
	if (proFilePath == "" || proFilePath == m_proFilePath) {return;}
	
	this->unloadProfile(true);
	m_proFilePath = proFilePath;
	
	lineDllPath->setText(m_proFilePath);
	textEdit->addMessage("Plugin path changed for " + m_proFilePath,Qt::black);
	this->setState(HmiState::ReadyToPlayNotLoaded);
}

// SLOT SETTINGS //////////////////////////////////////////////////////////////
void MainWindow::slotSettings()
{
	SettingsDialog settingsDialog(this);
	settingsDialog.addSettingsWidget(new GeneralSettingsWidget(&settingsDialog));
	settingsDialog.addSettingsWidget(new VJoySettingsWidget(&settingsDialog));
	int result = settingsDialog.exec();
	if (result == QDialog::Rejected) {return;}
}

// SLOT COMPILATION ///////////////////////////////////////////////////////////
void MainWindow::slotCompilation()
{
	m_compilWidget->setProjectDirectory(dirName(m_proFilePath));
	m_compilWidget->show();
}

// SLOT PLAY //////////////////////////////////////////////////////////////////
void MainWindow::slotPlay()
{
	if (timer->isActive()) {return;}
	
	// load the plugin only if necessary
	if (!m_loader || m_dllFilePath == "")
	{
		// search for one dll
		QString dllDir = dirName(m_proFilePath) + "/" + debugOrRelease();
		QStringList dllFiles = QDir{dllDir}.entryList({"*.dll"},QDir::Files);
		if (dllFiles.size() == 0)
		{
			textEdit->addMessage("No profile dll in directory " + dllDir,Qt::red);
			return;
		}
		else if (dllFiles.size() > 1)
		{
			textEdit->addMessage("Several profile dlls in directory " + dllDir,Qt::red);
			return;
		}
		m_dllFileName = dllFiles[0];
		m_dllFilePath = dllDir + "/" + m_dllFileName;
		
		// load the profile plugin
		textEdit->addMessage("Loading profile " + m_dllFileName,Qt::black);
		m_bConfigOk = this->loadProfile(m_dllFilePath);
	}
	if (!m_bConfigOk)
	{
		textEdit->addMessage("Plugin loading failed",Qt::red);
		this->setState(HmiState::ReadyToPlayNotLoaded);
		return;
	}
	
	// updating widgets
	textEdit->addMessage("Starting " + m_dllFileName,Qt::black);
	this->setState(HmiState::Playing);
	
	// configuration
	m_profile->setTimeStep(boxRefreshRate->value());
	timer->setInterval(boxRefreshRate->value());
	try
	{
		m_profile->reset();
		if (!m_profile->play())
		{
			textEdit->addMessage("Failed to initialize profile",Qt::red);
			this->setState(HmiState::ReadyToPlayLoaded);
			return;
		}
	}
	catch (std::exception &e)
	{
		QString msg = "Failed to initialize profile: " + QString{e.what()};
		textEdit->addMessage(msg,Qt::red);
		this->setState(HmiState::ReadyToPlayLoaded);
		return;
	}
	
	// start the loop!
	timer->start();
	textEdit->addMessage("Running",Qt::black);
}

// SLOT STOP //////////////////////////////////////////////////////////////////
void MainWindow::slotStop()
{
	textEdit->addMessage("Stop profile " + m_dllFileName,Qt::black);
	this->setState(HmiState::ReadyToPlayLoaded);
	
	timer->stop();
	m_profile->stop();
	m_profile->UnmapAll();
}

// SLOT UNLOAD ////////////////////////////////////////////////////////////////
void MainWindow::slotUnload()
{
	textEdit->addMessage("Unload profile " + m_dllFileName,Qt::black);
	this->setState(HmiState::ReadyToPlayNotLoaded);
	this->unloadProfile(false);
}

// SLOT ONE LOOP //////////////////////////////////////////////////////////////
void MainWindow::slotOneLoop()
{
	if (!m_profile)
	{
		textEdit->addMessage("Impossible: no profile set",Qt::red);
		return;
	}
	
	if (!m_bConfigOk)
	{
		textEdit->addMessage("Impossible: profile not correctly initialized",Qt::red);
		return;
	}
	
	try {m_profile->run();}
	catch (std::exception &e) {textEdit->addMessage(e.what(),Qt::red);}
}

