#include "ConnectionWidget.h"
#include <QtWidgets>

#include <QHostInfo>
#include <QNetworkInterface>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  SETUP WIDGET
//  FIND CLASSICAL HOSTS
//
//  SLOT CONNECT
//  SLOT ERROR
//
//  SET CONNECTING
//  SET CONNECTED
//  SET DISCONNECTED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
ConnectionWidget::ConnectionWidget(QWidget *parent) : QWidget(parent)
{
	this->setupWidget();
	connect(m_connectButton, &QAbstractButton::clicked, this, &ConnectionWidget::slotConnect);
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void ConnectionWidget::setupWidget()
{
	QStringList hosts = ConnectionWidget::findClassicalHosts();
	
	// create widgets
	m_hostCombo = new QComboBox(this);
	m_hostCombo->setEditable(true);
	m_hostCombo->addItems(hosts);
	m_portLineEdit = new QLineEdit(this);
	m_portLineEdit->setValidator(new QIntValidator(1,65535,this));
	m_portLineEdit->setText("32241");
	m_hostLabel = new QLabel("Server name:",this);
	m_portLabel = new QLabel("Server port:",this);
	m_connectButton = new QPushButton("Connect",this);
	
	// add widgets in the layout
	m_layout = new QHBoxLayout(this);
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
	if (name != QLatin1String("localhost")) {hosts << "localhost";}
	// find out IP addresses of this machine
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (const QHostAddress &ha : ipAddressesList) {if (!ha.isLoopback()) {hosts << ha.toString();}} // add non-localhost addresses first
	for (const QHostAddress &ha : ipAddressesList) {if (ha.isLoopback()) {hosts << ha.toString();}} // add localhost addresses afterwards
	
	return hosts;
}





// SLOT CONNECT ///////////////////////////////////////////////////////////////
void ConnectionWidget::slotConnect()
{
	emit connectionRequest(m_hostCombo->currentText(),m_portLineEdit->text().toInt());
}

// SLOT ERROR /////////////////////////////////////////////////////////////////
void ConnectionWidget::slotError(QString text)
{
	QMessageBox::information(this, "Client window", text);
}






// SET CONNECTING /////////////////////////////////////////////////////////////
void ConnectionWidget::setConnecting()
{
	this->show();
	m_connectButton->setEnabled(false);
}

// SET CONNECTED //////////////////////////////////////////////////////////////
void ConnectionWidget::setConnected()
{
	this->hide();
	m_connectButton->setEnabled(true);
}

// SET DISCONNECTED ///////////////////////////////////////////////////////////
void ConnectionWidget::setDisconnected()
{
	this->show();
	m_connectButton->setEnabled(true);
}

