#include "CompilationWidget.h"
#include "QtCompiler.h"
#include "../HMI/TextEdit.h"

#include <QIcon>
#include <QGridLayout>
#include <QCloseEvent>
#include <QPushButton>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  SET PROJECT DIRECTORY
//  SETUP WIDGET
//  CLOSE EVENT
//  KEY PRESS EVENT
//
//  SLOT RUN
//  SLOT STOP
//  SLOT CLOSE
//  SLOT COMPILATION FINISHED
//  SLOT MESSAGE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
CompilationWidget::CompilationWidget(QWidget *parent) : QWidget{parent}
{
	// compiler
	m_compiler = new QtCompiler{};
	boxSettings = m_compiler->settingsWidget();
	connect(m_compiler, SIGNAL(compilationMessage(QString,QColor)), this, SLOT(slotMessage(QString,QColor)));
	connect(m_compiler, SIGNAL(compilationFinished()),              this, SLOT(slotCompilationFinished()));
	
	// ihm
	this->setupWidget();
	this->resize(750,500);
	
	// connections
	connect(boutonRun,   SIGNAL(clicked()), this, SLOT(slotRun()));
	connect(boutonStop,  SIGNAL(clicked()), this, SLOT(slotStop()));
	connect(boutonClose, SIGNAL(clicked()), this, SLOT(slotClose()));
}

CompilationWidget::~CompilationWidget()
{
	if (boxSettings)
	{
		layout->removeWidget(boxSettings);
		boxSettings->setParent(nullptr);
	}
	
	delete m_compiler;
}






// SET PROJECT DIRECTORY //////////////////////////////////////////////////////
void CompilationWidget::setProjectDirectory(const QString &projectDir)
{
	m_projectDirectory = projectDir;
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void CompilationWidget::setupWidget()
{
	this->setWindowIcon(QIcon{":/RESOURCES/ICONES/compilation.png"});
	this->setWindowTitle("Compilator");
	this->setWindowFlags(Qt::Window);
	this->setWindowModality(Qt::ApplicationModal);
	
	// layout
	layout = new QGridLayout{this};
	this->setLayout(layout);
	
	// bas
	textEdit = new TextEdit{this};
	boutonRun = new QPushButton{"Run",this};
	boutonStop = new QPushButton{"Stop",this};
	boutonStop->setEnabled(false);
	boutonClose = new QPushButton{"Close",this};
	
	// ajout au layout
	layout->addWidget(boxSettings,0,0,1,6);
	layout->addWidget(textEdit,1,0,1,6);
	layout->addWidget(boutonRun,2,0,1,2);
	layout->addWidget(boutonStop,2,2,1,2);
	layout->addWidget(boutonClose,2,4,1,2);
}

// CLOSE EVENT ////////////////////////////////////////////////////////////////
void CompilationWidget::closeEvent(QCloseEvent *event)
{
	event->ignore();
	this->slotClose();
}

// KEY PRESS EVENT ////////////////////////////////////////////////////////////
void CompilationWidget::keyPressEvent(QKeyEvent *event)
{
	int touche = event->key();
	
	if ((touche == Qt::Key_Escape) || (touche == Qt::Key_Return) || (touche == Qt::Key_Enter))
	{
		this->slotClose();
	}
	else
	{
		QWidget::keyPressEvent(event);
	}
}






// SLOT RUN ///////////////////////////////////////////////////////////////////
void CompilationWidget::slotRun()
{
	if (!m_compiler) {return;}
	if (m_compiler->isRunning()) {return;}
	
	boutonRun->setEnabled(false);
	boutonClose->setEnabled(false);
	boutonStop->setEnabled(true);
	
	m_compiler->setCompilationDirectory(m_projectDirectory);
	m_compiler->runCompilation();
}

// SLOT STOP //////////////////////////////////////////////////////////////////
void CompilationWidget::slotStop()
{
	if (!m_compiler) {return;}
	boutonStop->setEnabled(false);
	m_compiler->stopCompilation();
	
	boutonRun->setEnabled(true);
	boutonClose->setEnabled(true);
}

// SLOT CLOSE /////////////////////////////////////////////////////////////////
void CompilationWidget::slotClose()
{
	if (m_compiler)
	{
		if (m_compiler->isRunning())
			return;
	}
	
	this->hide();
}

// SLOT COMPILATION FINISHED //////////////////////////////////////////////////
void CompilationWidget::slotCompilationFinished()
{
	boutonStop->setEnabled(false);
	boutonRun->setEnabled(true);
	boutonClose->setEnabled(true);
}

// SLOT MESSAGE ///////////////////////////////////////////////////////////////
void CompilationWidget::slotMessage(const QString &message, const QColor &color)
{
	textEdit->setTextColor(color);
	textEdit->append(message);
	textEdit->repaint();
}

