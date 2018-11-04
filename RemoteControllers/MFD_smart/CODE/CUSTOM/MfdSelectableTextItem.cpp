#include "MfdSelectableTextItem.h"
#include <QFontMetrics>
#include <QPainter>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//
//  TEXT
//  SELECT
//  UNSELECT
//  SWITCH SELECTION
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdSelectableTextItem::MfdSelectableTextItem(const QString &text, qreal fontSize, Qt::Alignment a, QGraphicsItem *parent) : QGraphicsItemGroup{parent}
{
	m_bSelected = false;
	m_font.setPointSizeF(fontSize);
	
	m_textItem = new QGraphicsSimpleTextItem{text,this};
	m_textItem->setFont(m_font);
	m_textItem->setPen(Qt::NoPen);
	m_textItem->setBrush(QBrush{Qt::green});
	
	//m_rect = m_textItem->boundingRect();
	m_rect = m_textItem->boundingRect().adjusted(-0.5,0.0,0.5,0.0);
	m_rectItem = new QGraphicsRectItem{m_rect,this};
	m_rectItem->setPen(Qt::NoPen);
	m_rectItem->setBrush(QBrush{Qt::black});
	
	if (a & Qt::AlignHCenter) {m_posOffset.rx() -= 0.5 * m_rect.width();}
	else if (a & Qt::AlignRight) {m_posOffset.rx() -= m_rect.width();}
	
	if (a & Qt::AlignVCenter) {m_posOffset.ry() -= 0.5 * m_rect.height();}
	else if (a & Qt::AlignBottom) {m_posOffset.ry() -= m_rect.height();}
	
	m_textItem->setPos(m_posOffset);
	m_rectItem->setPos(m_posOffset);
	m_textItem->setZValue(1.0);
	m_rectItem->setZValue(0.0);
	this->setZValue(0.0);
}




// TEXT ///////////////////////////////////////////////////////////////////////
QString MfdSelectableTextItem::text() const
{
	return m_textItem->text();
}

// SELECT /////////////////////////////////////////////////////////////////////
void MfdSelectableTextItem::select()
{
	m_bSelected = true;
	m_textItem->setBrush(QBrush{Qt::black});
	m_rectItem->setBrush(QBrush{Qt::green});
}

// UNSELECT ///////////////////////////////////////////////////////////////////
void MfdSelectableTextItem::unselect()
{
	m_bSelected = false;
	m_textItem->setBrush(QBrush{Qt::green});
	m_rectItem->setBrush(QBrush{Qt::black});
}

// SWITCH SELECTION ///////////////////////////////////////////////////////////
void MfdSelectableTextItem::switchSelection()
{
	if (m_bSelected) {this->unselect();}
	else {this->select();}
}

