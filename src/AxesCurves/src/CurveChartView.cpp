#include "CurveChartView.h"
#include "curves/AbstractAxisCurve.h"
#include "RealJoysticks/AbstractRealJoystick.h"
#include "Other/Lim.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  MOUSE RELEASE EVENT
//
//  CHANGE JOYSTICK OR AXIS
//  CHANGE DIRECTION
//  CHANGE TRIM1
//  CHANGE TRIM2
//  CHANGE CURVE
//
//  SLOT UPDATE CURVE
//  UPDATE CURRENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurveChartView::CurveChartView(QWidget *parent) : QChartView{parent}
{
	m_joystick = nullptr;
	m_axis = 0;
	m_kdirection = 1.0;
	m_trim1 = 0.0;
	m_trim2 = 0.0;
	m_curve = nullptr;
	
	// series for highlighting the "axes" (mathematically speaking)
	QPen pen{Qt::black};
	m_seriesXaxis = new QLineSeries{};
	m_seriesYaxis = new QLineSeries{};
	m_seriesXaxis->setPen(pen);
	m_seriesYaxis->setPen(pen);
	*m_seriesXaxis << QPointF{-1.0,0.0} << QPointF{1.0,0.0};
	*m_seriesYaxis << QPointF{0.0,-1.0} << QPointF{0.0,1.0};
	
	// series for the curve
	m_seriesCurve = new QLineSeries{};
	for (int i=0; i<2001; ++i)
	{
		qreal x = 0.001*i - 1.0;
		*m_seriesCurve << QPointF{x,x};
	}
	
	// series for the current position
	m_seriesCurrent = new QScatterSeries{};
	m_seriesCurrent->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	m_seriesCurrent->setMarkerSize(10.0);
	*m_seriesCurrent << QPointF{0.0,0.0};
	
	// chart creation
	m_chart = new QChart{};
	m_chart->legend()->hide();
	m_chart->addSeries(m_seriesXaxis);
	m_chart->addSeries(m_seriesYaxis);
	m_chart->addSeries(m_seriesCurve);
	m_chart->addSeries(m_seriesCurrent);
	
	// axes creation
	m_axisX = new QValueAxis{};
	m_axisY = new QValueAxis{};
	m_axisX->setRange(-1,1);
	m_axisY->setRange(-1,1);
	m_axisX->setTitleText("Real joystick raw position");
	m_axisY->setTitleText("Virtual joystick position");
	m_chart->addAxis(m_axisX,Qt::AlignBottom);
	m_chart->addAxis(m_axisY,Qt::AlignLeft);
	
	// attach series to axes
	m_seriesCurve->attachAxis(m_axisX);
	m_seriesCurve->attachAxis(m_axisY);
	m_seriesCurrent->attachAxis(m_axisX);
	m_seriesCurrent->attachAxis(m_axisY);
	m_seriesXaxis->attachAxis(m_axisX);
	m_seriesXaxis->attachAxis(m_axisY);
	m_seriesYaxis->attachAxis(m_axisX);
	m_seriesYaxis->attachAxis(m_axisY);
	
	// the end
	this->setChart(m_chart);
	this->setRenderHint(QPainter::Antialiasing);
	this->setRubberBand(QChartView::RectangleRubberBand);
}

// MOUSE RELEASE EVENT ////////////////////////////////////////////////////////
void CurveChartView::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		m_chart->zoomReset();
	}
	else
	{
		QChartView::mouseReleaseEvent(event);
	}
}






// CHANGE JOYSTICK OR AXIS ////////////////////////////////////////////////////
void CurveChartView::changeJoystickOrAxis(AbstractRealJoystick *j, uint axis)
{
	m_joystick = j;
	m_axis = axis;
	
	this->updateCurrent();
}

// CHANGE DIRECTION ///////////////////////////////////////////////////////////
void CurveChartView::changeDirection(double kdirection)
{
	m_kdirection = kdirection;
	this->slotUpdateCurve();
}

// CHANGE TRIM1 ///////////////////////////////////////////////////////////////
void CurveChartView::changeTrim1(double trim1)
{
	m_trim1 = trim1;
	this->slotUpdateCurve();
}

// CHANGE TRIM2 ///////////////////////////////////////////////////////////////
void CurveChartView::changeTrim2(double trim2)
{
	m_trim2 = trim2;
	this->slotUpdateCurve();
}

// CHANGE CURVE ///////////////////////////////////////////////////////////////
void CurveChartView::changeCurve(AbstractAxisCurve *curve)
{
	m_curve = curve;
	
	if (m_curve) {QObject::connect(m_curve, SIGNAL(curveModified()), this, SLOT(slotUpdateCurve()));}
	this->slotUpdateCurve();
}







// UPDATE CURRENT /////////////////////////////////////////////////////////////
void CurveChartView::updateCurrent()
{
	if (!m_joystick) {return;}
	qreal x = lim<qreal>(m_joystick->axisValue(m_axis)+m_trim1,-1.0,1.0);
	qreal y = x;
	if (m_curve) {y = m_curve->run(x);}
	y = lim<qreal>(m_kdirection*y+m_trim2,-1.0,1.0);
	
	m_seriesCurrent->replace(0,x,y);
}

// SLOT UPDATE CURVE //////////////////////////////////////////////////////////
void CurveChartView::slotUpdateCurve()
{
	// la courbe
	QVector<QPointF> points;
	points.reserve(2001);
	for (int i=0; i<2001; ++i)
	{
		qreal x = lim<qreal>(0.001*i-1.0+m_trim1,-1.0,1.0);
		qreal y = x;
		if (m_curve) {y = m_curve->run(x);}
		y = lim<qreal>(m_kdirection*y+m_trim2,-1.0,1.0);
		
		points << QPointF{x,y};
	}
	m_seriesCurve->replace(points);
	
	// le point courant
	this->updateCurrent();
}

