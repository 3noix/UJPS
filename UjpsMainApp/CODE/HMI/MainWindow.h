#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QWidget>
#include <QCloseEvent>
class TextEdit;
class QVBoxLayout;
class QHBoxLayout;
class QAction;
class QPushButton;
class QLineEdit;
class QToolBar;
class QLabel;
class QSpinBox;
class QCheckBox;

class CompilationWidget;
class ProfileEngine;


enum class HmiState
{
	WaitingForDll,
	ReadyToPlayNotLoaded,
	ReadyToPlayLoaded,
	Playing,
	Quitting
	// no need of a state for Compiling as the compiler window is modal
};


class MainWindow : public QWidget
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
		void slotCompilation();
		void slotPlay();
		void slotStop();
		void slotUnload();
		
		
	protected:
		void closeEvent(QCloseEvent *event);
		
		
	private:
		void setState(HmiState s);
		void createActions();
		void setupWidget();
		
		QAction *actionSettings, *actionCompilation;
		QAction *actionPlay, *actionStop, *actionUnload;
		
		TextEdit *textEdit;
		QVBoxLayout *layout;
		QHBoxLayout *layoutDllChoice, *layoutRefreshRate;
		QPushButton *boutonBrowse;
		QLineEdit *lineDllPath;
		QToolBar *toolbar;
		QLabel *labelRefreshRate;
		QSpinBox *boxRefreshRate;
		QCheckBox *chkMappingRepeater;
		
		QString m_proFilePath;
		QString m_dllFilePath;
		QString m_dllFileName;
		CompilationWidget *m_compilWidget;
		ProfileEngine *m_engine;
};

#endif

