#ifndef STANDARD_JOYSTICK_WIDGET
#define STANDARD_JOYSTICK_WIDGET


#include <QtWidgets>
class AbstractRealJoystick;
class ButtonWidget;


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
		
		
	private slots:
		void slotRunOneLoop();
		
		
	private:
		AbstractRealJoystick *m_joystick;
		QTimer *m_timer;
		bool m_own;
		
		void setupWidget();
		void initState();
		QHBoxLayout *layout;
		QGridLayout *axesLayout, *buttonsLayout;
		QGroupBox *boxAxes, *boxButtons, *boxPov;
		QVector<QLabel*> axesLabels;
		QVector<QSlider*> axesSliders;
		QVector<QLabel*> axesValues;
		QVector<ButtonWidget*> buttonsChecks;
};

#endif
