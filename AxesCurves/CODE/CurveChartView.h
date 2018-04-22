#ifndef CURVE_CHART_VIEW
#define CURVE_CHART_VIEW


#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
using namespace QtCharts;

class AbstractRealJoystick;
class AbstractAxisCurve;


class CurveChartView : public QChartView
{
	Q_OBJECT
	
	public:
		CurveChartView(QWidget *parent = nullptr);
		CurveChartView(const CurveChartView &other) = delete;
		CurveChartView(CurveChartView &&other) = delete;
		CurveChartView& operator=(const CurveChartView &other) = delete;
		CurveChartView& operator=(CurveChartView &&other) = delete;
		virtual ~CurveChartView();
		
		void changeJoystickOrAxis(AbstractRealJoystick *j, uint axis);
		void changeDirection(double kdirection);
		void changeTrim1(double trim1);
		void changeTrim2(double trim2);
		void changeCurve(AbstractAxisCurve *curve);
		void updateCurrent();
		
		
	protected:
		void mouseReleaseEvent(QMouseEvent *event);
		
		
	private slots:
		void slotUpdateCurve();
		
		
	private:
		QChart *m_chart;
		QLineSeries *m_seriesXaxis;
		QLineSeries *m_seriesYaxis;
		QLineSeries *m_seriesCurve;
		QScatterSeries *m_seriesCurrent;
		QValueAxis *m_axisX;
		QValueAxis *m_axisY;
		
		AbstractRealJoystick *m_joystick;
		uint m_axis;
		qreal m_kdirection;
		qreal m_trim1;
		qreal m_trim2;
		AbstractAxisCurve *m_curve;
};

#endif

