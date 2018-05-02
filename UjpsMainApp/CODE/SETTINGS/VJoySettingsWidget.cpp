#include "VJoySettingsWidget.h"
#include "ApplicationSettings.h"
#include "MyFileDialog.h"
#include "../otherFunctions.h"
#include "VirtualJoystick.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>


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
	layout2 = new QHBoxLayout;
	checkBox = new QCheckBox("Use vJoyConfig.exe",this);
	label = new QLabel("vJoyConfig.exe : ",this);
	line = new QLineEdit(this);
	button = new QPushButton("Browse",this);
	layout2->addWidget(label);
	layout2->addWidget(line);
	layout2->addWidget(button);
	layout1->addWidget(checkBox);
	layout1->addLayout(layout2);
	layout1->addStretch();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	bool bUseVJoyConfigBinary = settings.property("bUseVJoyConfigBinary").toBool();
	Qt::CheckState st = Qt::Checked;
	if (!bUseVJoyConfigBinary) {st = Qt::Unchecked;}
	checkBox->setCheckState(st);
	this->slotCheckBoxStateChanged(st);
	line->setText(settings.property("vJoyConfigBinary").toString());
	
	connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(slotCheckBoxStateChanged(int)));
	connect(button,SIGNAL(clicked()),this,SLOT(slotBrowseButtonClicked()));
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
	bool bUseVJoyConfigBinary = (checkBox->checkState() == Qt::Checked);
	QString exeFilePath = line->text();
	
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
	label->setEnabled(bEnable);
	line->setEnabled(bEnable);
	button->setEnabled(bEnable);
	
}

// SLOT BROWSE BUTTON CLICKED /////////////////////////////////////////////////
void VJoySettingsWidget::slotBrowseButtonClicked()
{
	ApplicationSettings& settings = ApplicationSettings::instance();
	QString dir = dirName(settings.property("vJoyConfigBinary").toString());
	
	QString fileSelected = MyFileDialog::getOpenFileName(this,"vJoyConfig",dir,"*.exe");
	if (fileSelected == "") {return;}
	line->setText(fileSelected);
}



