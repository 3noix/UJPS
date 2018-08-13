#include "VigemSettingsWidget.h"
#include "ApplicationSettings.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QProcess>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  ADD STATUS WIDGETS
//  ADD START AUTO WHITE LISTER WIDGETS
//  ADD VIGEM CONF PAGE WIDGETS
//  ADD WHITE LIST WIDGETS
//
//  TAB NAME
//  BUTTON OK CLICKED
//  BUTTON CANCEL CLICKED
//
//  SLOT REFRESH STATUS
//  SLOT START AUTO WHITE LISTER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
VigemSettingsWidget::VigemSettingsWidget(QWidget *parent) : AbstractSettingsWidget(parent)
{
	layout1 = new QVBoxLayout{this};
	layout1->setSpacing(10);
	
	layoutStatus = new QHBoxLayout{};
	layoutStartAutoWhiteLister = new QHBoxLayout{};
	layoutVigemConfPage = new QHBoxLayout{};
	layoutWhiteList = new QHBoxLayout{};
	
	this->setLayout(layout1);
	layout1->addLayout(layoutStatus);
	layout1->addLayout(layoutStartAutoWhiteLister);
	layout1->addLayout(layoutVigemConfPage);
	layout1->addLayout(layoutWhiteList);
	layout1->addStretch();
	
	this->addStatusWidgets();
	this->addStartAutoWhiteListerWidgets();
	this->addVigemConfPageWidgets();
	this->addWhiteListWidgets();
}

VigemSettingsWidget::~VigemSettingsWidget()
{
	delete layoutStatus;
	delete layoutStartAutoWhiteLister;
	delete layoutVigemConfPage;
	delete layoutWhiteList;
}





//  ADD STATUS WIDGETS ////////////////////////////////////////////////////////
void VigemSettingsWidget::addStatusWidgets()
{
	QString strOk = "<b><font color=\"#009900\">Ready</font></b>" ;
	QString strKo = "<b><font color=\"red\">Not ready</font></b>" ;
	QString label2str = m_vigemInterface.vigemIsReady() ? strOk : strKo;
	
	label1 = new QLabel{"ViGEm status:",this};
	label2 = new QLabel{label2str,this};
	label2->setTextFormat(Qt::RichText);
	buttonRefreshStatus = new QPushButton{"Refresh",this};
	
	layoutStatus->addWidget(label1);
	layoutStatus->addWidget(label2);
	layoutStatus->addWidget(buttonRefreshStatus);
	layoutStatus->addStretch();
	
	QObject::connect(buttonRefreshStatus,&QPushButton::clicked,this,&VigemSettingsWidget::slotRefreshStatus);
}

// ADD START AUTO WHITE LISTER WIDGETS ////////////////////////////////////////
void VigemSettingsWidget::addStartAutoWhiteListerWidgets()
{
	QString labelText = "<a href=\"rien\">Start AutoWhitelister.exe</a>";
	labelStartAutoWhiteLister = new QLabel{labelText,this};
	labelStartAutoWhiteLister->setTextFormat(Qt::RichText);
	labelStartAutoWhiteLister->setTextInteractionFlags(Qt::TextBrowserInteraction);
	labelStartAutoWhiteLister->setOpenExternalLinks(false);
	
	layoutStartAutoWhiteLister->addWidget(labelStartAutoWhiteLister);
	layoutStartAutoWhiteLister->addStretch();
	
	QObject::connect(labelStartAutoWhiteLister,SIGNAL(linkActivated(QString)),this,SLOT(slotStartAutoWhiteLister()));
}

// ADD VIGEM CONF PAGE WIDGETS ////////////////////////////////////////////////
void VigemSettingsWidget::addVigemConfPageWidgets()
{
	QString labelText = "<a href=\"http://localhost:26762/\">Open ViGEm configuration page</a>";
	labelVigemConfPage = new QLabel{labelText,this};
	labelVigemConfPage->setTextFormat(Qt::RichText);
	labelVigemConfPage->setTextInteractionFlags(Qt::TextBrowserInteraction);
	labelVigemConfPage->setOpenExternalLinks(true);
	
	layoutVigemConfPage->addWidget(labelVigemConfPage);
	layoutVigemConfPage->addStretch();
}

// ADD WHITE LIST WIDGETS /////////////////////////////////////////////////////
void VigemSettingsWidget::addWhiteListWidgets()
{
	boxWhiteList = new QCheckBox{"White-list the application",this};
	layoutWhiteList->addWidget(boxWhiteList);
	layoutWhiteList->addStretch();
	
	ApplicationSettings& settings = ApplicationSettings::instance();
	bool bChecked = settings.property("bWhiteListPid").toBool();
	
	if (bChecked) {boxWhiteList->setCheckState(Qt::Checked);}
	else {boxWhiteList->setCheckState(Qt::Unchecked);}
}





// TAB NAME ///////////////////////////////////////////////////////////////////
QString VigemSettingsWidget::tabName() const
{
	return "ViGEm";
}

// BUTTON OK CLICKED //////////////////////////////////////////////////////////
void VigemSettingsWidget::buttonOkClicked()
{
	bool bWhiteList = (boxWhiteList->checkState()==Qt::Checked);
	
	// settings
	ApplicationSettings& settings = ApplicationSettings::instance();
	settings.setProperty("bWhiteListPid",bWhiteList);
	
	// white or black list the pid
	if (m_vigemInterface.vigemIsReady())
	{
		if (bWhiteList) {m_vigemInterface.whiteList(QCoreApplication::applicationPid());}
		else {m_vigemInterface.blackList(QCoreApplication::applicationPid());}
	}
}

// BUTTON CANCEL CLICKED //////////////////////////////////////////////////////
void VigemSettingsWidget::buttonCancelClicked()
{
	
}






// SLOT REFRESH STATUS ////////////////////////////////////////////////////////
void VigemSettingsWidget::slotRefreshStatus()
{
	QString strOk = "<b><font color=\"#009900\">Ready</font></b>" ;
	QString strKo = "<b><font color=\"red\">Not ready</font></b>" ;
	QString label2str = m_vigemInterface.vigemIsReady() ? strOk : strKo;
	label2->setText(label2str);
}

// SLOT START AUTO WHITE LISTER ///////////////////////////////////////////////
void VigemSettingsWidget::slotStartAutoWhiteLister()
{
	QString autoWhiteListerExe = QCoreApplication::applicationDirPath() + "/../../HidingJoysticks/ViGEm/AutoWhitelister.exe";
	QProcess::startDetached(autoWhiteListerExe);
}


