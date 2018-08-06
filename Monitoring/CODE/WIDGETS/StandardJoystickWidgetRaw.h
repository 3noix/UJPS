#ifndef STANDARD_JOYSTICK_WIDGET_RAW
#define STANDARD_JOYSTICK_WIDGET_RAW


class GameController;
class GameControllerAxisEvent;
class GameControllerButtonEvent;
class GameControllerPovEvent;

#include <QtWidgets>
class AxesWidget;
class ButtonWidget;
class PovWidgetDecorated;


class StandardJoystickWidgetRaw : public QWidget
{
	Q_OBJECT
	
	public:
		StandardJoystickWidgetRaw(GameController *j, bool own = true, QWidget *parent = nullptr);
		StandardJoystickWidgetRaw(const StandardJoystickWidgetRaw &other) = delete;
		StandardJoystickWidgetRaw(StandardJoystickWidgetRaw &&other) = delete;
		StandardJoystickWidgetRaw& operator=(const StandardJoystickWidgetRaw &other) = delete;
		StandardJoystickWidgetRaw& operator=(StandardJoystickWidgetRaw &&other) = delete;
		virtual ~StandardJoystickWidgetRaw();
		
		
	private slots:
		void slotJoystickAxisValueChanged(GameControllerAxisEvent *event);
		void slotJoystickButtonStateChanged(GameControllerButtonEvent *event);
		void slotJoystickPovAngleChanged(GameControllerPovEvent *event);
		
		
	private:
		GameController *m_joystick;
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
