#ifndef STANDARD_JOYSTICK_WIDGET
#define STANDARD_JOYSTICK_WIDGET


class GameController;
class GameControllerAxisEvent;
class GameControllerButtonEvent;
class GameControllerPovEvent;

#include <QtWidgets>
class AxesWidget;
class ButtonWidget;
class PovWidgetDecorated;


class StandardJoystickWidget : public QWidget
{
	Q_OBJECT
	
	public:
		StandardJoystickWidget(GameController *j, bool own = true);
		StandardJoystickWidget(const StandardJoystickWidget &other) = delete;
		StandardJoystickWidget(StandardJoystickWidget &&other) = delete;
		StandardJoystickWidget& operator=(const StandardJoystickWidget &other) = delete;
		StandardJoystickWidget& operator=(StandardJoystickWidget &&other) = delete;
		virtual ~StandardJoystickWidget();
		
		
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
