#ifndef STANDARD_JOYSTICK_WIDGET
#define STANDARD_JOYSTICK_WIDGET


#include <QtWidgets>
class AbstractRealJoystick;
class AxesWidget;
class ButtonWidget;
class PovWidgetDecorated;


class StandardJoystickWidget : public QWidget
{
	Q_OBJECT
	
	public:
		StandardJoystickWidget(AbstractRealJoystick *j, bool own = true);
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
		
		
	private:
		AbstractRealJoystick *m_joystick;
		QTimer *m_timer;
		bool m_own;
		
		void setupWidget();
		void initState();
		
		QHBoxLayout *layout1;
		QVBoxLayout *layout2;
		QHBoxLayout *layout3;
		QGridLayout *buttonsLayout;
		AxesWidget *boxAxes;
		QGroupBox *boxButtons, *boxPov;
		QVector<ButtonWidget*> buttonsWidgets;
		QVector<PovWidgetDecorated*> povWidgets;
};

#endif
