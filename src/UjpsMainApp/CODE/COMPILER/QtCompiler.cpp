#include "QtCompiler.h"
#include "QtCompilationProcess.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDir>



///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  COMPILATOR NAME
//  RUN COMPILATION
//  STOP COMPILATION
//  SETTINGS WIDGET
//  IS RUNNING
//
//  CREATE WIDGET
//  READ SETTINGS
//  WRITE SETTINGS
///////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
QtCompiler::QtCompiler() : AbstractCompiler{}
{
	m_process = new QtCompilationProcess{};
	QObject::connect(m_process, SIGNAL(compilationMessage(QString,QColor)), this, SIGNAL(compilationMessage(QString,QColor)));
	QObject::connect(m_process, SIGNAL(compilationFinished()),              this, SIGNAL(compilationFinished()));
	
	this->createWidget();
	this->readSettings();
}

QtCompiler::~QtCompiler()
{
	delete boxSettings;
	delete m_process;
}






// COMPILATOR NAME ////////////////////////////////////////////////////////////
QString QtCompiler::compilatorName() const
{
	return "C++ Qt mingw32";
}

// RUN COMPILATION ////////////////////////////////////////////////////////////
void QtCompiler::runCompilation()
{
	// écriture des réglages dans un fichier
	this->writeSettings();
	
	// recherche d'un unique fichier .pro
	QString compilationDirectory = this->compilationDirectory();
	if (compilationDirectory == "")
	{
		emit compilationMessage("No compilation directory specified",Qt::red);
		return;
	}
	QStringList proFiles = QDir{compilationDirectory}.entryList({"*.pro"},QDir::Files);
	if (proFiles.size() == 0)
	{
		emit compilationMessage("There is no .pro file in the compilation directory",Qt::red);
		return;
	}
	else if (proFiles.size() > 1)
	{
		emit compilationMessage("There are several .pro files in the compilation directory",Qt::red);
		return;
	}
	
	// lancement de la compilation
	QString qtDir = lineQtBinaryDirPath->text();
	QString mingwDir = lineMingwBinaryDirPath->text();
	bool bDebug = checkDebug->isChecked();
	bool bRelease = checkRelease->isChecked();
	
	m_process->setupEnvironmentForQtUsage(qtDir,mingwDir);
	m_process->beginCompilation(compilationDirectory,proFiles[0],bDebug,bRelease);
}

// STOP COMPILATION ///////////////////////////////////////////////////////////
void QtCompiler::stopCompilation()
{
	m_process->killCompilation();
}

// SETTINGS WIDGET ////////////////////////////////////////////////////////////
QWidget* QtCompiler::settingsWidget() const
{
	return boxSettings;
}

// IS RUNNING /////////////////////////////////////////////////////////////////
bool QtCompiler::isRunning() const
{
	return (m_process->state() != QProcess::NotRunning);
}






// CREATE WIDGET //////////////////////////////////////////////////////////////
void QtCompiler::createWidget()
{
	// box settings
	boxSettings = new QGroupBox{"Qt MinGw compiler settings"};
	boxLayout = new QGridLayout{boxSettings};
	boxSettings->setLayout(boxLayout);
	
	// line edits
	labelQtBinaryDirPath = new QLabel{"Qt directory :",boxSettings};
	labelMingwBinaryDirPath = new QLabel{"Mingw directory :",boxSettings};
	lineQtBinaryDirPath = new QLineEdit{boxSettings};
	lineMingwBinaryDirPath = new QLineEdit{boxSettings};
	
	// checkboxes
	checkDebug = new QCheckBox{"Debug",boxSettings};
	checkRelease = new QCheckBox{"Release",boxSettings};
	checkDebug->setChecked(true);
	checkRelease->setChecked(true);
	
	// ajout aux layouts
	boxLayout->addWidget(labelQtBinaryDirPath,0,0,1,1);
	boxLayout->addWidget(labelMingwBinaryDirPath,1,0,1,1);
	boxLayout->addWidget(lineQtBinaryDirPath,0,1,1,1);
	boxLayout->addWidget(lineMingwBinaryDirPath,1,1,1,1);
	boxLayout->addWidget(checkDebug,2,0,1,2);
	boxLayout->addWidget(checkRelease,3,0,1,2);
}

// READ SETTINGS //////////////////////////////////////////////////////////////
bool QtCompiler::readSettings()
{
	// read settings
	QFile file{QCoreApplication::applicationDirPath() + "/QtCompilerSettings.json"};
	if (!file.open(QIODevice::ReadOnly)) {return false;}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
	file.close();
	if (!jsonDoc.isObject()) {return false;}
	QJsonObject settings = jsonDoc.object();
	
	// on vérifie que toutes les propriétés sont là
	if (!settings.contains("qtBinaryDirPath"))    {return false;}
	if (!settings.contains("mingwBinaryDirPath")) {return false;}
	if (!settings.contains("debugCompilation"))   {return false;}
	if (!settings.contains("releaseCompilation")) {return false;}
	
	// application des réglages
	lineQtBinaryDirPath->setText(settings["qtBinaryDirPath"].toString());
	lineMingwBinaryDirPath->setText(settings["mingwBinaryDirPath"].toString());
	checkDebug->setChecked(settings["debugCompilation"].toBool());
	checkRelease->setChecked(settings["releaseCompilation"].toBool());
	return true;
}

// WRITE SETTINGS /////////////////////////////////////////////////////////////
bool QtCompiler::writeSettings()
{
	QJsonObject settings;
	settings["qtBinaryDirPath"] = lineQtBinaryDirPath->text();
	settings["mingwBinaryDirPath"] = lineMingwBinaryDirPath->text();
	settings["debugCompilation"] = checkDebug->isChecked();
	settings["releaseCompilation"] = checkRelease->isChecked();
	
	QFile file{QCoreApplication::applicationDirPath() + "/QtCompilerSettings.json"};
	if (!file.open(QIODevice::WriteOnly)) {return false;}
	qint64 bytesWritten = file.write(QJsonDocument{settings}.toJson());
	file.close();
	return (bytesWritten > 0);
}

