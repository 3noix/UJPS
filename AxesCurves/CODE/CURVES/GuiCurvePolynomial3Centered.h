#ifndef GUI_CURVE_POLYNOMIAL_3_CENTERED
#define GUI_CURVE_POLYNOMIAL_3_CENTERED


#include "AbstractAxisCurve.h"
class CurvePolynomial3CenteredWidget;


class GuiCurvePolynomial3Centered : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		GuiCurvePolynomial3Centered(float leftDZ = 0.0f, float centerDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f);
		GuiCurvePolynomial3Centered(const GuiCurvePolynomial3Centered &other) = delete;
		GuiCurvePolynomial3Centered(GuiCurvePolynomial3Centered &&other) = delete;
		GuiCurvePolynomial3Centered& operator=(const GuiCurvePolynomial3Centered &other) = delete;
		GuiCurvePolynomial3Centered& operator=(GuiCurvePolynomial3Centered &&other) = delete;
		virtual ~GuiCurvePolynomial3Centered();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotLeftDZModified(double ldz);
		void slotCenterDZModified(double cdz);
		void slotRightDZModified(double rdz);
		void slotCurveParamModified(double curveParam);
		
		
	private:
		float m_leftDZ;
		float m_centerDZ;
		float m_rightDZ;
		float m_curveParam;
		CurvePolynomial3CenteredWidget *m_widget;
		
		float m_m;
		float m_M;
		float m_cM;
		float m_cm;
};


#include <QGroupBox>
class QGridLayout;
class QLabel;
class QDoubleSpinBox;


class CurvePolynomial3CenteredWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		CurvePolynomial3CenteredWidget();
		CurvePolynomial3CenteredWidget(const CurvePolynomial3CenteredWidget &other) = delete;
		CurvePolynomial3CenteredWidget(CurvePolynomial3CenteredWidget &&other) = delete;
		CurvePolynomial3CenteredWidget& operator=(const CurvePolynomial3CenteredWidget &other) = delete;
		CurvePolynomial3CenteredWidget& operator=(CurvePolynomial3CenteredWidget &&other) = delete;
		virtual ~CurvePolynomial3CenteredWidget() = default;
		
		
	signals:
		void leftDZModified(double newLeftDZ);
		void centerDZModified(double newCenterDZ);
		void rightDZModified(double newRightDZ);
		void curveParamModified(double newCurve);
		
		
	private:
		QGridLayout *layout;
		QLabel *labelLDZ, *labelCDZ, *labelRDZ, *labelCurve;
		QDoubleSpinBox *boxLDZ, *boxCDZ, *boxRDZ, *boxCurve;
};

#endif
