#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QtWidgets>


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
		void slotUpdate();
		
		
	private:
		void createActions();
		void createMenus();
		void setupWidget();
		void clearTabs();
		
		QAction *actionUpdate, *actionQuit;
		QMenu *fileMenu;
		
		QWidget *mainWidget;
		QVBoxLayout *layout;
		QHBoxLayout *layoutUp;
		QLabel *labelMode;
		QComboBox *boxMode;
		
		QTabWidget *tabs;
		QLabel *labelNoController;
};

#endif
