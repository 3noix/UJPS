#ifndef J_CURVE
#define J_CURVE


#include "AbstractAxisCurve.h"
class JCurveWidget;


class JCurve : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		JCurve(float zoom = 0.0f);
		JCurve(const JCurve &other) = delete;
		JCurve(JCurve &&other) = delete;
		JCurve& operator=(const JCurve &other) = delete;
		JCurve& operator=(JCurve &&other) = delete;
		virtual ~JCurve();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotZoomModified(double zoom);
		
		
	private:
		float m_zoom;
		JCurveWidget *m_widget;
};


#include <QGroupBox>
class QHBoxLayout;
class QLabel;
class QDoubleSpinBox;


class JCurveWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		JCurveWidget();
		JCurveWidget(const JCurveWidget &other) = delete;
		JCurveWidget(JCurveWidget &&other) = delete;
		JCurveWidget& operator=(const JCurveWidget &other) = delete;
		JCurveWidget& operator=(JCurveWidget &&other) = delete;
		virtual ~JCurveWidget() = default;
		
		
	signals:
		void zoomModified(double newZoom);
		
		
	private:
		QHBoxLayout *layout;
		QLabel *labelZoom;
		QDoubleSpinBox *boxZoom;
};


#endif
