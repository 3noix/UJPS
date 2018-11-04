#include "MfdBezelSegmentV.h"
#include "MfdSquareButton.h"
#include "Brushs.h"
#include <QPainter>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  PAINT
//  BOUNDING RECT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdBezelSegmentV::MfdBezelSegmentV(std::array<uint,5> buttons, QGraphicsItem *parent) : QGraphicsObject{parent}
{
	m_topLeft     = {0.0,0.0};
	m_rightBottom = {2.5+10.0+2.5+1.8, 1.1+0.8+4.0*15.3+10.0+0.8+1.1};
	
	m_left1  << QPointF{0.0,0.0} << QPointF{0.0,1.1} << QPointF{15.0,1.1} << QPointF{14.7,0.0};
	m_rect1  = QRectF{QPointF{0.0,1.1},QPointF{2.5+10.0+2.5,1.1+0.8+10+0.8}};
	m_right1 << QPointF{0.0,12.7} << QPointF{0.0,13.8} << QPointF{14.7,13.8} << QPointF{15.0,12.7};
	
	m_left2  = m_left1.translated({0.0,15.3});
	m_rect2  = m_rect1.translated({0.0,15.3});
	m_right2 = m_right1.translated({0.0,15.3});
	
	m_left3  = m_left1.translated({0.0,2.0*15.3});
	m_rect3  = m_rect1.translated({0.0,2.0*15.3});
	m_right3 = m_right1.translated({0.0,2.0*15.3});
	
	m_left4  = m_left1.translated({0.0,3.0*15.3});
	m_rect4  = m_rect1.translated({0.0,3.0*15.3});
	m_right4 = m_right1.translated({0.0,3.0*15.3});
	
	m_left5  = m_left1.translated({0.0,4.0*15.3});
	m_rect5  = m_rect1.translated({0.0,4.0*15.3});
	m_right5 = m_right1.translated({0.0,4.0*15.3});
	
	m_int12 = QRectF{m_right1[1],m_right1[1]+QPointF{14.7,1.5}};
	m_int23 = m_int12.translated({0.0,15.3});
	m_int34 = m_int12.translated({0.0,2.0*15.3});
	m_int45 = m_int12.translated({0.0,3.0*15.3});
	
	m_inside = QRectF{QPointF{14.7,0.0},QPointF{16.6,m_rightBottom.y()}};
	
	this->setZValue(0.0);
	
	
	// création boutons
	m_button1 = new MfdSquareButton{buttons[0],this};
	m_button2 = new MfdSquareButton{buttons[1],this};
	m_button3 = new MfdSquareButton{buttons[2],this};
	m_button4 = new MfdSquareButton{buttons[3],this};
	m_button5 = new MfdSquareButton{buttons[4],this};
	
	// ajout boutons
	m_button1->setPos(QPointF{7.5,6.9});
	m_button2->setPos(QPointF{7.5,6.9+15.3});
	m_button3->setPos(QPointF{7.5,6.9+15.3*2.0});
	m_button4->setPos(QPointF{7.5,6.9+15.3*3.0});
	m_button5->setPos(QPointF{7.5,6.9+15.3*4.0});
	
	// connections boutons
	QObject::connect(m_button1, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_button2, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_button3, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_button4, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	QObject::connect(m_button5, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
}

// PAINT //////////////////////////////////////////////////////////////////////
void MfdBezelSegmentV::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	
	painter->setPen({});
	painter->setBrush(b.interior);
	painter->drawRect(m_inside);
	
	painter->setBrush(b.gray1);
	painter->drawPolygon(m_left1);
	painter->drawPolygon(m_right1);
	painter->drawPolygon(m_left2);
	painter->drawPolygon(m_right2);
	painter->drawPolygon(m_left3);
	painter->drawPolygon(m_right3);
	painter->drawPolygon(m_left4);
	painter->drawPolygon(m_right4);
	painter->drawPolygon(m_left5);
	painter->drawPolygon(m_right5);
	
	painter->setBrush(b.gray2);
	painter->drawRect(m_rect1);
	painter->drawRect(m_rect2);
	painter->drawRect(m_rect3);
	painter->drawRect(m_rect4);
	painter->drawRect(m_rect5);
	
	painter->setBrush(b.gray3);
	painter->drawRect(m_int12);
	painter->drawRect(m_int23);
	painter->drawRect(m_int34);
	painter->drawRect(m_int45);
}

// BOUNDING RECT //////////////////////////////////////////////////////////////
QRectF MfdBezelSegmentV::boundingRect() const
{
	return {m_topLeft,m_rightBottom};
}

