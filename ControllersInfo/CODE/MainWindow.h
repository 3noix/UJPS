#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QtWidgets>
class WorkerThread;
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
		virtual ~MainWindow() = default;
		
		
	private slots:
		void slotStartUpdate();
		void slotEndUpdate();
		void slotQuit();
		
		
	private:
		void setData(const QVector<GameController*> joysticks);
		
		void createActions();
		void createMenus();
		void setupWidget();
		
		void createHeaders();
		void clearLayout();
		
		QAction *actionUpdate, *actionQuit;
		QMenu *fileMenu;
		
		QStackedWidget *stack;
		QWidget *gridWidget, *widgetLoading;
		QGridLayout *layout;
		QVBoxLayout *layoutLoading;
		QLabel *labelLoading, *labelGif;
		QMovie *movieGif;
		
		WorkerThread *m_thread;
};


#endif

