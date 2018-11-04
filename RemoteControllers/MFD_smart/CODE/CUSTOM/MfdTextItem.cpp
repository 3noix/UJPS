#include "MfdTextItem.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  TEXT
//  SET ACTIVATED
//  IS ACTIVATED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdTextItem::MfdTextItem(const QString &text, qreal fontSize, Qt::Alignment a, QGraphicsItem *parent) : QGraphicsItemGroup{parent}
{
	m_font.setPointSizeF(fontSize);
	m_penActivated.setColor(Qt::magenta);
	m_penActivated.setWidthF(0.2);
	
	m_textItem = new QGraphicsSimpleTextItem{text,this};
	m_textItem->setFont(m_font);
	m_textItem->setPen(Qt::NoPen);
	m_textItem->setBrush(QBrush{Qt::green});
	
	m_rectActivated = m_textItem->boundingRect();
	//m_rectActivated = m_textItem->boundingRect().adjusted(0.0,0.0,0.0,0.0);
	m_rectItem = new QGraphicsRectItem{m_rectActivated,this};
	m_rectItem->setPen(m_penActivated);
	m_rectItem->setBrush(Qt::NoBrush);
	m_rectItem->setVisible(false);
	
	if (a & Qt::AlignHCenter) {m_posOffset.rx() -= 0.5 * m_rectActivated.width();}
	else if (a & Qt::AlignRight) {m_posOffset.rx() -= m_rectActivated.width();}
	
	if (a & Qt::AlignVCenter) {m_posOffset.ry() -= 0.5 * m_rectActivated.height();}
	else if (a & Qt::AlignBottom) {m_posOffset.ry() -= m_rectActivated.height();}
	
	m_textItem->setPos(m_posOffset);
	m_rectItem->setPos(m_posOffset);
	
	this->setZValue(0.0);
}

// TEXT ///////////////////////////////////////////////////////////////////////
QString MfdTextItem::text() const
{
	return m_textItem->text();
}

// SET ACTIVATED //////////////////////////////////////////////////////////////
void MfdTextItem::setActivated(bool b)
{
	m_rectItem->setVisible(b);
}

// IS ACTIVATED ///////////////////////////////////////////////////////////////
bool MfdTextItem::isActivated() const
{
	return m_rectItem->isVisible();
}

