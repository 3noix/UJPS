#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QMainWindow>
#include <QCloseEvent>
#include "RealJoysticksManager.h"
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QLabel;
class QDoubleSpinBox;
class QComboBox;
class QStackedWidget;
class QTimer;
class QMenu;
class QMovie;

class WorkerThread;
class CurveChartView;
class AbstractAxisCurve;
class AbstractRealJoystick;


class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = nullptr);
		MainWindow(const MainWindow &other) = delete;
		MainWindow(MainWindow &&other) = delete;
		MainWindow& operator=(const MainWindow &other) = delete;
		MainWindow& operator=(MainWindow &&other) = delete;
		virtual ~MainWindow() = default;
		
		
	private slots:
		void slotUpdate();
		void slotEndUpdate();
		void slotQuit();
		
		void slotRunOneLoop();
		
		void slotJoystickChanged(int index);
		void slotAxisChanged(int axis);
		void slotDirectionChanged(int index);
		void slotTrim1Changed(double trim1);
		void slotTrim2Changed(double trim2);
		void slotCurveChanged(int index);
		
		
	private:
		void createActions();
		void createMenus();
		void setupWidget();
		
		QStringList curvesNames() const;
		AbstractAxisCurve* createCurve(const QString &curveName) const;
		
		QAction *actionUpdate, *actionQuit;
		QMenu *fileMenu;
		
		QStackedWidget *stack;
		QWidget *mainWidget;
		QGridLayout *layout;
		QLabel *labelJoystick, *labelAxis, *labelDirection;
		QLabel *labelTrim1, *labelTrim2, *labelCurve;
		QComboBox *boxJoystick, *boxAxis, *boxDirection, *boxCurve;
		QDoubleSpinBox *boxTrim1, *boxTrim2;
		CurveChartView *chartView;
		
		QWidget *widgetLoading;
		QVBoxLayout *layoutLoading;
		QLabel *labelLoading, *labelGif;
		QMovie *movieGif;
		
		QTimer *m_timer;
		WorkerThread *m_thread;
		RealJoysticksManager m_jm;
		AbstractRealJoystick *m_currentJoystick;
		int m_axis;
		
		AbstractAxisCurve *m_curve;
		QWidget *m_settingsWidget;
};


#endif

