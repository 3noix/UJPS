#include "MfdScene.h"
#include "MfdBezelSegmentH.h"
#include "MfdBezelSegmentV.h"
#include "MfdBezelCorner1.h"
#include "MfdBezelCorner2.h"
#include "MfdScreen.h"
#include "Geometry.h"

#include "ThrustmasterMfdCougar.h"
namespace TMFD = ThrustmasterMfdCougar;


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  SET LED 1
//  SET LED 2
//  LED 1
//  LED 2
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdScene::MfdScene(QObject *parent) : QGraphicsScene{parent}
{
	this->setSceneRect(QRectF{QPointF{0.0,g.L0},QPointF{0.0,g.L0}});
	
	// segments
	m_up    = new MfdBezelSegmentH{{TMFD::OSB1,TMFD::OSB2,TMFD::OSB3,TMFD::OSB4,TMFD::OSB5}};
	m_right = new MfdBezelSegmentV{{TMFD::OSB10,TMFD::OSB9,TMFD::OSB8,TMFD::OSB7,TMFD::OSB6}};
	m_down  = new MfdBezelSegmentH{{TMFD::OSB11,TMFD::OSB12,TMFD::OSB13,TMFD::OSB14,TMFD::OSB15}};
	m_left  = new MfdBezelSegmentV{{TMFD::OSB20,TMFD::OSB19,TMFD::OSB18,TMFD::OSB17,TMFD::OSB16}};
	
	this->addItem(m_up);
	this->addItem(m_left);
	this->addItem(m_down);
	this->addItem(m_right);
	
	m_up->setPos(QPointF{g.a1,0.0});
	m_left->setPos(QPointF{0.0,g.a0});
	m_down->setPos(QPointF{g.L0-g.a1,g.L0});
	m_right->setPos(QPointF{g.L0,g.a0+75.0});
	
	m_down->setRotation(180.0);
	m_right->setRotation(180.0);
	
	QObject::connect(m_up,    SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_right, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_down,  SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_left,  SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	
	// corners
	m_upLeft    = new MfdBezelCorner1{TMFD::GAINU,"GAIN",false};
	m_upRight   = new MfdBezelCorner1{TMFD::SYMU,"SYM",true};
	m_downLeft  = new MfdBezelCorner2{TMFD::BRTU,"BRT",false};
	m_downRight = new MfdBezelCorner2{TMFD::CONU,"CON",true};
	
	this->addItem(m_upLeft);
	this->addItem(m_upRight);
	this->addItem(m_downLeft);
	this->addItem(m_downRight);
	
	m_upLeft->setPos(QPointF{0.0,0.0});
	m_upRight->setPos(QPointF{g.L0,0.0});
	m_downLeft->setPos(QPointF{0.0,g.a0+75.0});
	m_downRight->setPos(QPointF{g.L0,g.a0+75.0});
	
	m_upRight->setTransform(QTransform::fromScale(-1,1));
	m_downRight->setTransform(QTransform::fromScale(-1,1));
	
	QObject::connect(m_upLeft,    SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_upRight,   SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_downLeft,  SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_downRight, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	
	// screen
	m_screen = new MfdScreen{};
	this->addItem(m_screen);
	m_screen->setPos(QPointF{0.0,0.0});
}

// SET LED 1 //////////////////////////////////////////////////////////////////
void MfdScene::setLed1(bool b)
{
	m_upLeft->setLed(b);
}

// SET LED 2 //////////////////////////////////////////////////////////////////
void MfdScene::setLed2(bool b)
{
	m_upRight->setLed(b);
}

// LED 1 //////////////////////////////////////////////////////////////////////
bool MfdScene::led1() const
{
	return m_upLeft->led();
}

// LED 2 //////////////////////////////////////////////////////////////////////
bool MfdScene::led2() const
{
	return m_upRight->led();
}

