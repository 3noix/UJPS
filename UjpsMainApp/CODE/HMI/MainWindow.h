#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QMainWindow>
#include <QCloseEvent>
class QMenu;
class QToolBar;
class QStatusBar;
class QAction;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QToolBar;
class QLabel;
class QSpinBox;

class TextEdit;
class CompilationWidget;
class ProfileEngine;


enum class HmiState
{
	NoProfileSelected,
	ReadyToPlayNotLoaded,
	Loading,
	ReadyToPlayLoaded,
	Initializing,
	Playing,
	Quitting
	// no need of a state for Compiling as the compiler window is modal
};


class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QString proFilePath, int dtms, bool bPlay, QWidget *parent = nullptr);
		MainWindow(const MainWindow &other) = delete;
		MainWindow(MainWindow &&other) = delete;
		MainWindow& operator=(const MainWindow &other) = delete;
		MainWindow& operator=(MainWindow &&other) = delete;
		virtual ~MainWindow();
		
		
	private slots:
		void slotBrowseButtonClicked();
		void slotSettings();
		void slotClose();
		void slotCompilation();
		void slotPlay1();
		void slotPlay2(bool bLoadOk);
		void slotPlay3(bool bInitOk);
		void slotStop();
		void slotUnload();
		
		void slotRunControllersInfo();
		void slotRunMonitoring();
		void slotRunAxesCurves();
		
		
	protected:
		void closeEvent(QCloseEvent *event);
		
		
	private:
		void setState(HmiState s);
		void createActions();
		void createMenus();
		void createToolBar();
		void setupWidget();
		
		QAction *actionQuit, *actionSettings;
		QAction *actionCompilation, *actionPlay, *actionStop, *actionUnload;
		QAction *actionRunControllersInfo, *actionRunMonitoring, *actionRunAxesCurves;
		
		QMenu *fileMenu, *profileMenu, *toolsMenu;
		QToolBar *toolbar;
		QStatusBar *statusbar;
		
		QWidget *mainWidget;
		TextEdit *textEdit;
		QVBoxLayout *layout;
		QHBoxLayout *layoutDllChoice, *layoutRefreshRate;
		QPushButton *boutonBrowse;
		QLineEdit *lineDllPath;
		QLabel *labelRefreshRate;
		QSpinBox *boxRefreshRate;
		
		QString m_proFilePath;
		QString m_dllFilePath;
		QString m_dllFileName;
		CompilationWidget *m_compilWidget;
		ProfileEngine *m_engine;
};


#endif

