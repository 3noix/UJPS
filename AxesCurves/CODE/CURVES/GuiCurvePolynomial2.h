#ifndef GUI_CURVE_POLYNOMIAL_2
#define GUI_CURVE_POLYNOMIAL_2


#include "AbstractAxisCurve.h"
class CurvePolynomial2Widget;


class GuiCurvePolynomial2 : public AbstractAxisCurve
{
	Q_OBJECT
	
	public:
		GuiCurvePolynomial2(float zoom = 0.0f);
		GuiCurvePolynomial2(const GuiCurvePolynomial2 &other) = delete;
		GuiCurvePolynomial2(GuiCurvePolynomial2 &&other) = delete;
		GuiCurvePolynomial2& operator=(const GuiCurvePolynomial2 &other) = delete;
		GuiCurvePolynomial2& operator=(GuiCurvePolynomial2 &&other) = delete;
		virtual ~GuiCurvePolynomial2();
		
		virtual float run(float in) override final;
		virtual QWidget* settingsWidget() override final;
		
		
	private slots:
		void slotZoomModified(double zoom);
		
		
	private:
		float m_zoom;
		CurvePolynomial2Widget *m_widget;
};


#include <QGroupBox>
class QHBoxLayout;
class QLabel;
class QDoubleSpinBox;


class CurvePolynomial2Widget : public QGroupBox
{
	Q_OBJECT
	
	public:
		CurvePolynomial2Widget();
		CurvePolynomial2Widget(const CurvePolynomial2Widget &other) = delete;
		CurvePolynomial2Widget(CurvePolynomial2Widget &&other) = delete;
		CurvePolynomial2Widget& operator=(const CurvePolynomial2Widget &other) = delete;
		CurvePolynomial2Widget& operator=(CurvePolynomial2Widget &&other) = delete;
		virtual ~CurvePolynomial2Widget() = default;
		
		
	signals:
		void zoomModified(double newZoom);
		
		
	private:
		QHBoxLayout *layout;
		QLabel *labelZoom;
		QDoubleSpinBox *boxZoom;
};


#endif
