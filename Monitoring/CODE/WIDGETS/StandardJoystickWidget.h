#ifndef STANDARD_JOYSTICK_WIDGET
#define STANDARD_JOYSTICK_WIDGET


#include <QtWidgets>
class AbstractRealJoystick;
class AxesWidget;
class ButtonWidget;
class PovWidgetDecorated;
class MyChartWidget;


class StandardJoystickWidget : public QWidget
{
	Q_OBJECT
	
	public:
		StandardJoystickWidget(AbstractRealJoystick *j, bool own = true, QWidget *parent = nullptr);
		StandardJoystickWidget(const StandardJoystickWidget &other) = delete;
		StandardJoystickWidget(StandardJoystickWidget &&other) = delete;
		StandardJoystickWidget& operator=(const StandardJoystickWidget &other) = delete;
		StandardJoystickWidget& operator=(StandardJoystickWidget &&other) = delete;
		virtual ~StandardJoystickWidget();
		
		void joystickButtonStateChanged(uint button, bool bPressed);
		void joystickAxisValueChanged(uint axis, float value);
		void joystickPovAngleChanged(uint pov, float value);
		
		
	private slots:
		void slotRunOneLoop();
		void slotUpdateTempoCurves(uint axis, bool bDisplay);
		
		
	private:
		AbstractRealJoystick *m_joystick;
		QTimer *m_timer;
		bool m_own;
		
		void setupWidget();
		void initState();
		
		QVBoxLayout *layout1;
		QHBoxLayout *layout2;
		QVBoxLayout *layout3;
		QHBoxLayout *layout4;
		QGridLayout *buttonsLayout;
		AxesWidget *boxAxes;
		QGroupBox *boxButtons, *boxPov;
		QVector<ButtonWidget*> buttonsWidgets;
		QVector<PovWidgetDecorated*> povWidgets;
		MyChartWidget *tempoChart;
		
		const int ratioTempoChart = 4;
		int compteur;
};


#endif

