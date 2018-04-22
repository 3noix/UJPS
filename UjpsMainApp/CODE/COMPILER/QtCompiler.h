#ifndef QT_COMPILER
#define QT_COMPILER

#include "AbstractCompiler.h"
class QtCompilationProcess;

class QGroupBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class QCheckBox;


class QtCompiler : public AbstractCompiler
{
	Q_OBJECT
	
	public:
		explicit QtCompiler();
		QtCompiler(const QtCompiler &other) = delete;
		QtCompiler(QtCompiler &&other) = delete;
		QtCompiler& operator=(const QtCompiler &other) = delete;
		QtCompiler& operator=(QtCompiler &&other) = delete;
		virtual ~QtCompiler();
		
		QString compilatorName() const;
		virtual void runCompilation() override;
		virtual void stopCompilation() override;
		virtual QWidget* settingsWidget() const override;
		virtual bool isRunning() const override;
		
		
	private:
		void createWidget();
		bool readSettings();
		bool writeSettings();
		
		QtCompilationProcess *m_process;
		
		QGroupBox *boxSettings;
		QGridLayout *boxLayout;
		QLabel *labelQtBinaryDirPath, *labelMingwBinaryDirPath;
		QLineEdit *lineQtBinaryDirPath, *lineMingwBinaryDirPath;
		QCheckBox *checkDebug, *checkRelease;
};


#endif





