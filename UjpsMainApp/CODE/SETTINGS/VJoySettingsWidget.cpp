#include "VJoySettingsWidget.h"
#include "ApplicationSettings.h"
#include "../otherFunctions.h"
#include "VirtualJoystick.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>
#include <QFileDialog>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  TAB NAME
//  BUTTON OK CLICKED
//  BUTTON CANCEL CLICKED
//
//  SLOT CHECK BOX STATE CHANGED
//  SLOT BROWSE BUTTON CLICKED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
VJoySettingsWidget::VJoySettingsWidget(QWidget *parent) : AbstractSettingsWidget(parent)
{
	layout1 = new QVBoxLayout(this);
	layoutVjoyConfigExe = new QHBoxLayout;
	
	boxVjoyConfigExe = new QCheckBox("Use vJoyConfig.exe",this);
	lineVjoyConfigExe = new QLineEdit(this);
	buttonVjoyConfigExe = new QPushButton("Browse",this);
	
	layoutVjoyConfigExe->addWidget(boxVjoyConfigExe);
	layoutVjoyConfigExe->addWidget(lineVjoyConfigExe);
	layoutVjoyConfigExe->addWidget(buttonVjoyConfigExe);
	layout1->addLayout(layoutVjoyConfigExe);
	layout1->addStretch();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	bool bUseVJoyConfigBinary = settings.property("bUseVJoyConfigBinary").toBool();
	Qt::CheckState st = Qt::Checked;
	if (!bUseVJoyConfigBinary) {st = Qt::Unchecked;}
	boxVjoyConfigExe->setCheckState(st);
	this->slotCheckBoxStateChanged(st);
	lineVjoyConfigExe->setText(settings.property("vJoyConfigBinary").toString());
	
	connect(boxVjoyConfigExe,SIGNAL(stateChanged(int)),this,SLOT(slotCheckBoxStateChanged(int)));
	connect(buttonVjoyConfigExe,SIGNAL(clicked()),this,SLOT(slotBrowseButtonClicked()));
}





// TAB NAME ///////////////////////////////////////////////////////////////////
QString VJoySettingsWidget::tabName() const
{
	return "vJoy";
}

// BUTTON OK CLICKED //////////////////////////////////////////////////////////
void VJoySettingsWidget::buttonOkClicked()
{
	ApplicationSettings& settings = ApplicationSettings::instance();
	bool bUseVJoyConfigBinary = (boxVjoyConfigExe->checkState() == Qt::Checked);
	QString exeFilePath = lineVjoyConfigExe->text();
	
	settings.setProperty("bUseVJoyConfigBinary",bUseVJoyConfigBinary);
	settings.setProperty("vJoyConfigBinary",exeFilePath);
	VirtualJoystick::setVJoyConfigOptions(bUseVJoyConfigBinary,exeFilePath);
}

// BUTTON CANCEL CLICKED //////////////////////////////////////////////////////
void VJoySettingsWidget::buttonCancelClicked()
{
	
}





// SLOT CHECK BOX STATE CHANGED ///////////////////////////////////////////////
void VJoySettingsWidget::slotCheckBoxStateChanged(int state)
{
	bool bEnable = (state == Qt::Checked);
	lineVjoyConfigExe->setEnabled(bEnable);
	buttonVjoyConfigExe->setEnabled(bEnable);
	
}

// SLOT BROWSE BUTTON CLICKED /////////////////////////////////////////////////
void VJoySettingsWidget::slotBrowseButtonClicked()
{
	ApplicationSettings& settings = ApplicationSettings::instance();
	QString dir = dirName(settings.property("vJoyConfigBinary").toString());
	
	QString fileSelected = QFileDialog::getOpenFileName(this,"vJoyConfig",dir,"*.exe");
	if (fileSelected == "") {return;}
	lineVjoyConfigExe->setText(fileSelected);
}



