#include "SettingsDialog.h"
#include "ApplicationSettings.h"
#include "AbstractSettingsWidget.h"

#include <QGridLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QCloseEvent>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//
//  SLOT BOUTON OK
//  SLOT BOUTON CANCEL
//  SETUP WIDGET
//  CLOSE EVENT
//  KEY PRESS EVENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
SettingsDialog::SettingsDialog(QWidget *parent) : QDialog{parent}
{
	this->setWindowTitle("Application settings");
	this->setWindowIcon(QIcon{":/icons/outils.png"});
	this->setWindowModality(Qt::WindowModal);
	
	this->setupWidget();
	this->resize(500,350);
	
	QObject::connect(boutonOk,     SIGNAL(clicked()), this, SLOT(slotBoutonOk()));
	QObject::connect(boutonCancel, SIGNAL(clicked()), this, SLOT(slotBoutonCancel()));
}






// SLOT BOUTON OK /////////////////////////////////////////////////////////////
void SettingsDialog::slotBoutonOk()
{
	for (AbstractSettingsWidget *w : settingsWidgets) {w->buttonOkClicked();}
	ApplicationSettings& settings = ApplicationSettings::instance();
	settings.writeFile();
	this->accept();
}

// SLOT BOUTON CANCEL /////////////////////////////////////////////////////////
void SettingsDialog::slotBoutonCancel()
{
	for (AbstractSettingsWidget *w : settingsWidgets) {w->buttonCancelClicked();}
	this->reject();
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void SettingsDialog::setupWidget()
{
	layout = new QGridLayout{this};
	this->setLayout(layout);
	
	tabs = new QTabWidget{this};
	boutonOk = new QPushButton{"Ok",this};
	boutonCancel = new QPushButton{"Cancel",this};
	
	layout->addWidget(tabs,0,0,1,2);
	layout->addWidget(boutonOk,1,0,1,1);
	layout->addWidget(boutonCancel,1,1,1,1);
}

// ADD SETTINGS WIDGET ////////////////////////////////////////////////////////
void SettingsDialog::addSettingsWidget(AbstractSettingsWidget *w)
{
	settingsWidgets.append(w);
	tabs->addTab(w,w->tabName());
}

// CLOSE EVENT ////////////////////////////////////////////////////////////////
void SettingsDialog::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event)
	this->slotBoutonCancel();
}

// KEY PRESS EVENT ////////////////////////////////////////////////////////////
void SettingsDialog::keyPressEvent(QKeyEvent *event)
{
	int touche = event->key();
	if (touche == Qt::Key_Escape)
	{
		this->slotBoutonCancel();
	}
	else if ((touche == Qt::Key_Return) || (touche == Qt::Key_Enter))
	{
		this->slotBoutonOk();
	}
	else
	{
		QWidget::keyPressEvent(event);
	}
}

