#ifndef STANDARD_JOYSTICK_WIDGET
#define STANDARD_JOYSTICK_WIDGET


class QGameController;
class QGameControllerAxisEvent;
class QGameControllerButtonEvent;
class QGameControllerPovEvent;

#include <QtWidgets>
class AxisWidget;
class ButtonWidget;
class PovWidgetDecorated;


class StandardJoystickWidget : public QWidget
{
	Q_OBJECT
	
	public:
		StandardJoystickWidget(QGameController *j, bool own = true);
		StandardJoystickWidget(const StandardJoystickWidget &other) = delete;
		StandardJoystickWidget(StandardJoystickWidget &&other) = delete;
		StandardJoystickWidget& operator=(const StandardJoystickWidget &other) = delete;
		StandardJoystickWidget& operator=(StandardJoystickWidget &&other) = delete;
		virtual ~StandardJoystickWidget();
		
		
	private slots:
		void slotJoystickAxisValueChanged(QGameControllerAxisEvent *event);
		void slotJoystickButtonStateChanged(QGameControllerButtonEvent *event);
		void slotJoystickPovAngleChanged(QGameControllerPovEvent *event);
		
		
	private:
		QGameController *m_joystick;
		QTimer *m_timer;
		bool m_own;
		
		void setupWidget();
		void initState();
		
		QHBoxLayout *layout1;
		QVBoxLayout *layout2;
		QHBoxLayout *layout3;
		QVBoxLayout *axesLayout;
		QGridLayout *buttonsLayout;
		QGroupBox *boxAxes, *boxButtons, *boxPov;
		QVector<AxisWidget*> axesWidgets;
		QVector<ButtonWidget*> buttonsWidgets;
		QVector<PovWidgetDecorated*> povWidgets;
};

#endif
