#include "MyChartWidget.h"
#include <cmath>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  MOUSE RELEASE EVENT
//  ADD CURVE
//  SLOT ADD CURVE
//  SLOT PUSH VALUE
//  SLOT REMOVE CURVE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MyChartWidget::MyChartWidget(int n, int dtms, QWidget *parent) : QChartView{parent}
{
	m_colors << Qt::blue << Qt::red << Qt::green << Qt::cyan;
	m_colors << Qt::magenta << QColor{255,127,0} << QColor{127,63,0} << Qt::black;
	m_nbSamples = n;
	m_dtms = dtms;
	
	// chart creation
	m_chart = new QChart{};
	//m_chart->legend()->hide();
	
	// axes creation
	qreal xmin = (0.001*m_dtms) * (1.0-m_nbSamples);
	m_axisX = new QValueAxis{};
	m_axisY = new QValueAxis{};
	m_axisX->setRange(xmin,0.0);
	m_axisY->setRange(-1.0,1.0);
	m_axisX->setTitleText("time (s)");
	//m_axisY->setTitleText("blabla");
	m_chart->setAxisX(m_axisX);
	m_chart->setAxisY(m_axisY);
	
	// the end
	this->setChart(m_chart);
	this->setRenderHint(QPainter::Antialiasing);
	this->setRubberBand(QChartView::RectangleRubberBand);
	this->setBackgroundBrush(QBrush{Qt::white});
}


// MOUSE RELEASE EVENT ////////////////////////////////////////////////////////
void MyChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton){m_chart->zoomReset();}
	else {QChartView::mouseReleaseEvent(event);}
}

// ADD CURVE //////////////////////////////////////////////////////////////////
bool MyChartWidget::addCurve(uint index, const QString &label, const QVector<double> &x, const QVector<double> &y)
{
	if (m_seriesMap.contains(index)) {return false;}
	int n = x.size();
	if (n != y.size() || n == 0) {return false;}
	
	// pen for curve
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	pen.setColor(m_colors[m_seriesMap.size()%m_colors.size()]);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	
	// create the series
	QLineSeries *series = new QLineSeries{};
	series->setName(label);
	series->setPen(pen);
	QVector<QPointF> pts;
	for (int i=0; i<n; ++i) {pts << QPointF{x[i],y[i]};}
	series->replace(pts);
	
	// add the series in the plot and register it
	m_chart->addSeries(series);
	series->attachAxis(m_axisX);
	series->attachAxis(m_axisY);
	m_seriesMap.insert(index,series);
	return true;
}

// SLOT ADD CURVE /////////////////////////////////////////////////////////////
void MyChartWidget::slotAddCurve(uint index, const QString &label)
{
	if (m_seriesMap.contains(index)) {return;}
	
	// pen for curve
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	pen.setColor(m_colors[index%m_colors.size()]);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	
	// create the series
	QLineSeries *series = new QLineSeries{};
	series->setName(label);
	series->setPen(pen);
	
	// add the series in the plot and register it
	m_chart->addSeries(series);
	series->attachAxis(m_axisX);
	series->attachAxis(m_axisY);
	m_seriesMap.insert(index,series);
}

// SLOT PUSH VALUE ////////////////////////////////////////////////////////////
void MyChartWidget::slotPushValue(uint index, qreal yvalue)
{
	if (!m_seriesMap.contains(index)) {return;}
	QLineSeries *series = m_seriesMap[index];
	
	qreal dt = 0.001 * m_dtms;
	QVector<QPointF> pts = series->pointsVector();
	int n = pts.size();
	for (int i=1; i<n; ++i) {pts[i-1].rx() -= dt;}
	pts << QPointF{0.0,yvalue};
	if (n >= m_nbSamples) {pts.removeFirst();}
	series->replace(pts);
}

// SLOT REMOVE CURVE //////////////////////////////////////////////////////////
void MyChartWidget::slotRemoveCurve(uint index)
{
	if (!m_seriesMap.contains(index)) {return;}
	QLineSeries *series = m_seriesMap.take(index);
	m_chart->removeSeries(series);
	delete series;
}


