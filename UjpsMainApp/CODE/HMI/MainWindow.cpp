#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QPushButton>
#include <QLineEdit>
#include <QToolBar>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QThread>
#include <QFileDialog>

#include "../ProfileEngine.h"
#include "MainWindow.h"
#include "TextEdit.h"
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
//  SLOT BROWSE BUTTON CLICKED
//  SLOT SETTINGS
//  SLOT COMPILATION
//  SLOT PLAY
//  SLOT STOP
//  SLOT UNLOAD
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MainWindow::MainWindow(QString proFilePath, int dtms, bool bPlay, QWidget *parent) : QWidget(parent)
{
	// read settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	settings.readFile();
	bool bUseVJoyConfigBinary = settings.property("bUseVJoyConfigBinary").toBool();
	QString vJoyConfigBinary = settings.property("vJoyConfigBinary").toString();
	VirtualJoystick::setVJoyConfigOptions(bUseVJoyConfigBinary, vJoyConfigBinary);

	// init
	m_proFilePath = "";
	m_dllFilePath = "";
	m_dllFileName = "";
	m_engine = new ProfileEngine{ this };

	m_compilWidget = new CompilationWidget{ this };

	this->createActions();
	this->setupWidget();
	this->setState(HmiState::WaitingForDll);

	// connections
	QObject::connect(chkMappingRepeater, &QCheckBox::stateChanged, m_engine, &ProfileEngine::slotMappingRepeaterChanged);
	QObject::connect(m_engine, &ProfileEngine::message, textEdit, &TextEdit::addMessage);
	QObject::connect(actionCompilation, &QAction::triggered, this, &MainWindow::slotCompilation);
	QObject::connect(actionSettings, &QAction::triggered, this, &MainWindow::slotSettings);
	QObject::connect(actionPlay, &QAction::triggered, this, &MainWindow::slotPlay);
	QObject::connect(actionStop, &QAction::triggered, this, &MainWindow::slotStop);
	QObject::connect(actionUnload, &QAction::triggered, this, &MainWindow::slotUnload);
	QObject::connect(boutonBrowse, &QPushButton::clicked, this, &MainWindow::slotBrowseButtonClicked);

	// arguments supplémentaires
	if(!proFilePath.isEmpty())
	{
		m_proFilePath = proFilePath;
		m_dllFilePath = "";
		m_dllFileName = "";

		lineDllPath->setText(m_proFilePath);
		textEdit->addMessage("Plugin path changed for " + m_proFilePath, Qt::black);
		this->setState(HmiState::ReadyToPlayNotLoaded);

		boxRefreshRate->setValue(dtms);

		if(bPlay) { this->slotPlay(); }
	}
}

MainWindow::~MainWindow()
{
	// write settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	if(!settings.isEmpty()) { settings.writeFile(); }
}





// CREATE ACTIONS /////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
	actionSettings = new QAction("Settings", this);
	actionSettings->setStatusTip("Application settings");
	actionSettings->setIcon(QIcon(":/RESOURCES/ICONES/outils.png"));

	actionCompilation = new QAction("Compilation", this);
	actionCompilation->setStatusTip("Compile profile");
	actionCompilation->setIcon(QIcon(":/RESOURCES/ICONES/compilation.png"));

	actionPlay = new QAction("Run", this);
	actionPlay->setStatusTip("Load and run profile");
	actionPlay->setIcon(QIcon(":/RESOURCES/ICONES/play.png"));

	actionStop = new QAction("Stop", this);
	actionStop->setStatusTip("Stop profile");
	actionStop->setIcon(QIcon(":/RESOURCES/ICONES/stop.png"));

	actionUnload = new QAction("Unload", this);
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
	toolbar = new QToolBar("Session", this);
	toolbar->setFloatable(false);
	toolbar->setMovable(false);
	toolbar->addAction(actionSettings);
	toolbar->addAction(actionCompilation);
	toolbar->addAction(actionPlay);
	toolbar->addAction(actionStop);
	toolbar->addAction(actionUnload);

	// dll choice
	boutonBrowse = new QPushButton("Browse", this);
	lineDllPath = new QLineEdit(this);
	lineDllPath->setReadOnly(true);

	// refresh rate
	labelRefreshRate = new QLabel("Refresh rate:", this);
	boxRefreshRate = new QSpinBox(this);
	boxRefreshRate->setMinimum(5);
	boxRefreshRate->setMaximum(500);
	boxRefreshRate->setValue(15);
	boxRefreshRate->setSingleStep(500);
	boxRefreshRate->setSuffix(" ms");

	// mapping repeater
	chkMappingRepeater = new QCheckBox("Mapping Repeater", this);
	chkMappingRepeater->setChecked(Qt::CheckState::Unchecked);
	chkMappingRepeater->setToolTip("Detected vJoy inputs are repeated for " + QString::number(g_MAPPING_REPEATER_DURATION) + " seconds, to help map actions in game without real joysticks interfering.");
	chkMappingRepeater->setEnabled(false);

	// text edit
	textEdit = new TextEdit(this);

	// add widgets to laytouts
	layoutDllChoice->addWidget(boutonBrowse);
	layoutDllChoice->addWidget(lineDllPath);
	layoutRefreshRate->addWidget(labelRefreshRate);
	layoutRefreshRate->addWidget(boxRefreshRate);
	layoutRefreshRate->addWidget(chkMappingRepeater);
	layoutRefreshRate->addStretch();

	layout->addLayout(layoutDllChoice);
	layout->addSpacing(5);
	layout->addLayout(layoutRefreshRate);
	layout->addSpacing(5);
	layout->addWidget(toolbar);
	layout->addWidget(textEdit);

	// end
	this->resize(500, 500);
	this->setWindowIcon(QIcon(":/RESOURCES/ICONES/gamepad.png"));
}

// SET STATE //////////////////////////////////////////////////////////////////
void MainWindow::setState(HmiState s)
{
	if(s == HmiState::WaitingForDll)
	{
		actionSettings->setEnabled(true);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(false);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(true);
		boxRefreshRate->setEnabled(false);
		chkMappingRepeater->setChecked(false);
		chkMappingRepeater->setEnabled(false);
	}
	else if(s == HmiState::ReadyToPlayNotLoaded)
	{
		actionSettings->setEnabled(true);
		actionCompilation->setEnabled(true);
		actionPlay->setEnabled(true);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(true);
		boxRefreshRate->setEnabled(true);
		chkMappingRepeater->setChecked(false);
		chkMappingRepeater->setEnabled(false);
	}
	else if(s == HmiState::ReadyToPlayLoaded)
	{
		actionSettings->setEnabled(false);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(true);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(true);
		boutonBrowse->setEnabled(true);
		boxRefreshRate->setEnabled(true);
		chkMappingRepeater->setChecked(false);
		chkMappingRepeater->setEnabled(false);
	}
	else if(s == HmiState::Playing)
	{
		actionSettings->setEnabled(false);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(false);
		actionStop->setEnabled(true);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(false);
		boxRefreshRate->setEnabled(false);
		chkMappingRepeater->setEnabled(true);
	}
	else if(s == HmiState::Quitting)
	{
		actionSettings->setEnabled(false);
		actionCompilation->setEnabled(false);
		actionPlay->setEnabled(false);
		actionStop->setEnabled(false);
		actionUnload->setEnabled(false);
		boutonBrowse->setEnabled(false);
		boxRefreshRate->setEnabled(false);
		chkMappingRepeater->setEnabled(false);
	}
}

// CLOSE EVENT ////////////////////////////////////////////////////////////////
void MainWindow::closeEvent(QCloseEvent *event)
{
	textEdit->addMessage("Closing", Qt::black);
	m_engine->stop();
	this->setState(HmiState::Quitting);

	if(m_engine->isLoaded())
	{
		m_engine->unloadProfile();
		QThread::sleep(1);
	}

	event->accept();
}









// SLOT BROWSE BUTTON CLICKED /////////////////////////////////////////////////
void MainWindow::slotBrowseButtonClicked()
{
	QString proFilePath = MyFileDialog::getOpenFileName(this, "Select profile plugin", "defaultDirectory", "*.pro");
	if(proFilePath == "" || proFilePath == m_proFilePath) { return; }

	m_engine->unloadProfile();
	m_proFilePath = proFilePath;
	m_dllFilePath = "";
	m_dllFileName = "";

	lineDllPath->setText(m_proFilePath);
	textEdit->addMessage("Plugin path changed for " + m_proFilePath, Qt::black);
	this->setState(HmiState::ReadyToPlayNotLoaded);
}

// SLOT SETTINGS //////////////////////////////////////////////////////////////
void MainWindow::slotSettings()
{
	SettingsDialog settingsDialog(this);
	settingsDialog.addSettingsWidget(new GeneralSettingsWidget(&settingsDialog));
	settingsDialog.addSettingsWidget(new VJoySettingsWidget(&settingsDialog));

	int result = settingsDialog.exec();
	if(result == QDialog::Rejected) { return; }
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
	if(m_engine->isActive()) { return; }

	// load the plugin only if necessary
	bool bConfigOk = true;
	if(m_dllFilePath == "" || !m_engine->isLoaded())
	{
		// search for one dll
		QString dllDir = dirName(m_proFilePath) + "/" + debugOrRelease();
		QStringList dllFiles = QDir{ dllDir }.entryList({ "*.dll" }, QDir::Files);
		if(dllFiles.size() == 0)
		{
			textEdit->addMessage("No profile dll in directory " + dllDir, Qt::red);
			return;
		}
		else if(dllFiles.size() > 1)
		{
			textEdit->addMessage("Several profile dlls in directory " + dllDir, Qt::red);
			return;
		}
		m_dllFileName = dllFiles[0];
		m_dllFilePath = dllDir + "/" + m_dllFileName;

		// load the profile plugin
		bConfigOk = m_engine->loadProfile(m_dllFilePath);
		chkMappingRepeater->setEnabled(bConfigOk);
	}

	// manages loading errors
	if(!bConfigOk)
	{
		this->setState(HmiState::ReadyToPlayNotLoaded);
		return;
	}

	// configuration and start
	this->setState(HmiState::Playing);
	if(!m_engine->run(boxRefreshRate->value())) { this->setState(HmiState::ReadyToPlayLoaded); }
}

// SLOT STOP //////////////////////////////////////////////////////////////////
void MainWindow::slotStop()
{
	this->setState(HmiState::ReadyToPlayLoaded);
	m_engine->stop();
}

// SLOT UNLOAD ////////////////////////////////////////////////////////////////
void MainWindow::slotUnload()
{
	m_engine->unloadProfile();
	this->setState(HmiState::ReadyToPlayNotLoaded);
}

