#include "MfdWidget.h"
#include "MfdControls.h"
#include "REMOTE/ConnectionWidget.h"
#include <QMessageBox>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  SLOT BUTTON CHANGED
//  SLOT SET DATA
//
//  SLOT ERROR
//  SLOT SET STATE
//  SHOW CONNECTION WIDGET
//
//  SET LED 1
//  SET LED 2
//  LED 1
//  LED 2
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdWidget::MfdWidget(int size, QWidget *parent) :
	QGraphicsView{parent},
	m_client{"MFD_remote",MfdControls::controlsNames,{},{}}
{
	// widget work
	this->setWindowTitle("MFD smart");
	this->setFixedSize(size,size);
	this->setBackgroundBrush(QBrush{Qt::white});
	this->setRenderHint(QPainter::Antialiasing);
	this->setScene(&m_scene);
	
	qreal scaleFactorX = 0.99 * size / this->sceneRect().width();
	qreal scaleFactorY = 0.99 * size / this->sceneRect().height();
	qreal scaleFactor = scaleFactorX;
	if (scaleFactorY < scaleFactorX) {scaleFactor = scaleFactorY;}
	this->scale(scaleFactor,scaleFactor);
	
	QObject::connect(&m_scene, SIGNAL(buttonChanged2(uint,bool)), this, SLOT(slotButtonChanged(uint,bool)));
	
	// network work
	m_connectionWidget = new ConnectionWidget{};
	this->slotSetState(RemoteJoystickTcpClient::State::NotConnected);
	
	QObject::connect(&m_client, &RemoteJoystickTcpClient::signalSetData, this, &MfdWidget::slotSetData);
	QObject::connect(&m_client, &RemoteJoystickTcpClient::stateChanged,  this, &MfdWidget::slotSetState);
	QObject::connect(&m_client, &RemoteJoystickTcpClient::error,         this, &MfdWidget::slotError);
	QObject::connect(m_connectionWidget, &ConnectionWidget::connectionRequest, &m_client, &RemoteJoystickTcpClient::slotConnect);
}

// DESTRUCTEUR ////////////////////////////////////////////////////////////////
MfdWidget::~MfdWidget()
{
	delete m_connectionWidget;
}






// SLOT BUTTON CHANGED ////////////////////////////////////////////////////////
void MfdWidget::slotButtonChanged(uint button, bool bPressed)
{
	m_client.slotSendButtonInfo(button,bPressed);
}

// SLOT SET DATA //////////////////////////////////////////////////////////////
void MfdWidget::slotSetData(const QString &prop, QVariant data)
{
	Q_UNUSED(prop)
	Q_UNUSED(data)
	
	/*if (prop == "button3")
	{
		bool b = data.toBool();
		m_button3->setDown(b);
	}*/
}






// SLOT ERROR /////////////////////////////////////////////////////////////////
void MfdWidget::slotError(const QString &text)
{
	QMessageBox::information(this, "MFD smart", text);
}

// SLOT SET STATE /////////////////////////////////////////////////////////////
void MfdWidget::slotSetState(RemoteJoystickTcpClient::State s)
{
	if (s == RemoteJoystickTcpClient::State::NotConnected || s == RemoteJoystickTcpClient::State::Error)
	{
		m_connectionWidget->show();
		m_connectionWidget->raise();
		m_connectionWidget->setDisconnected();
	}
	else if (s == RemoteJoystickTcpClient::State::Connecting)
	{
		m_connectionWidget->show();
		m_connectionWidget->raise();
		m_connectionWidget->setConnecting();
	}
	else if (s == RemoteJoystickTcpClient::State::Connected)
	{
		m_connectionWidget->hide();
		m_connectionWidget->setConnected();
		
		// send initial state
		// TO BE COMPLETED
	}
}

// SHOW CONNECTION WIDGET /////////////////////////////////////////////////////
void MfdWidget::showConnectionWidget()
{
	m_connectionWidget->show();
	m_connectionWidget->raise();
}






// SET LED 1 //////////////////////////////////////////////////////////////////
void MfdWidget::setLed1(bool b)
{
	m_scene.setLed1(b);
}

// SET LED 2 //////////////////////////////////////////////////////////////////
void MfdWidget::setLed2(bool b)
{
	m_scene.setLed2(b);
}

// LED 1 //////////////////////////////////////////////////////////////////////
bool MfdWidget::led1() const
{
	return m_scene.led1();
}

// LED 2 //////////////////////////////////////////////////////////////////////
bool MfdWidget::led2() const
{
	return m_scene.led2();
}

