#ifndef GUI_CURVE_EXP_NOTCENTERED
#define GUI_CURVE_EXP_NOTCENTERED


#include "AbstractAxisCurve.h"
class CurveExpNotCenteredWidget;


class GuiCurveExpNotCentered : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		GuiCurveExpNotCentered(float leftDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f, float zoom = 0.0f);
		GuiCurveExpNotCentered(const GuiCurveExpNotCentered &other) = delete;
		GuiCurveExpNotCentered(GuiCurveExpNotCentered &&other) = delete;
		GuiCurveExpNotCentered& operator=(const GuiCurveExpNotCentered &other) = delete;
		GuiCurveExpNotCentered& operator=(GuiCurveExpNotCentered &&other) = delete;
		virtual ~GuiCurveExpNotCentered();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotLeftDZModified(double ldz);
		void slotRightDZModified(double rdz);
		void slotCurveParamModified(double curveParam);
		void slotZoomModified(double zoom);
		
		
	private:
		float m_leftDZ;
		float m_rightDZ;
		float m_curveParam;
		float m_zoom;
		CurveExpNotCenteredWidget *m_widget;
		
		float m_m;
		float m_M;
};


#include <QGroupBox>
class QGridLayout;
class QLabel;
class QDoubleSpinBox;


class CurveExpNotCenteredWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		CurveExpNotCenteredWidget();
		CurveExpNotCenteredWidget(const CurveExpNotCenteredWidget &other) = delete;
		CurveExpNotCenteredWidget(CurveExpNotCenteredWidget &&other) = delete;
		CurveExpNotCenteredWidget& operator=(const CurveExpNotCenteredWidget &other) = delete;
		CurveExpNotCenteredWidget& operator=(CurveExpNotCenteredWidget &&other) = delete;
		virtual ~CurveExpNotCenteredWidget() = default;
		
		
	signals:
		void leftDZModified(double newLeftDZ);
		void rightDZModified(double newRightDZ);
		void curveParamModified(double newCurve);
		void zoomModified(double newZoom);
		
		
	private:
		QGridLayout *layout;
		QLabel *labelLDZ, *labelRDZ, *labelCurve, *labelZoom;
		QDoubleSpinBox *boxLDZ, *boxRDZ, *boxCurve, *boxZoom;
};

#endif
