#ifndef GUI_CURVE_POLYNOMIAL_3_NOTCENTERED
#define GUI_CURVE_POLYNOMIAL_3_NOTCENTERED


#include "AbstractAxisCurve.h"
class CurvePolynomial3NotCenteredWidget;


class GuiCurvePolynomial3NotCentered : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		GuiCurvePolynomial3NotCentered(float leftDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f);
		GuiCurvePolynomial3NotCentered(const GuiCurvePolynomial3NotCentered &other) = delete;
		GuiCurvePolynomial3NotCentered(GuiCurvePolynomial3NotCentered &&other) = delete;
		GuiCurvePolynomial3NotCentered& operator=(const GuiCurvePolynomial3NotCentered &other) = delete;
		GuiCurvePolynomial3NotCentered& operator=(GuiCurvePolynomial3NotCentered &&other) = delete;
		virtual ~GuiCurvePolynomial3NotCentered();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotLeftDZModified(double ldz);
		void slotRightDZModified(double rdz);
		void slotCurveParamModified(double curveParam);
		
		
	private:
		float m_leftDZ;
		float m_rightDZ;
		float m_curveParam;
		CurvePolynomial3NotCenteredWidget *m_widget;
		
		float m_m;
		float m_M;
};


#include <QGroupBox>
class QGridLayout;
class QLabel;
class QDoubleSpinBox;


class CurvePolynomial3NotCenteredWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		CurvePolynomial3NotCenteredWidget();
		CurvePolynomial3NotCenteredWidget(const CurvePolynomial3NotCenteredWidget &other) = delete;
		CurvePolynomial3NotCenteredWidget(CurvePolynomial3NotCenteredWidget &&other) = delete;
		CurvePolynomial3NotCenteredWidget& operator=(const CurvePolynomial3NotCenteredWidget &other) = delete;
		CurvePolynomial3NotCenteredWidget& operator=(CurvePolynomial3NotCenteredWidget &&other) = delete;
		virtual ~CurvePolynomial3NotCenteredWidget() = default;
		
		
	signals:
		void leftDZModified(double newLeftDZ);
		void rightDZModified(double newRightDZ);
		void curveParamModified(double newCurve);
		
		
	private:
		QGridLayout *layout;
		QLabel *labelLDZ, *labelRDZ, *labelCurve;
		QDoubleSpinBox *boxLDZ, *boxRDZ, *boxCurve;
};


#endif

