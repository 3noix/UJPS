#include "MfdBezelCorner1.h"
#include "MfdRectangularButton.h"
#include "Geometry.h"
#include "Brushs.h"
#include <QPainter>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  PAINT
//  BOUNDING RECT
//  SET LED
//  LED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdBezelCorner1::MfdBezelCorner1(uint buttonUp, const QString &buttonText, bool bFlip, QGraphicsItem *parent) : QGraphicsObject{parent}
{
	m_bLedOn = false;
	m_topLeft = {0.0,0.0};
	m_rightBottom = {g.a1,g.a0};
	
	QRectF rect1 = {QPointF{g.a3,g.a3}, QPointF{2.0*g.a1-g.a3,2.0*g.a1-g.a3}};
	QRectF rect2 = {QPointF{g.a2,g.a2}, QPointF{2.0*g.a1-g.a2,2.0*g.a1-g.a2}};
	
	// contour
	m_path1 = QPainterPath{QPointF{0.0,6.0}};
	m_path1.setFillRule(Qt::WindingFill);
	m_path1.lineTo(QPointF{0.0,g.a0});
	m_path1.lineTo(QPointF{g.a3,g.a0});
	m_path1.lineTo(QPointF{g.a3,g.a1});
	m_path1.arcTo(rect1,180.0,-90.0);
	m_path1.lineTo(QPointF{g.a1,g.a3});
	m_path1.lineTo(QPointF{g.a1,0.0});
	m_path1.lineTo(QPointF{6.0,0.0});
	m_path1.arcTo(QRectF{QPointF{0.0,0.0},QPointF{12.0,12.0}},90.0,90.0);
	
	// interior
	m_path2 = QPainterPath{QPointF{g.a3,g.a0}};
	m_path2.lineTo(QPointF{g.a3,g.a1});
	m_path2.arcTo(rect1,180.0,-90.0);
	m_path2.lineTo(QPointF{g.a1,g.a2});
	m_path2.arcTo(rect2,90.0,90.0);
	m_path2.lineTo(QPointF{g.a2,g.a0});
	m_path2.lineTo(QPointF{g.a3,g.a0});
	
	// screw
	qreal dep = 0.8;
	qreal lon = 2.8;
	m_screwPrint << QPointF{dep,lon}   << QPointF{dep,dep}   << QPointF{lon,dep};
	m_screwPrint << QPointF{lon,-dep}  << QPointF{dep,-dep}  << QPointF{dep,-lon};
	m_screwPrint << QPointF{-dep,-lon} << QPointF{-dep,-dep} << QPointF{-lon,-dep};
	m_screwPrint << QPointF{-lon,dep}  << QPointF{-dep,dep}  << QPointF{-dep,lon};
	//m_screwPrint.translate(6.0,6.0);
	
	// button
	m_button = new MfdRectangularButton{buttonUp,buttonText,bFlip,this};
	m_button->setPos(QPointF{7.5,21.95});
	QObject::connect(m_button, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	
	this->setZValue(0.0);
}

// PAINT //////////////////////////////////////////////////////////////////////
void MfdBezelCorner1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	
	// contour
	painter->setPen({});
	painter->setBrush(b.gray2);
	painter->drawPath(m_path1);
	painter->setBrush(b.interior);
	painter->drawPath(m_path2);
	
	// screw
	QPen pen{Qt::black};
	pen.setWidthF(0.2);
	painter->setPen(pen);
	painter->setBrush(b.gray2);
	painter->drawEllipse(QPointF{6.0,6.0},4.0,4.0);
	painter->setBrush(b.screw);
	painter->save();
	painter->translate(6.0,6.0);
	painter->rotate(45.0);
	painter->drawPolygon(m_screwPrint);
	painter->restore();
	
	// led
	if (m_bLedOn) {painter->setBrush(b.ledOn);}
	else {painter->setBrush(b.ledOff);}
	painter->drawEllipse(QPointF{22.0,6.0},4.3,4.3);
}

// BOUNDING RECT //////////////////////////////////////////////////////////////
QRectF MfdBezelCorner1::boundingRect() const
{
	return {m_topLeft,m_rightBottom};
}

// SET LED ////////////////////////////////////////////////////////////////////
void MfdBezelCorner1::setLed(bool b)
{
	if (b == m_bLedOn) {return;}
	m_bLedOn = b;
	this->update();
}

// LED ////////////////////////////////////////////////////////////////////////
bool MfdBezelCorner1::led() const
{
	return m_bLedOn;
}

