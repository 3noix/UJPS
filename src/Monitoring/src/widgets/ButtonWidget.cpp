#include "ButtonWidget.h"
#include <QPen>
#include <QBrush>
#include <QPainter>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  IS CHECKED
//  SLOT SET CHECKED
//  PAINT EVENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
ButtonWidget::ButtonWidget(int i, bool enabled, QWidget *parent) : QWidget{parent}
{
	m_enabled = enabled;
	m_checked = false;
	m_text = QString::number(i);
	this->setFixedSize(30,30);
}

// IS CHECKED /////////////////////////////////////////////////////////////////
bool ButtonWidget::isChecked() const
{
	return m_checked;
}

// SLOT SET CHECKED ///////////////////////////////////////////////////////////
void ButtonWidget::slotSetChecked(bool checked)
{
	m_checked = checked;
	this->update();
}

// PAINT EVENT ////////////////////////////////////////////////////////////////
void ButtonWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	QFont font;
	font.setPointSize(15);
	QPen pen{QBrush{Qt::black}, 1.0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin};
	pen.setCosmetic(true);
	QPainter painter{this};
	painter.setFont(font);
	painter.setPen(pen);
	if (!m_enabled) {painter.setBrush(QBrush{Qt::darkGray});}
	else if (m_checked) {painter.setBrush(QBrush{Qt::red});}
	else {painter.setBrush(QBrush{Qt::darkRed});}
	painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
	painter.drawEllipse(0,0,30,30);
	painter.drawText(this->rect(),Qt::AlignCenter,m_text);
}

