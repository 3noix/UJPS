#ifndef STANDARD_JOYSTICK_WIDGET_RAW
#define STANDARD_JOYSTICK_WIDGET_RAW


#include "QtGameControllerModif/GameControllerEvents.h"
class GameController;

#include <QtWidgets>
#include <vector>
class AxesWidget;
class ButtonWidget;
class PovWidgetDecorated;
class MyChartWidget;


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
		void slotRunOneLoop();
		void slotJoystickAxisValueChanged(GameControllerAxisEvent event);
		void slotJoystickButtonStateChanged(GameControllerButtonEvent event);
		void slotJoystickPovAngleChanged(GameControllerPovEvent event);
		void slotUpdateTempoCurves(uint axis, bool bDisplay);
		
		
	private:
		GameController *m_joystick;
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
		std::vector<ButtonWidget*> buttonsWidgets;
		std::vector<PovWidgetDecorated*> povWidgets;
		MyChartWidget *tempoChart;
		
		const int ratioTempoChart = 4;
		int compteur;
};


#endif

