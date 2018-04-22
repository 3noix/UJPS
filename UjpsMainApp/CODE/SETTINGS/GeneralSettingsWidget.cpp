#include "GeneralSettingsWidget.h"
#include "ApplicationSettings.h"
#include "../XML/GenericPropertiesInfo.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  ADD DEFAULT DIR WIDGETS
//
//  TAB NAME
//  BUTTON OK CLICKED
//  BUTTON CANCEL CLICKED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GeneralSettingsWidget::GeneralSettingsWidget(QWidget *parent) : AbstractSettingsWidget(parent)
{
	layout1 = new QVBoxLayout(this);
	layout2 = new QHBoxLayout();
	this->setLayout(layout1);
	layout1->addLayout(layout2);
	layout1->addStretch();
	
	this->addDefaultDirWidgets();
}

GeneralSettingsWidget::~GeneralSettingsWidget()
{
	delete layout2;
}





// ADD DEFAULT DIR WIDGETS ////////////////////////////////////////////////////
void GeneralSettingsWidget::addDefaultDirWidgets()
{
	labelDefDir = new QLabel("Profiles default directory:",this);
	radioDefDirPrevious = new QRadioButton("Previous",this);
	radioDefDirFixed = new QRadioButton("Fixed",this);
	radioDefDirGroup = new QButtonGroup(this);
	radioDefDirGroup->addButton(radioDefDirPrevious);
	radioDefDirGroup->addButton(radioDefDirFixed);
	lineDefDir = new QLineEdit(this);
	
	layout2->addWidget(labelDefDir);
	layout2->addWidget(radioDefDirPrevious);
	layout2->addWidget(radioDefDirFixed);
	layout2->addWidget(lineDefDir);
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	QStringList list = GenericPropertiesInfo::qvariant2qstringlist(settings.property("defaultDirectory"));
	if (list.size() == 2)
	{
		if (list[0] == "Previous") {radioDefDirPrevious->setChecked(true);}
		else {radioDefDirFixed->setChecked(true);}
		
		lineDefDir->setText(list[1]);
	}
	else
	{
		radioDefDirFixed->setChecked(true);
	}
}



// TAB NAME ///////////////////////////////////////////////////////////////////
QString GeneralSettingsWidget::tabName() const
{
	return "General";
}

// BUTTON OK CLICKED //////////////////////////////////////////////////////////
void GeneralSettingsWidget::buttonOkClicked()
{
	ApplicationSettings& settings = ApplicationSettings::instance();
	
	// default directory
	QVariant mode = QString("Fixed");
	if (radioDefDirPrevious->isChecked()) {mode = QString("Previous");}
	QVariant path = lineDefDir->text().replace("\\","/");
	QList<QVariant> vlist;
	vlist << mode << path;
	settings.setProperty("defaultDirectory",QVariant(vlist));
}

// BUTTON CANCEL CLICKED //////////////////////////////////////////////////////
void GeneralSettingsWidget::buttonCancelClicked()
{
	
}

