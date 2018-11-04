#include "MfdBezelCorner2.h"
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
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdBezelCorner2::MfdBezelCorner2(uint buttonUp, const QString &buttonText, bool bFlip, QGraphicsItem *parent) : QGraphicsObject{parent}
{
	m_topLeft     = {0.0,0.0};
	m_rightBottom = {g.a1,g.a0};
	
	QRectF rect0 = {QPointF{0.4,20.7}, QPointF{12.4,32.7}};
	QRectF rect1 = {QPointF{g.a3,g.a0-2.0*g.a1+g.a3},QPointF{2.0*g.a1-g.a3,g.a0-g.a3}};
	QRectF rect2 = {QPointF{g.a2,g.a0-2.0*g.a1+g.a2},QPointF{2.0*g.a1-g.a2,g.a0-g.a2}};
	
	// contour
	m_path1 = QPainterPath{QPointF{0.0,0.0}};
	m_path1.setFillRule(Qt::WindingFill);
	m_path1.lineTo(QPointF{0.0,20.7});
	m_path1.lineTo(QPointF{6.4,20.7});
	m_path1.arcTo(rect0,90.0,-90.0);
	m_path1.lineTo(QPointF{12.4,g.a0});
	m_path1.lineTo(QPointF{g.a1,g.a0});
	m_path1.lineTo(QPointF{g.a1,g.a0-g.a3});
	m_path1.arcTo(rect1,-90.0,-90.0);
	m_path1.lineTo(QPointF{g.a3,0.0});
	m_path1.lineTo(QPointF{0.0,0.0});
	
	// interior
	m_path2 = QPainterPath{QPointF{g.a1,g.a0-g.a3}};
	m_path2.arcTo(rect1,-90.0,-90.0);
	m_path2.lineTo(QPointF{g.a3,0.0});
	m_path2.lineTo(QPointF{g.a2,0.0});
	m_path2.arcTo(rect2,-180.0,90.0);
	m_path2.lineTo(QPointF{g.a1,g.a0-g.a3});
	
	// screw
	qreal dep = 0.8;
	qreal lon = 2.8;
	m_screwPrint << QPointF{dep,lon}   << QPointF{dep,dep}   << QPointF{lon,dep};
	m_screwPrint << QPointF{lon,-dep}  << QPointF{dep,-dep}  << QPointF{dep,-lon};
	m_screwPrint << QPointF{-dep,-lon} << QPointF{-dep,-dep} << QPointF{-lon,-dep};
	m_screwPrint << QPointF{-lon,dep}  << QPointF{-dep,dep}  << QPointF{-dep,lon};
	//m_screwPrint.translate(20.5,g.a0-6.0);
	
	// button
	m_button = new MfdRectangularButton{buttonUp,buttonText,bFlip,this};
	m_button->setPos(QPointF{7.5,9.55});
	QObject::connect(m_button, SIGNAL(buttonChanged(uint,bool)), this, SIGNAL(buttonChanged(uint,bool)));
	
	this->setZValue(0.0);
}

// PAINT //////////////////////////////////////////////////////////////////////
void MfdBezelCorner2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
	painter->drawEllipse(QPointF{20.5,g.a0-6.0},4.0,4.0);
	painter->setBrush(b.screw);
	painter->save();
	painter->translate(20.5,g.a0-6.0);
	painter->rotate(45.0);
	painter->drawPolygon(m_screwPrint);
	painter->restore();
}

// BOUNDING RECT //////////////////////////////////////////////////////////////
QRectF MfdBezelCorner2::boundingRect() const
{
	return {m_topLeft,m_rightBottom};
}

