#include "QtCompilationProcess.h"
#include <QDir>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  SETUP ENVIRONMENT FOR QT USAGE
//  BEGIN COMPILATION
//  KILL COMPILATION
//  SLOT CONTINUE COMPILATION
//
//  SLOT ERROR
//  SLOT ADD TEXT STDOUT
//  SLOT ADD TEXT STDERR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
QtCompilationProcess::QtCompilationProcess() : QProcess{nullptr}
{
	B_QMAKE_PASS = false;
	B_MAKE_DEBUG_PASS = false;
	B_MAKE_RELEASE_PASS = false;
	B_ERROR = false;
	B_DEBUG_RQT = false;
	B_RELEASE_RQT = false;
	
	m_killed = false;
	
	connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotContinueCompilation(int,QProcess::ExitStatus)));
	connect(this, SIGNAL(error(QProcess::ProcessError)),      this, SLOT(slotError(QProcess::ProcessError)));
	connect(this, SIGNAL(readyReadStandardOutput()),          this, SLOT(slotAddTextStdout()));
	connect(this, SIGNAL(readyReadStandardError()),           this, SLOT(slotAddTextStderr()));
}

QtCompilationProcess::~QtCompilationProcess()
{
	if (this->state() != QProcess::NotRunning)
	{this->killCompilation();}
}






// SETUP ENVIRONMENT FOR QT USAGE /////////////////////////////////////////////
void QtCompilationProcess::setupEnvironmentForQtUsage(const QString &qtDir, const QString &mingwDir)
{
	m_qtDir = qtDir;
	m_mingwDir = mingwDir;
	
	QProcessEnvironment myEnvt = QProcessEnvironment::systemEnvironment();
	myEnvt.insert("PATH",qtDir + ";" + mingwDir);
	this->setProcessEnvironment(myEnvt);
}

// BEGIN COMPILATION //////////////////////////////////////////////////////////
void QtCompilationProcess::beginCompilation(const QString &directory, const QString &projectFile, bool debugMode, bool releaseMode)
{
	// vérifie qu'une compilation n'est pas déjà en cours
	if (this->state() != QProcess::NotRunning)
	{
		emit compilationMessage("A compilation process is already running !", Qt::red);
		return;
	}
	
	// vérification de l'existence du répertoire du modèle
	QDir modelDir{directory};
	if (!modelDir.exists())
	{
		emit compilationMessage("The following directory does not exists : " + directory, Qt::red);
		return;
	}
	
	// changement du répertoire de travail
	emit compilationMessage("Command : cd " + directory, Qt::blue);
	this->setWorkingDirectory(directory);
	
	
	// controle de la compilation
	B_QMAKE_PASS = true;
	B_MAKE_DEBUG_PASS = false;
	B_MAKE_RELEASE_PASS = false;
	B_ERROR = false;
	B_DEBUG_RQT = debugMode;
	B_RELEASE_RQT = releaseMode;
	
	// lancer qmake
	m_killed = false;
	emit compilationMessage("Command : qmake " + projectFile, Qt::blue);
	QStringList args = {projectFile};
	this->start(m_qtDir + "/qmake", {projectFile});
}

// KILL COMPILATION ///////////////////////////////////////////////////////////
void QtCompilationProcess::killCompilation()
{
	if (this->state() != QProcess::NotRunning)
	{
		this->kill();
		m_killed = true;
		emit compilationMessage("Compilation process killed !", Qt::red);
		emit compilationFinished();
	}
	else
	{
		emit compilationMessage("The compilation process is not running !", Qt::black);
	}
}

// SLOT CONTINUE COMPILATION //////////////////////////////////////////////////
void QtCompilationProcess::slotContinueCompilation(int exitCode, QProcess::ExitStatus exitStatus)
{
	Q_UNUSED(exitCode)
	
	// si la compil a été killée, on ne cherche pas à continuer qq que ce soit
	if (m_killed) {return;}
	
	// vérifie si make a été lancé entièrement
	bool B_MAKE_DONE = false;
	if (B_DEBUG_RQT && !B_RELEASE_RQT) {B_MAKE_DONE = B_MAKE_DEBUG_PASS;}
	else if (!B_DEBUG_RQT && B_RELEASE_RQT) {B_MAKE_DONE = B_MAKE_RELEASE_PASS;}
	else if (B_DEBUG_RQT && B_RELEASE_RQT) {B_MAKE_DONE = B_MAKE_DEBUG_PASS && B_MAKE_RELEASE_PASS;}
	
	
	// si il y a eu crash dans le process
	if (exitStatus != QProcess::NormalExit)
	{
		emit compilationMessage("Crash !", Qt::red);
	}
	
	// lancement de mingw32-make debug
	// si qmake a été exécuté, si la compil en mode debug a été demandée et pas encore exécutée, et si il n'y a pas d'erreur précédemment
	else if (B_QMAKE_PASS && !B_MAKE_DEBUG_PASS && B_DEBUG_RQT && !B_ERROR)
	{
		B_MAKE_DEBUG_PASS = true;
		
		emit compilationMessage("Command : mingw32-make debug", Qt::blue);
		QStringList args = {"debug"};
		this->start(m_mingwDir + "/mingw32-make", args);
	}
	
	// lancement de mingw32-make release
	// si qmake a été exécuté, si la compil en mode release a été demandée et pas encore exécutée, et si il n'y a pas d'erreur précédemment
	else if (B_QMAKE_PASS && !B_MAKE_RELEASE_PASS && B_RELEASE_RQT && !B_ERROR)
	{
		B_MAKE_RELEASE_PASS = true;
		
		emit compilationMessage("Command : mingw32-make release", Qt::blue);
		QStringList args = {"release"};
		this->start(m_mingwDir + "/mingw32-make", args);
	}
	
	// compilation terminée !
	// si qmake et make (dans les modes demandés) ont été exécutés, et qu'il n'y a pas eu d'erreur précédemment
	else if (B_QMAKE_PASS && B_MAKE_DONE && !B_ERROR)
	{
		emit compilationMessage("Compilation completed !\n", Qt::green);
		emit compilationFinished();
	}
	
	// terminé avec erreur
	else if (B_ERROR)
	{
		emit compilationMessage("Compilation failed or finished with warning(s) !\n", Qt::red);
		emit compilationFinished();
	}
	
	// bug
	else
	{
		emit compilationMessage("Bug in the logic of the compilation slot !\n", Qt::red);
	}
}






// SLOT ERROR /////////////////////////////////////////////////////////////////
void QtCompilationProcess::slotError(QProcess::ProcessError processError)
{
	if (m_killed) {return;}
	
	QStringList errorTypes;
	errorTypes << "QProcess::FailedToStart" << "QProcess::Crashed" << "QProcess::Timedout";
	errorTypes << "QProcess::WriteError" << "QProcess::ReadError" << "QProcess::UnknownError";
	
	if ((processError >= 0) && (processError < 6))
	{
		emit compilationMessage("slotError : " + errorTypes[processError], Qt::red);
	}
	else
	{
		emit compilationMessage("slotError : processError = " + QString::number(processError), Qt::red);
	}
	
	emit compilationFinished();
}

// SLOT ADD TEXT STDOUT ///////////////////////////////////////////////////////
void QtCompilationProcess::slotAddTextStdout()
{
	QString data = this->readAllStandardOutput();
	data = data.trimmed();
	if (data.size() == 0) {return;}
	emit compilationMessage(data,Qt::black);
}

// SLOT ADD TEXT STDERR ///////////////////////////////////////////////////////
void QtCompilationProcess::slotAddTextStderr()
{
	B_ERROR = true;
	QString data = this->readAllStandardError();
	data = data.trimmed();
	if (data.size() == 0) {return;}
	emit compilationMessage(data,Qt::red);
}

