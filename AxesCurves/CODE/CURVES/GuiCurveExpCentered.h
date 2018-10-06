#ifndef GUI_CURVE_EXP_CENTERED
#define GUI_CURVE_EXP_CENTERED


#include "AbstractAxisCurve.h"
class CurveExpCenteredWidget;


class GuiCurveExpCentered : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		GuiCurveExpCentered(float leftDZ = 0.0f, float centerDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f, float zoom = 0.0f);
		GuiCurveExpCentered(const GuiCurveExpCentered &other) = delete;
		GuiCurveExpCentered(GuiCurveExpCentered &&other) = delete;
		GuiCurveExpCentered& operator=(const GuiCurveExpCentered &other) = delete;
		GuiCurveExpCentered& operator=(GuiCurveExpCentered &&other) = delete;
		virtual ~GuiCurveExpCentered();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotLeftDZModified(double ldz);
		void slotCenterDZModified(double cdz);
		void slotRightDZModified(double rdz);
		void slotCurveParamModified(double curveParam);
		void slotZoomModified(double zoom);
		
		
	private:
		float m_leftDZ;
		float m_centerDZ;
		float m_rightDZ;
		float m_curveParam;
		float m_zoom;
		CurveExpCenteredWidget *m_widget;
		
		float m_m;
		float m_M;
		float m_cM;
		float m_cm;
};


#include <QGroupBox>
class QGridLayout;
class QLabel;
class QDoubleSpinBox;


class CurveExpCenteredWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		CurveExpCenteredWidget();
		CurveExpCenteredWidget(const CurveExpCenteredWidget &other) = delete;
		CurveExpCenteredWidget(CurveExpCenteredWidget &&other) = delete;
		CurveExpCenteredWidget& operator=(const CurveExpCenteredWidget &other) = delete;
		CurveExpCenteredWidget& operator=(CurveExpCenteredWidget &&other) = delete;
		virtual ~CurveExpCenteredWidget() = default;
		
		
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

