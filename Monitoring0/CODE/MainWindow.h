#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QtWidgets>
class QGameController;


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
		
		
	private:
		QTabWidget *mainTabWidget;
		QVector<QWidget*> joysticksWidgets;
		QVector<QGameController*> joysticks;
};

#endif
