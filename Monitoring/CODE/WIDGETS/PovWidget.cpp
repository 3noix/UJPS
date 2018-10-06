#include "PovWidget.h"
#include <QPen>
#include <QBrush>
#include <QPainter>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  ANGLE
//  SLOT SET ANGLE
//  PAINT EVENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
PovWidget::PovWidget(QWidget *parent) : QWidget{parent}
{
	m_angle = -1.0f;
	this->setFixedSize(100,100);
}

// ANGLE //////////////////////////////////////////////////////////////////////
float PovWidget::angle() const
{
	return m_angle;
}

// SLOT SET ANGLE /////////////////////////////////////////////////////////////
void PovWidget::slotSetAngle(float angle)
{
	m_angle = angle;
	this->update();
}

// PAINT EVENT ////////////////////////////////////////////////////////////////
void PovWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	QPen pen{QBrush{Qt::black}, 1.0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin};
	pen.setCosmetic(true);
	QPainter painter{this};
	painter.setPen(pen);
	painter.setBrush(QBrush{Qt::gray});
	painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
	painter.drawEllipse(45,45,10,10);
	painter.setBrush({});
	painter.drawEllipse(13,13,74,74);
	painter.setPen(QPen{Qt::NoPen});
	
	if (m_angle == -1.0f)
	{
		painter.setBrush(QBrush{Qt::darkRed});
		painter.drawEllipse(45,45,10,10);
	}
	else
	{
		painter.setBrush(QBrush{Qt::red});
		QPolygonF pol;
		pol << QPointF{0.0,-10.0} << QPointF{9.0,0.0};
		pol << QPointF{3.0,0.0} << QPointF{3.0,15.0};
		pol << QPointF{-3.0,15.0} << QPointF{-3.0,0.0} << QPointF{-9.0,0.0};
		painter.translate(QPointF{50.0,50.0});
		painter.rotate(m_angle);
		painter.translate(QPointF{0.0,-40.0});
		painter.drawPolygon(pol);
	}
}

