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
		virtual ~MainWindow() = default;
		
		
	private slots:
		void slotUpdate();
		
		
	private:
		void createActions();
		void createMenus();
		void setupWidget();
		
		void createHeaders();
		void clearLayout();
		
		QAction *actionUpdate, *actionQuit;
		QMenu *fileMenu;
		
		QWidget *w;
		QGridLayout *layout;
};


#endif

