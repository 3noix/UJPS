#ifndef MY_CHART_WIDGET
#define MY_CHART_WIDGET


#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include <vector>
#include <map>
using namespace QtCharts;


class MyChartWidget : public QChartView
{
	Q_OBJECT
	
	public:
		MyChartWidget(int n = 1000, int dtms = 15, QWidget *parent = nullptr);
		MyChartWidget(const MyChartWidget &other) = delete;
		MyChartWidget(MyChartWidget &&other) = delete;
		MyChartWidget& operator=(const MyChartWidget &other) = delete;
		MyChartWidget& operator=(MyChartWidget &&other) = delete;
		virtual ~MyChartWidget() = default;
		
		bool addCurve(uint index, const QString &label, const QVector<double> &x, const QVector<double> &y);
		
		
	public slots:
		void slotAddCurve(uint index, const QString &label);
		void slotPushValue(uint index, qreal yvalue);
		void slotRemoveCurve(uint index);
		
		
	protected:
		void mouseReleaseEvent(QMouseEvent *event);
		
		
	private:
		int m_nbSamples;
		int m_dtms;
		
		QChart *m_chart;
		QValueAxis *m_axisX;
		QValueAxis *m_axisY;
		std::map<uint,QLineSeries*> m_seriesMap;
		std::vector<QColor> m_colors;
};


#endif

