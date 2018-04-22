#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QWidget>
#include <QCloseEvent>
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QLabel;
class QDoubleSpinBox;
class QComboBox;
class QTimer;

#include "RealJoysticksManager.h"
class CurveChartView;
class AbstractAxisCurve;


class MainWindow : public QWidget
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = nullptr);
		MainWindow(const MainWindow &other) = delete;
		MainWindow(MainWindow &&other) = delete;
		MainWindow& operator=(const MainWindow &other) = delete;
		MainWindow& operator=(MainWindow &&other) = delete;
		virtual ~MainWindow();
		
		
	private slots:
		void slotRunOneLoop();
		
		void slotJoystickChanged(int index);
		void slotAxisChanged(int axis);
		void slotDirectionChanged(int index);
		void slotTrim1Changed(double trim1);
		void slotTrim2Changed(double trim2);
		void slotCurveChanged(int index);
		
		
	private:
		void setupWidget();
		
		QStringList curvesNames() const;
		AbstractAxisCurve* createCurve(const QString &curveName) const;
		
		QGridLayout *layout;
		QLabel *labelJoystick, *labelAxis, *labelDirection;
		QLabel *labelTrim1, *labelTrim2, *labelCurve;
		QComboBox *boxJoystick, *boxAxis, *boxDirection, *boxCurve;
		QDoubleSpinBox *boxTrim1, *boxTrim2;
		CurveChartView *chartView;
		
		QTimer *m_timer;
		RealJoysticksManager m_joyManager;
		AbstractRealJoystick *m_currentJoystick;
		int m_axis;
		
		AbstractAxisCurve *m_curve;
		QWidget *m_settingsWidget;
};

#endif

