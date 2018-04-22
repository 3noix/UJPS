#ifndef J_CURVE_GUI
#define J_CURVE_GUI


#include "AbstractAxisCurve.h"
class JCurveWidget;


class JCurveGUI : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		JCurveGUI(float zoom = 0.0f);
		JCurveGUI(const JCurveGUI &other) = delete;
		JCurveGUI(JCurveGUI &&other) = delete;
		JCurveGUI& operator=(const JCurveGUI &other) = delete;
		JCurveGUI& operator=(JCurveGUI &&other) = delete;
		virtual ~JCurveGUI();
		
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
