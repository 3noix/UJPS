#include "MfdSquareButton.h"
#include "Brushs.h"
#include <QPainter>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  PAINT
//  BOUNDING RECT
//
//  MOUSE PRESS EVENT
//  MOUSE RELEASE EVENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdSquareButton::MfdSquareButton(uint button, QGraphicsItem *parent) : QGraphicsObject{parent}
{
	m_button = button;
	
	m_size = 5.0;
	m_b = 1.0;
	m_c = 2.0;
	
	m_r0 = 1.0;
	m_rb = 0.8;
	m_rc = 0.6;
	
	m_rect = QRectF{QPointF{-m_size,-m_size},QPointF{m_size,m_size}};
	
	qreal cote = m_size;
	qreal rayo = m_r0;
	m_path1 = QPainterPath{QPointF{-cote,-cote+rayo}};
	m_path1.lineTo(QPointF{-cote,cote-rayo});
	m_path1.arcTo({QPointF{-cote,cote-2.0*rayo},QPointF{-cote+2.0*rayo,cote}},-180.0,90.0);
	//m_path1.lineTo(QPointF{-cote+rayo,cote});
	m_path1.lineTo(QPointF{cote-rayo,cote});
	m_path1.arcTo({QPointF{cote-2.0*rayo,cote-2.0*rayo},QPointF{cote,cote}},-90.0,90.0);
	//m_path1.lineTo(QPointF{cote,cote-rayo});
	m_path1.lineTo(QPointF{cote,-cote+rayo});
	m_path1.arcTo({QPointF{cote-2.0*rayo,-cote},QPointF{cote,-cote+2.0*rayo}},0.0,90.0);
	//m_path1.lineTo(QPointF{cote-rayo,-cote});
	m_path1.lineTo(QPointF{-cote+rayo,-cote});
	m_path1.arcTo({QPointF{-cote,-cote},QPointF{-cote+2.0*rayo,-cote+2.0*rayo}},90.0,90.0);
	//m_path1.lineTo(QPointF{-cote,-cote+rayo});
	
	cote = m_size - m_b;
	rayo = m_rb;
	m_path2 = QPainterPath{QPointF{-cote,-cote+rayo}};
	m_path2.lineTo(QPointF{-cote,cote-rayo});
	m_path2.arcTo({QPointF{-cote,cote-2.0*rayo},QPointF{-cote+2.0*rayo,cote}},-180.0,90.0);
	//m_path2.lineTo(QPointF{-cote+rayo,cote});
	m_path2.lineTo(QPointF{cote-rayo,cote});
	m_path2.arcTo({QPointF{cote-2.0*rayo,cote-2.0*rayo},QPointF{cote,cote}},-90.0,90.0);
	//m_path2.lineTo(QPointF{cote,cote-rayo});
	m_path2.lineTo(QPointF{cote,-cote+rayo});
	m_path2.arcTo({QPointF{cote-2.0*rayo,-cote},QPointF{cote,-cote+2.0*rayo}},0.0,90.0);
	//m_path2.lineTo(QPointF{cote-rayo,-cote});
	m_path2.lineTo(QPointF{-cote+rayo,-cote});
	m_path2.arcTo({QPointF{-cote,-cote},QPointF{-cote+2.0*rayo,-cote+2.0*rayo}},90.0,90.0);
	//m_path2.lineTo(QPointF{-cote,-cote+rayo});
	
	cote = m_size - m_c;
	rayo = m_rc;
	m_path3 = QPainterPath{QPointF{-cote,-cote+rayo}};
	m_path3.lineTo(QPointF{-cote,cote-rayo});
	m_path3.arcTo({QPointF{-cote,cote-2.0*rayo},QPointF{-cote+2.0*rayo,cote}},-180.0,90.0);
	//m_path3.lineTo(QPointF{-cote+rayo,cote});
	m_path3.lineTo(QPointF{cote-rayo,cote});
	m_path3.arcTo({QPointF{cote-2.0*rayo,cote-2.0*rayo},QPointF{cote,cote}},-90.0,90.0);
	//m_path3.lineTo(QPointF{cote,cote-rayo});
	m_path3.lineTo(QPointF{cote,-cote+rayo});
	m_path3.arcTo({QPointF{cote-2.0*rayo,-cote},QPointF{cote,-cote+2.0*rayo}},0.0,90.0);
	//m_path3.lineTo(QPointF{cote-rayo,-cote});
	m_path3.lineTo(QPointF{-cote+rayo,-cote});
	m_path3.arcTo({QPointF{-cote,-cote},QPointF{-cote+2.0*rayo,-cote+2.0*rayo}},90.0,90.0);
	//m_path3.lineTo(QPointF{-cote,-cote+rayo});
	
	this->setZValue(10.0);
}

// PAINT //////////////////////////////////////////////////////////////////////
void MfdSquareButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	
	QPen pen{Qt::black};
	pen.setWidthF(0.4);
	painter->setPen(pen);
	painter->setBrush(b.gray3);
	painter->drawPath(m_path1);
	painter->setPen({});
	painter->setBrush(b.backlit);
	painter->drawPath(m_path2);
	painter->setBrush(b.gray3);
	painter->drawPath(m_path3);
}

// BOUNDING RECT //////////////////////////////////////////////////////////////
QRectF MfdSquareButton::boundingRect() const
{
	return m_rect;
}




//  MOUSE PRESS EVENT /////////////////////////////////////////////////////////
void MfdSquareButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	emit buttonChanged(m_button,true);
}

//  MOUSE RELEASE EVENT ///////////////////////////////////////////////////////
void MfdSquareButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	emit buttonChanged(m_button,false);
}

