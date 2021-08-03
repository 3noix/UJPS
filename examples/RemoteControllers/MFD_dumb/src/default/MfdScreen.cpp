#include "MfdScreen.h"
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
MfdScreen::MfdScreen(QGraphicsItem *parent) : QGraphicsObject{parent}
{
	m_topLeft     = {0.0,0.0};
	m_rightBottom = {g.L0,g.L0};
	m_rect = {m_topLeft,m_rightBottom};
	
	QRectF circleUpLeft  = {QPointF{g.a2,g.a2},                             QPointF{2.0*g.a1-g.a2,2.0*g.a1-g.a2}};
	QRectF circleUpRight = {QPointF{g.L0+g.a2-2.0*g.a1,g.a2},               QPointF{g.L0-g.a2,2.0*g.a1-g.a2}};
	QRectF circleDnRight = {QPointF{g.L0+g.a2-2.0*g.a1,g.L0+g.a2-2.0*g.a1}, QPointF{g.L0-g.a2,g.L0-g.a2}};
	QRectF circleDnLeft  = {QPointF{g.a2,g.L0+g.a2-2.0*g.a1},               QPointF{2.0*g.a1-g.a2,g.L0-g.a2}};
	
	m_path = QPainterPath{QPointF{g.a2,g.a1}};
	m_path.setFillRule(Qt::WindingFill);
	m_path.arcTo(circleUpLeft,180.0,-90.0);
	//m_path.lineTo(QPointF{g.a1,g.a2});
	m_path.lineTo(QPointF{g.L0-g.a1,g.a2});
	m_path.arcTo(circleUpRight,90.0,-90.0);
	//m_path.lineTo(QPointF{g.L0-g.a2,g.a1});
	m_path.lineTo(QPointF{g.L0-g.a2,g.L0-g.a1});
	m_path.arcTo(circleDnRight,0.0,-90.0);
	//m_path.lineTo(QPointF{g.L0-g.a1,g.L0-g.a2});
	m_path.lineTo(QPointF{g.a1,g.L0-g.a2});
	m_path.arcTo(circleDnLeft,-90.0,-90.0);
	//m_path.lineTo(QPointF{g.a2,g.L0-g.a1});
	m_path.lineTo(QPointF{g.a2,g.a1});
	
	this->setZValue(-10.0);
}

// PAINT //////////////////////////////////////////////////////////////////////
void MfdScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	
	painter->setPen({});
	painter->setBrush(b.screen);
	painter->drawPath(m_path);
}

// BOUNDING RECT //////////////////////////////////////////////////////////////
QRectF MfdScreen::boundingRect() const
{
	return m_rect;
}

