#include "VJoySettingsWidget.h"
#include "ApplicationSettings.h"
#include "MyFileDialog.h"
#include "../otherFunctions.h"
#include "VirtualJoystick.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  TAB NAME
//  BUTTON OK CLICKED
//  BUTTON CANCEL CLICKED
//  SLOT BROWSE BUTTON CLICKED
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR /////////////////////////////////////////////////////////////////////////////////////////////////
VJoySettingsWidget::VJoySettingsWidget(QWidget *parent) : AbstractSettingsWidget(parent)
{
	layout1 = new QVBoxLayout(this);
	layout2 = new QHBoxLayout;
	label = new QLabel("vJoyConfig.exe : ",this);
	line = new QLineEdit(this);
	button = new QPushButton("Browse",this);
	layout2->addWidget(label);
	layout2->addWidget(line);
	layout2->addWidget(button);
	layout1->addLayout(layout2);
	layout1->addStretch();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	line->setText(settings.property("vJoyConfigBinary").toString());
	
	connect(button,SIGNAL(clicked()),this,SLOT(slotBrowseButtonClicked()));
}





// TAB NAME ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString VJoySettingsWidget::tabName() const
{
	return "vJoy";
}

// BUTTON OK CLICKED ///////////////////////////////////////////////////////////////////////////////////////////////////////////
void VJoySettingsWidget::buttonOkClicked()
{
	ApplicationSettings& settings = ApplicationSettings::instance();
	QString exeFilePath = line->text();
	settings.setProperty("vJoyConfigBinary",exeFilePath);
	VirtualJoystick::setVJoyConfigExePath(exeFilePath);
}

// BUTTON CANCEL CLICKED ///////////////////////////////////////////////////////////////////////////////////////////////////////
void VJoySettingsWidget::buttonCancelClicked()
{
	
}

//  SLOT BROWSE BUTTON CLICKED /////////////////////////////////////////////////////////////////////////////////////////////////
void VJoySettingsWidget::slotBrowseButtonClicked()
{
	ApplicationSettings& settings = ApplicationSettings::instance();
	QString dir = dirName(settings.property("vJoyConfigBinary").toString());
	
	QString fileSelected = MyFileDialog::getOpenFileName(this,"vJoyConfig",dir,"*.exe");
	if (fileSelected == "") {return;}
	line->setText(fileSelected);
}



