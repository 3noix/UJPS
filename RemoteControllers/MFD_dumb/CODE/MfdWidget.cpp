#include "MfdWidget.h"
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
	m_client{"MFD_remote",{"OSB1","OSB2","OSB3","OSB4","OSB5","OSB6","OSB7","OSB8","OSB9","OSB10","OSB11","OSB12","OSB13","OSB14","OSB15","OSB16","OSB17","OSB18","OSB19","OSB20","SYMU","SYMD","CONU","COND","BRTU","BRTD","GAINU","GAIND"},{},{}}
{
	// widget work
	this->setWindowTitle("MFD dumb");
	this->setFixedSize(size,size);
	this->setBackgroundBrush(QBrush{Qt::white});
	this->setRenderHint(QPainter::Antialiasing);
	this->setScene(&m_scene);
	
	qreal scaleFactorX = 0.99 * size / this->sceneRect().width();
	qreal scaleFactorY = 0.99 * size / this->sceneRect().height();
	qreal scaleFactor = scaleFactorX;
	if (scaleFactorY < scaleFactorX) {scaleFactor = scaleFactorY;}
	this->scale(scaleFactor,scaleFactor);
	
	QObject::connect(&m_scene, SIGNAL(buttonChanged(uint,bool)),  this, SLOT(slotButtonChanged(uint,bool)));
	
	// network work
	m_connectionWidget = new ConnectionWidget{};
	this->slotSetState(RemoteJoystickClient::State::NotConnected);
	
	QObject::connect(&m_client, &RemoteJoystickClient::signalSetData, this, &MfdWidget::slotSetData);
	QObject::connect(&m_client, &RemoteJoystickClient::stateChanged,  this, &MfdWidget::slotSetState);
	QObject::connect(&m_client, &RemoteJoystickClient::error,         this, &MfdWidget::slotError);
	QObject::connect(m_connectionWidget, &ConnectionWidget::connectionRequest, &m_client, &RemoteJoystickClient::slotConnect);
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
	QMessageBox::information(this, "MFD dumb", text);
}

// SLOT SET STATE /////////////////////////////////////////////////////////////
void MfdWidget::slotSetState(RemoteJoystickClient::State s)
{
	if (s == RemoteJoystickClient::State::NotConnected || s == RemoteJoystickClient::State::Error)
	{
		m_connectionWidget->show();
		m_connectionWidget->raise();
		m_connectionWidget->setDisconnected();
	}
	else if (s == RemoteJoystickClient::State::Connecting)
	{
		m_connectionWidget->show();
		m_connectionWidget->raise();
		m_connectionWidget->setConnecting();
	}
	else if (s == RemoteJoystickClient::State::Connected)
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

