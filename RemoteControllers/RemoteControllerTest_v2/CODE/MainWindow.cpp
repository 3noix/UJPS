#include "MainWindow.h"
#include <QtWidgets>

#include <QHostInfo>
#include <QNetworkInterface>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  SETUP WIDGET
//  FIND CLASSICAL HOSTS
//
//  SLOT CONNECT
//  SLOT DISCONNECT
//  SLOT SET DATA
//  SLOT SET STATE
//  SLOT ERROR
//
//  SLOT SLIDER VALUE CHANGED
//  SLOT BUTTON 1 PRESSED
//  SLOT BUTTON 2 PRESSED
//  SLOT BUTTON 1 RELEASED
//  SLOT BUTTON 2 RELEASED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	this->setupWidget();
	this->setWindowTitle(QGuiApplication::applicationDisplayName());
	this->slotSetState(AbstractRemoteJoystickClient::State::NotConnected);
	
	connect(m_connectButton, &QAbstractButton::clicked, this, &MainWindow::slotConnect);
	connect(m_disconnectButton, &QAbstractButton::clicked, this, &MainWindow::slotDisconnect);
	
	connect(&m_client, &AbstractRemoteJoystickClient::stateChanged, this, &MainWindow::slotSetState);
	connect(&m_client, &AbstractRemoteJoystickClient::error, this, &MainWindow::slotError);
	connect(&m_client, &RemoteJoystickClient::signalSetData, this, &MainWindow::slotSetData);
	
	connect(m_slider, &QSlider::valueChanged, this, &MainWindow::slotSliderValueChanged);
	connect(m_button1, &QPushButton::pressed, this, &MainWindow::slotButton1Pressed);
	connect(m_button2, &QPushButton::pressed, this, &MainWindow::slotButton2Pressed);
	connect(m_button1, &QPushButton::released, this, &MainWindow::slotButton1Released);
	connect(m_button2, &QPushButton::released, this, &MainWindow::slotButton2Released);
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	QStringList hosts = MainWindow::findClassicalHosts();
	
	// create widgets
	m_hostCombo = new QComboBox(this);
	m_hostCombo->setEditable(true);
	m_hostCombo->addItems(hosts);
	m_portLineEdit = new QLineEdit(this);
	m_portLineEdit->setValidator(new QIntValidator(1,65535,this));
	m_portLineEdit->setText("32241");
	m_hostLabel = new QLabel("Server name:",this);
	m_portLabel = new QLabel("Server port:",this);
	m_statusLabel = new QLabel("Not connected",this);
	m_connectButton = new QPushButton("Connect",this);
	m_disconnectButton = new QPushButton("Disconnect",this);
	
	m_box = new QGroupBox("Controls",this);
	m_layout2 = new QGridLayout(m_box);
	m_box->setLayout(m_layout2);
	m_slider = new QSlider(this);
	m_slider->setMinimum(-10000);
	m_slider->setMaximum(10000);
	m_slider->setOrientation(Qt::Horizontal);
	m_button1 = new QPushButton("Button 1",this);
	m_button2 = new QPushButton("Button 2",this);
	m_button3 = new QPushButton("Button 3",this);
	m_layout2->addWidget(m_slider,0,0,1,3);
	m_layout2->addWidget(m_button1,1,0,1,1);
	m_layout2->addWidget(m_button2,1,1,1,1);
	m_layout2->addWidget(m_button3,1,2,1,1);
	
	// add widgets in the layout
	m_mainLayout = new QGridLayout(this);
	m_mainLayout->addWidget(m_hostLabel,0,0,1,1);
	m_mainLayout->addWidget(m_hostCombo,0,1,1,2);
	m_mainLayout->addWidget(m_portLabel,1,0,1,1);
	m_mainLayout->addWidget(m_portLineEdit,1,1,1,2);
	m_mainLayout->addWidget(m_connectButton,2,0,1,1);
	m_mainLayout->addWidget(m_disconnectButton,2,1,1,1);
	m_mainLayout->addWidget(m_statusLabel,2,2,1,1);
	m_mainLayout->addWidget(m_box,3,0,1,3);
}

// FIND CLASSICAL HOSTS ///////////////////////////////////////////////////////
QStringList MainWindow::findClassicalHosts()
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
void MainWindow::slotConnect()
{
	m_client.slotConnect(m_hostCombo->currentText(),m_portLineEdit->text().toInt());
}

// SLOT DISCONNECT ////////////////////////////////////////////////////////////
void MainWindow::slotDisconnect()
{
	m_client.slotDisconnect();
}

// SLOT SET DATA //////////////////////////////////////////////////////////////
void MainWindow::slotSetData(const QString &prop, QVariant data)
{
	if (prop == "button3")
	{
		bool b = data.toBool();
		m_button3->setDown(b);
	}
}

// SLOT SET STATE /////////////////////////////////////////////////////////////
void MainWindow::slotSetState(AbstractRemoteJoystickClient::State s)
{
	if (s == AbstractRemoteJoystickClient::State::NotConnected)
	{
		m_connectButton->setEnabled(true);
		m_disconnectButton->setEnabled(false);
		m_statusLabel->setText("Not connected");
	}
	else if (s == AbstractRemoteJoystickClient::State::Connecting)
	{
		m_connectButton->setEnabled(false);
		m_disconnectButton->setEnabled(false);
		m_statusLabel->setText("Connecting");
	}
	else if (s == AbstractRemoteJoystickClient::State::Connected)
	{
		m_connectButton->setEnabled(false);
		m_disconnectButton->setEnabled(true);
		m_statusLabel->setText("Connected");
		
		// initialisation du slider
		float f = ((float)m_slider->value()) / 10000.0f;
		m_client.slotSendAxisInfo(0,f);
	}
	else
	{
		m_connectButton->setEnabled(true);
		m_disconnectButton->setEnabled(true);
		m_statusLabel->setText("Unknown state");
	}
}

// SLOT ERROR /////////////////////////////////////////////////////////////////
void MainWindow::slotError(QString text)
{
	QMessageBox::information(this, "Client window", text);
}





// SLOT SLIDER VALUE CHANGED //////////////////////////////////////////////////
void MainWindow::slotSliderValueChanged(int value)
{
	float f = ((float)value) / 10000.0f;
	m_client.slotSendAxisInfo(0,f);
}

// SLOT BUTTON 1 PRESSED //////////////////////////////////////////////////////
void MainWindow::slotButton1Pressed()
{
	m_client.slotSendButtonInfo(0,true);
}

// SLOT BUTTON 2 PRESSED //////////////////////////////////////////////////////
void MainWindow::slotButton2Pressed()
{
	m_client.slotSendButtonInfo(1,true);
}

// SLOT BUTTON 1 RELEASED /////////////////////////////////////////////////////
void MainWindow::slotButton1Released()
{
	m_client.slotSendButtonInfo(0,false);
}

// SLOT BUTTON 2 RELEASED /////////////////////////////////////////////////////
void MainWindow::slotButton2Released()
{
	m_client.slotSendButtonInfo(1,false);
}


