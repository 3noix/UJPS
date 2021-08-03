#include "ConnectionWidget.h"
#include <QHostInfo>
#include <QNetworkInterface>

#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include <QCoreApplication>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  SETUP WIDGET
//  FIND CLASSICAL HOSTS
//
//  CLOSE EVENT
//  SLOT CONNECT
//  SET CONNECTING
//  SET CONNECTED
//  SET DISCONNECTED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
ConnectionWidget::ConnectionWidget(QWidget *parent) : QWidget{parent}
{
	this->setupWidget();
	this->setWindowModality(Qt::ApplicationModal);
	QObject::connect(m_connectButton, &QAbstractButton::clicked, this, &ConnectionWidget::slotConnect);
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void ConnectionWidget::setupWidget()
{
	QStringList hosts = ConnectionWidget::findClassicalHosts();
	
	// create widgets
	m_hostCombo = new QComboBox{this};
	m_hostCombo->setEditable(true);
	m_hostCombo->addItems(hosts);
	m_portLineEdit = new QLineEdit{this};
	m_portLineEdit->setValidator(new QIntValidator{1,65535,this});
	m_portLineEdit->setText("32241");
	m_hostLabel = new QLabel{"Server name:",this};
	m_portLabel = new QLabel{"Server port:",this};
	m_connectButton = new QPushButton{"Connect",this};
	
	// add widgets in the layout
	m_layout = new QHBoxLayout{this};
	m_layout->addWidget(m_hostLabel);
	m_layout->addWidget(m_hostCombo);
	m_layout->addWidget(m_portLabel);
	m_layout->addWidget(m_portLineEdit);
	m_layout->addWidget(m_connectButton);
}

// FIND CLASSICAL HOSTS ///////////////////////////////////////////////////////
QStringList ConnectionWidget::findClassicalHosts()
{
	// find standard hosts
	// find out name of this machine
	QStringList hosts;
	QString name = QHostInfo::localHostName();
	if (!name.isEmpty())
	{
		hosts << name;
		QString domain = QHostInfo::localDomainName();
		if (!domain.isEmpty()) {hosts << name + "." + domain;}
	}
	if (name != QLatin1String{"localhost"}) {hosts << "localhost";}
	// find out IP addresses of this machine
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (const QHostAddress &ha : ipAddressesList) {if (!ha.isLoopback()) {hosts << ha.toString();}} // add non-localhost addresses first
	for (const QHostAddress &ha : ipAddressesList) {if (ha.isLoopback()) {hosts << ha.toString();}} // add localhost addresses afterwards
	
	return hosts;
}






// CLOSE EVENT ////////////////////////////////////////////////////////////////
void ConnectionWidget::closeEvent(QCloseEvent *event)
{
	event->accept();
	qApp->quit();
}

// SLOT CONNECT ///////////////////////////////////////////////////////////////
void ConnectionWidget::slotConnect()
{
	emit connectionRequest(m_hostCombo->currentText(),m_portLineEdit->text().toInt());
}

// SET CONNECTING /////////////////////////////////////////////////////////////
void ConnectionWidget::setConnecting()
{
	m_connectButton->setEnabled(false);
}

// SET CONNECTED //////////////////////////////////////////////////////////////
void ConnectionWidget::setConnected()
{
	m_connectButton->setEnabled(false);
}

// SET DISCONNECTED ///////////////////////////////////////////////////////////
void ConnectionWidget::setDisconnected()
{
	m_connectButton->setEnabled(true);
}

