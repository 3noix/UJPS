#include "MfdRectangularButton.h"
#include "Brushs.h"
#include <QPainter>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>


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
MfdRectangularButton::MfdRectangularButton(uint button, const QString &text, bool bFlip, QGraphicsItem *parent) : QGraphicsObject{parent}
{
	m_button = button;
	m_currentButton = button;
	m_text = text;
	m_bFlip = bFlip;
	
	m_dx = 5.0;
	m_dy = 8.75;
	m_rect = QRectF{QPointF{-m_dx,-m_dy},QPointF{m_dx,m_dy}};
	
	m_hArrow = 2.5;
	m_arrowOffset = 1.8;
	m_r0 = 1.0;
	
	m_path1 = QPainterPath{QPointF{-m_dx,-m_dy+m_r0}};
	m_path1.lineTo(QPointF{-m_dx,m_dy-m_r0});
	m_path1.arcTo({QPointF{-m_dx,m_dy-2.0*m_r0},QPointF{-m_dx+2.0*m_r0,m_dy}},-180.0,90.0);
	//m_path1.lineTo(QPointF{-m_dx+m_r0,m_dy});
	m_path1.lineTo(QPointF{m_dx-m_r0,m_dy});
	m_path1.arcTo({QPointF{m_dx-2.0*m_r0,m_dy-2.0*m_r0},QPointF{m_dx,m_dy}},-90.0,90.0);
	//m_path1.lineTo(QPointF{m_dx,m_dy-m_r0});
	m_path1.lineTo(QPointF{m_dx,-m_dy+m_r0});
	m_path1.arcTo({QPointF{m_dx-2.0*m_r0,-m_dy},QPointF{m_dx,-m_dy+2.0*m_r0}},0.0,90.0);
	//m_path1.lineTo(QPointF{m_dx-m_r0,-m_dy});
	m_path1.lineTo(QPointF{-m_dx+m_r0,-m_dy});
	m_path1.arcTo({QPointF{-m_dx,-m_dy},QPointF{-m_dx+2.0*m_r0,-m_dy+2.0*m_r0}},90.0,90.0);
	//m_path1.lineTo(QPointF{-m_dx,-m_dy+m_r0});
	
	m_bar = QRectF{QPointF{-m_dx+1.0,-0.5},QPointF{m_dx-1.0,0.5}};
	m_textRect = QRectF{QPointF{-m_dx,-4.5},QPointF{m_dx,0.0}};
	
	m_triangle << QPointF{0,-m_dy+m_arrowOffset};
	m_triangle << QPointF{-m_hArrow/qSqrt(3.0),-m_dy+m_arrowOffset+m_hArrow};
	m_triangle << QPointF{m_hArrow/qSqrt(3.0),-m_dy+m_arrowOffset+m_hArrow};
	
	m_arrow << QPointF{0.0,m_dy-m_arrowOffset};
	m_arrow << QPointF{-m_hArrow/qSqrt(3.0),m_dy-m_arrowOffset-m_hArrow};
	m_arrow << QPointF{-0.7,m_dy-m_arrowOffset-m_hArrow};
	m_arrow << QPointF{-0.7,1.5};
	m_arrow << QPointF{0.7,1.5};
	m_arrow << QPointF{0.7,m_dy-m_arrowOffset-m_hArrow};
	m_arrow << QPointF{m_hArrow/qSqrt(3.0),m_dy-m_arrowOffset-m_hArrow};
	
	this->setZValue(10.0);
}

// PAINT //////////////////////////////////////////////////////////////////////
void MfdRectangularButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
	painter->drawRect(m_bar);
	painter->drawPolygon(m_triangle);
	painter->drawPolygon(m_arrow);
	
	QFont font = painter->font();
	font.setPointSizeF(2.0);
	painter->setFont(font);
	pen.setBrush(b.backlit);
	pen.setWidthF(1.0);
	painter->setPen(pen);
	
	if (m_bFlip)
	{
		painter->save();
		painter->scale(-1.0,1.0);
	}
	painter->drawText(m_textRect,m_text,QTextOption{Qt::AlignCenter});
	if (m_bFlip) {painter->restore();}
}

// BOUNDING RECT //////////////////////////////////////////////////////////////
QRectF MfdRectangularButton::boundingRect() const
{
	return m_rect;
}




//  MOUSE PRESS EVENT /////////////////////////////////////////////////////////
void MfdRectangularButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->pos().y() > 0) {m_currentButton = m_button + 1;}
	else {m_currentButton = m_button;}
	
	emit buttonChanged(m_currentButton,true);
}

//  MOUSE RELEASE EVENT ///////////////////////////////////////////////////////
void MfdRectangularButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	emit buttonChanged(m_currentButton,false);
}

