#include "MainWindow.h"
#include "RemoteJoystickMessageTypes.h"

#include <QtWidgets>
#include <QtNetwork>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  SETUP WIDGET
//  SET STATE
//
//  SLOT SESSION OPENED
//  SLOT CONNECT
//  SLOT CONNECTED
//  SLOT RECEIVE DATA
//  SLOT DISCONNECT
//  SLOT DISCONNECTED
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
	m_tcpSocket = new QTcpSocket{this};
	m_networkSession = nullptr;
	
	// travail sur les widgets
	this->setupWidget();
	connect(m_slider, &QSlider::valueChanged, this, &MainWindow::slotSliderValueChanged);
	connect(m_button1, &QPushButton::pressed, this, &MainWindow::slotButton1Pressed);
	connect(m_button2, &QPushButton::pressed, this, &MainWindow::slotButton2Pressed);
	connect(m_button1, &QPushButton::released, this, &MainWindow::slotButton1Released);
	connect(m_button2, &QPushButton::released, this, &MainWindow::slotButton2Released);
	
	this->setWindowTitle(QGuiApplication::applicationDisplayName());
	this->setState(State::Init);
	
	// connections
	connect(m_connectButton, &QAbstractButton::clicked, this, &MainWindow::slotConnect);
	connect(m_disconnectButton, &QAbstractButton::clicked, this, &MainWindow::slotDisconnect);
	connect(m_tcpSocket, &QTcpSocket::connected, this, &MainWindow::slotConnected);
	connect(m_tcpSocket, &QTcpSocket::disconnected, this, &MainWindow::slotDisconnected);
	connect(m_tcpSocket, &QIODevice::readyRead, this, &MainWindow::slotReceiveData);
	typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
	connect(m_tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &MainWindow::slotError);
	
	// configuration du client
	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
	{
		// Get saved network configuration
		QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();
		
		// If the saved network configuration is not currently discovered use the system default
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
			config = manager.defaultConfiguration();
		
		m_networkSession = new QNetworkSession(config, this);
		connect(m_networkSession, &QNetworkSession::opened, this, &MainWindow::slotSessionOpened);
		m_networkSession->open();
	}
	else
	{
		this->setState(State::NotConnected);
	}
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
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

// SET STATE //////////////////////////////////////////////////////////////////
void MainWindow::setState(State s)
{
	bool bSessionOk = (!m_networkSession || m_networkSession->isOpen());
	
	if (!bSessionOk || s == State::Init)
	{
		m_connectButton->setEnabled(false);
		m_disconnectButton->setEnabled(false);
		m_statusLabel->setText("Init or session pb");
	}
	else if (s == State::NotConnected)
	{
		m_connectButton->setEnabled(true);
		m_disconnectButton->setEnabled(false);
		m_statusLabel->setText("Not connected");
	}
	else if (s == State::Connecting)
	{
		m_connectButton->setEnabled(false);
		m_disconnectButton->setEnabled(false);
		m_statusLabel->setText("Connecting");
	}
	else if (s == State::Connected)
	{
		m_connectButton->setEnabled(false);
		m_disconnectButton->setEnabled(true);
		m_statusLabel->setText("Connected");
	}
	else
	{
		m_connectButton->setEnabled(true);
		m_disconnectButton->setEnabled(true);
		m_statusLabel->setText("Unknown state");
	}
}







// SLOT SESSION OPENED ////////////////////////////////////////////////////////
void MainWindow::slotSessionOpened()
{
	// Save the used configuration
	QNetworkConfiguration config = m_networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
		id = m_networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	else
		id = config.identifier();
	
	QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();
	this->setState(State::NotConnected);
}

// SLOT CONNECT ///////////////////////////////////////////////////////////////
void MainWindow::slotConnect()
{
	m_tcpSocket->abort();
	m_tcpSocket->connectToHost(m_hostCombo->currentText(),m_portLineEdit->text().toInt());
	this->setState(State::Connecting);
}

// SLOT CONNECTED /////////////////////////////////////////////////////////////
void MainWindow::slotConnected()
{
	this->setState(State::Connected);
	
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	m_tcpSocket->flush();
	quint8 nbButtons = 2;
	QStringList buttonsNames{"B1","B2"};
	quint8 nbAxes = 1;
	QStringList axesNames{"A1"};
	out << quint16{0} << RemoteJoystickMessageType::Init << QString{"TouchScreen2"} << nbButtons << buttonsNames << nbAxes << axesNames;
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT RECEIVE DATA //////////////////////////////////////////////////////////
void MainWindow::slotReceiveData()
{
	QDataStream in{m_tcpSocket};
	in.setVersion(QDataStream::Qt_5_7);
	in.startTransaction();
	
	QString prop;
	QVariant data;
	in >> prop >> data;
	if (!in.commitTransaction()) {return;}
	
	if (prop == "button3")
	{
		bool b = data.toBool();
		m_button3->setDown(b);
	}
}

// SLOT DISCONNECT ////////////////////////////////////////////////////////////
void MainWindow::slotDisconnect()
{
	m_tcpSocket->disconnectFromHost();
}

// SLOT DISCONNECTED //////////////////////////////////////////////////////////
void MainWindow::slotDisconnected()
{
	this->setState(State::NotConnected);
	m_tcpSocket->abort();
}

// SLOT ERROR /////////////////////////////////////////////////////////////////
void MainWindow::slotError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QAbstractSocket::RemoteHostClosedError)
	{
		return;
	}
	else if (socketError == QAbstractSocket::HostNotFoundError)
	{
		QString text = "The host was not found. Please check the host name and port settings.";
		QMessageBox::information(this, "Client window", text);
	}
	else if (socketError == QAbstractSocket::ConnectionRefusedError)
	{
		QString text = "The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct.";
		QMessageBox::information(this, "Client window", text);
	}
	else
	{
		QString text = "The following error occurred: " + m_tcpSocket->errorString() + ".";
		QMessageBox::information(this, "Client window", text);
	}
	
	this->setState(State::Error);
}





// SLOT SLIDER VALUE CHANGED //////////////////////////////////////////////////
void MainWindow::slotSliderValueChanged(int value)
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	float f = ((float)value) / 10000.0f;
	out << quint16{0} << RemoteJoystickMessageType::Axis << quint8{0} << f;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT BUTTON 1 PRESSED //////////////////////////////////////////////////////
void MainWindow::slotButton1Pressed()
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickMessageType::Button << quint8{0} << true;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT BUTTON 2 PRESSED //////////////////////////////////////////////////////
void MainWindow::slotButton2Pressed()
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickMessageType::Button << quint8{1} << true;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT BUTTON 1 RELEASED /////////////////////////////////////////////////////
void MainWindow::slotButton1Released()
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickMessageType::Button << quint8{0} << false;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}

// SLOT BUTTON 2 RELEASED /////////////////////////////////////////////////////
void MainWindow::slotButton2Released()
{
	QByteArray ba;
	QDataStream out{&ba, QIODevice::WriteOnly};
	out.setVersion(QDataStream::Qt_5_7);
	
	out << quint16{0} << RemoteJoystickMessageType::Button << quint8{1} << false;
	
	m_tcpSocket->flush();
	out.device()->seek(0);
	quint16 dataSize = ba.size()-sizeof(quint16);
	out << dataSize;
	m_tcpSocket->write(ba);
}


