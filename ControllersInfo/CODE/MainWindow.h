#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QtWidgets>
#include "VigemPidWhiteLister.h"
class GameControllersEnumThread;
class GameController;


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
		void slotSettings();
		void slotStartUpdate();
		void slotEndUpdate();
		void slotQuit();
		
		
	private:
		void setData(const QVector<GameController*> joysticks);
		
		void createActions();
		void createMenus();
		void setupWidget();
		
		void createHeaders(bool bVigemColumn);
		void clearLayout();
		
		QAction *actionSettings, *actionUpdate, *actionQuit;
		QMenu *fileMenu;
		
		QStackedWidget *stack;
		QWidget *gridWidget, *widgetLoading;
		QGridLayout *layout;
		QVBoxLayout *layoutLoading;
		QLabel *labelLoading, *labelGif;
		QMovie *movieGif;
		
		GameControllersEnumThread *m_thread;
		
		VigemPidWhiteLister m_vigemInterface;
};


#endif

