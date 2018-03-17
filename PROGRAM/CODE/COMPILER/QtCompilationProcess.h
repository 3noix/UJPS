#ifndef QT_COMPILATION_PROCESS
#define QT_COMPILATION_PROCESS

#include <QProcess>
#include <QColor>


class QtCompilationProcess : public QProcess
{
	Q_OBJECT
	
	public:
		explicit QtCompilationProcess();
		QtCompilationProcess(const QtCompilationProcess &other) = delete;
		QtCompilationProcess(QtCompilationProcess &&other) = delete;
		QtCompilationProcess& operator=(const QtCompilationProcess &other) = delete;
		QtCompilationProcess& operator=(QtCompilationProcess &&other) = delete;
		~QtCompilationProcess();
		
		void setupEnvironmentForQtUsage(const QString &qtDir, const QString &mingwDir);
		void beginCompilation(const QString &directory, const QString &projectFile, bool debugMode, bool releaseMode);	
		void killCompilation();
		
		
	signals:
		void compilationMessage(QString str, QColor color);
		void compilationFinished();
		
		
	private slots:
		void slotContinueCompilation(int exitCode, QProcess::ExitStatus exitStatus);
		void slotError(QProcess::ProcessError processError);
		void slotAddTextStdout();
		void slotAddTextStderr();
		
		
	private:
		bool m_killed;
		
		bool B_QMAKE_PASS;
		bool B_MAKE_DEBUG_PASS;
		bool B_MAKE_RELEASE_PASS;
		bool B_ERROR;
		bool B_DEBUG_RQT;
		bool B_RELEASE_RQT;
		
		QString m_qtDir;
		QString m_mingwDir;
};


#endif





