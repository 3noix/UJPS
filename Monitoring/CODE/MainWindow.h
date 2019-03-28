#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QtWidgets>
#include "VigemPidWhiteLister.h"
class GameControllersEnumThread;
class GameController;
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
		virtual ~MainWindow();
		
		
	private slots:
		void slotModeChanged(int index);
		void slotSettings();
		void slotUpdate();
		void slotEndUpdate();
		void slotQuit();
		
		
	private:
		void setData(const QVector<GameController*> joysticks);
		void setData(const QVector<AbstractRealJoystick*> joysticks);
		
		void createActions();
		void createMenus();
		void setupWidget();
		void clearTabs();
		
		QAction *actionSettings, *actionUpdate, *actionQuit;
		QMenu *fileMenu;
		
		QWidget *mainWidget;
		QStackedWidget *stack;
		QVBoxLayout *layout;
		QHBoxLayout *layoutUp;
		QLabel *labelMode;
		QComboBox *boxMode;
		
		QWidget *widgetLoading;
		QVBoxLayout *layoutLoading;
		QLabel *labelLoading, *labelGif;
		QMovie *movieGif;
		
		QTabWidget *tabs;
		QLabel *labelNoController;
		
		GameControllersEnumThread *m_thread;
		int m_index;
		
		VigemPidWhiteLister m_vigemInterface;
};


#endif

