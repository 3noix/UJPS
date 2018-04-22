#ifndef S_CURVE_GUI
#define S_CURVE_GUI


#include "AbstractAxisCurve.h"
class SCurveWidget;


class SCurveGUI : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		SCurveGUI(float leftDZ = 0.0f, float centerDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f, float zoom = 0.0f);
		SCurveGUI(const SCurveGUI &other) = delete;
		SCurveGUI(SCurveGUI &&other) = delete;
		SCurveGUI& operator=(const SCurveGUI &other) = delete;
		SCurveGUI& operator=(SCurveGUI &&other) = delete;
		virtual ~SCurveGUI();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotLeftDZModified(double ldz);
		void slotCenterDZModified(double cdz);
		void slotRightDZModified(double rdz);
		void slotCurveParamModified(double curveParam);
		void slotZoomModified(double zoom);
		
		
	private:
		//in=-1..1, lower=0..1, center=0..1, upper=0..1, trim=-1..1, curve=-32..32
		float m_leftDZ;
		float m_centerDZ;
		float m_rightDZ;
		float m_curveParam;
		float m_zoom;
		SCurveWidget *m_widget;
		
		float m_m;
		float m_M;
		float m_cM;
		float m_cm;
};


#include <QGroupBox>
class QGridLayout;
class QLabel;
class QDoubleSpinBox;


class SCurveWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		SCurveWidget();
		SCurveWidget(const SCurveWidget &other) = delete;
		SCurveWidget(SCurveWidget &&other) = delete;
		SCurveWidget& operator=(const SCurveWidget &other) = delete;
		SCurveWidget& operator=(SCurveWidget &&other) = delete;
		virtual ~SCurveWidget() = default;
		
		
	signals:
		void leftDZModified(double newLeftDZ);
		void centerDZModified(double newCenterDZ);
		void rightDZModified(double newRightDZ);
		void curveParamModified(double newCurve);
		void zoomModified(double newZoom);
		
		
	private:
		QGridLayout *layout;
		QLabel *labelLDZ, *labelCDZ, *labelRDZ, *labelCurve, *labelZoom;
		QDoubleSpinBox *boxLDZ, *boxCDZ, *boxRDZ, *boxCurve, *boxZoom;
};

#endif
