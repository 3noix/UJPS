#include "GeneralSettingsWidget.h"
#include "Settings/ApplicationSettings.h"
#include "Settings/otherFunctions.h"
#include "UjpsCore/VirtualEventsQueue.h"

#include <QJsonArray>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include <QFileDialog>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  ADD DEFAULT DIR WIDGETS
//  ADD STARTING PROFILE WIDGETS
//  ADD DEFAULT TIME STEP WIDGETS
//  ADD INPUT REPEATER WIDGET
//
//  TAB NAME
//  BUTTON OK CLICKED
//  BUTTON CANCEL CLICKED
//
//  SLOT STARTING PROFILE STATE CHANGED
//  SLOT STARTING PROFILE BROWSE
//  SLOT DEFAULT TIME STEP STATE CHANGED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GeneralSettingsWidget::GeneralSettingsWidget(QWidget *parent) : AbstractSettingsWidget{parent}
{
	layout1 = new QVBoxLayout{this};
	layout1->setSpacing(10);
	
	layoutDefDir = new QHBoxLayout{};
	layoutStartingProfile = new QHBoxLayout{};
	layoutDefTimeStep = new QHBoxLayout{};
	layoutInputRepeater = new QHBoxLayout{};
	
	this->setLayout(layout1);
	layout1->addLayout(layoutDefDir);
	layout1->addLayout(layoutStartingProfile);
	layout1->addLayout(layoutDefTimeStep);
	layout1->addLayout(layoutInputRepeater);
	layout1->addStretch();
	
	this->addDefaultDirWidgets();
	this->addStartingProfileWidgets();
	this->addDefaultTimeStepWidget();
	this->addInputRepeaterWidget();
}

GeneralSettingsWidget::~GeneralSettingsWidget()
{
	delete layoutDefDir;
	delete layoutStartingProfile;
	delete layoutDefTimeStep;
	delete layoutInputRepeater;
}





// ADD DEFAULT DIR WIDGETS ////////////////////////////////////////////////////
void GeneralSettingsWidget::addDefaultDirWidgets()
{
	labelDefDir = new QLabel{"Profiles default directory:",this};
	radioDefDirPrevious = new QRadioButton{"Previous",this};
	radioDefDirFixed = new QRadioButton{"Fixed",this};
	radioDefDirGroup = new QButtonGroup{this};
	radioDefDirGroup->addButton(radioDefDirPrevious);
	radioDefDirGroup->addButton(radioDefDirFixed);
	lineDefDir = new QLineEdit{this};
	
	layoutDefDir->addWidget(labelDefDir);
	layoutDefDir->addWidget(radioDefDirPrevious);
	layoutDefDir->addWidget(radioDefDirFixed);
	layoutDefDir->addWidget(lineDefDir);
	
	QJsonObject &settings = ApplicationSettings::getSettings();
	QJsonArray array = settings["defaultDirectory"].toArray();
	if (array.size() == 2)
	{
		if (array[0].toString() == "Previous") {radioDefDirPrevious->setChecked(true);}
		else {radioDefDirFixed->setChecked(true);}
		
		lineDefDir->setText(array[1].toString());
	}
	else
	{
		radioDefDirFixed->setChecked(true);
	}
}

// ADD STARTING PROFILE WIDGETS ///////////////////////////////////////////////
void GeneralSettingsWidget::addStartingProfileWidgets()
{
	boxUseStartingProfile = new QCheckBox{"Default profile: ",this};
	lineStartingProfile = new QLineEdit{this};
	buttonStartingProfile = new QPushButton{"Browse",this};
	
	QObject::connect(boxUseStartingProfile, &QCheckBox::stateChanged, this, &GeneralSettingsWidget::slotStartingProfileStateChanged);
	QObject::connect(buttonStartingProfile, &QPushButton::clicked,    this, &GeneralSettingsWidget::slotStartingProfileBrowse);
	
	layoutStartingProfile->addWidget(boxUseStartingProfile);
	layoutStartingProfile->addWidget(lineStartingProfile);
	layoutStartingProfile->addWidget(buttonStartingProfile);
	
	QJsonObject &settings = ApplicationSettings::getSettings();
	bool bEnable = settings["bUseStartingProfilePath"].toBool();
	QString startingProfile = settings["startingProfilePath"].toString();
	
	if (bEnable) {boxUseStartingProfile->setCheckState(Qt::Checked);}
	else {boxUseStartingProfile->setCheckState(Qt::Unchecked);}
	lineStartingProfile->setText(startingProfile);
	lineStartingProfile->setEnabled(bEnable);
	buttonStartingProfile->setEnabled(bEnable);
}

// ADD DEFAULT TIME STEP WIDGETS //////////////////////////////////////////////
void GeneralSettingsWidget::addDefaultTimeStepWidget()
{
	checkboxDefTimeStep = new QCheckBox{"Default time step:",this};
	spinboxDefTimeStep = new QSpinBox{this};
	spinboxDefTimeStep->setMinimum(5);
	spinboxDefTimeStep->setMaximum(500);
	spinboxDefTimeStep->setValue(15);
	spinboxDefTimeStep->setSingleStep(1);
	spinboxDefTimeStep->setSuffix(" ms");
	
	QObject::connect(checkboxDefTimeStep, &QCheckBox::stateChanged, this, &GeneralSettingsWidget::slotDefaultTimeStepStateChanged);
	
	layoutDefTimeStep->addWidget(checkboxDefTimeStep);
	layoutDefTimeStep->addWidget(spinboxDefTimeStep);
	layoutDefTimeStep->addStretch();
	
	QJsonObject &settings = ApplicationSettings::getSettings();
	bool bEnable = settings["bUseDefaultTimeStep"].toBool();
	int defaultTimeStep = settings["defaultTimeStep"].toInt();
	
	if (bEnable) {checkboxDefTimeStep->setCheckState(Qt::Checked);}
	else {checkboxDefTimeStep->setCheckState(Qt::Unchecked);}
	if (defaultTimeStep < 5 || defaultTimeStep > 500) {spinboxDefTimeStep->setValue(15);}
	else {spinboxDefTimeStep->setValue(defaultTimeStep);}
	spinboxDefTimeStep->setEnabled(bEnable);
}

// ADD INPUT REPEATER WIDGET //////////////////////////////////////////////////
void GeneralSettingsWidget::addInputRepeaterWidget()
{
	checkboxInputRepeater = new QCheckBox{"Enable input repeater",this};
	
	bool bEnable = VirtualEventsQueue::isInputRepeaterEnabled();
	if (bEnable) {checkboxInputRepeater->setCheckState(Qt::Checked);}
	else {checkboxInputRepeater->setCheckState(Qt::Unchecked);}
	
	layoutInputRepeater->addWidget(checkboxInputRepeater);
	layoutInputRepeater->addStretch();
}






// TAB NAME ///////////////////////////////////////////////////////////////////
QString GeneralSettingsWidget::tabName() const
{
	return "General";
}

// BUTTON OK CLICKED //////////////////////////////////////////////////////////
void GeneralSettingsWidget::buttonOkClicked()
{
	QJsonObject &settings = ApplicationSettings::getSettings();
	
	// default directory
	QString mode = (radioDefDirPrevious->isChecked() ? "Previous" : "Fixed");
	QString path = lineDefDir->text().replace("\\","/");
	QJsonArray array{mode,path};
	settings["defaultDirectory"] = array;
	
	// starting profile
	settings["bUseStartingProfilePath"] = (boxUseStartingProfile->checkState() == Qt::Checked);
	settings["startingProfilePath"] = lineStartingProfile->text();
	
	// default time step
	settings["bUseDefaultTimeStep"] = (checkboxDefTimeStep->checkState() == Qt::Checked);
	settings["defaultTimeStep"] = spinboxDefTimeStep->value();
	
	// output repeater
	VirtualEventsQueue::setInputRepeaterEnabled(checkboxInputRepeater->checkState()==Qt::Checked);
}

// BUTTON CANCEL CLICKED //////////////////////////////////////////////////////
void GeneralSettingsWidget::buttonCancelClicked()
{
}






// SLOT STARTING PROFILE STATE CHANGED ////////////////////////////////////////
void GeneralSettingsWidget::slotStartingProfileStateChanged(int checkState)
{
	bool bEnable = (checkState == Qt::Checked);
	lineStartingProfile->setEnabled(bEnable);
	buttonStartingProfile->setEnabled(bEnable);
}

// SLOT STARTING PROFILE BROWSE ///////////////////////////////////////////////
void GeneralSettingsWidget::slotStartingProfileBrowse()
{
	QJsonObject& settings = ApplicationSettings::getSettings();
	QString dir = dirName(settings["startingProfilePath"].toString());
	
	QString fileSelected = QFileDialog::getOpenFileName(this,"Starting profile path",dir,"*.pro");
	if (fileSelected == "") {return;}
	lineStartingProfile->setText(fileSelected);
}

// SLOT DEFAULT TIME STEP STATE CHANGED ///////////////////////////////////////
void GeneralSettingsWidget::slotDefaultTimeStepStateChanged(int checkState)
{
	bool bEnable = (checkState == Qt::Checked);
	spinboxDefTimeStep->setEnabled(bEnable);
}

