#ifndef ABSTRACT_COMPILER
#define ABSTRACT_COMPILER


#include <QObject>
#include <QColor>
class CompilatorsCenter;


class AbstractCompiler : public QObject
{
	Q_OBJECT
	
	public:
		explicit AbstractCompiler() = default;
		AbstractCompiler(const AbstractCompiler &other) = delete;
		AbstractCompiler(AbstractCompiler &&other) = delete;
		AbstractCompiler& operator=(const AbstractCompiler &other) = delete;
		AbstractCompiler& operator=(AbstractCompiler &&other) = delete;
		virtual ~AbstractCompiler() = default;
		
		void setCenter(CompilatorsCenter *c);
		
		virtual QString compilatorName() const = 0;
		virtual void runCompilation() = 0;
		virtual void stopCompilation() = 0;
		virtual QWidget* settingsWidget() const = 0;
		virtual bool isRunning() const = 0;
		
		void setCompilationDirectory(const QString &dir) {m_compilationDirectory = dir;};
		
		
	signals:
		void compilationMessage(QString str, QColor color);
		void compilationFinished();
		
		
	protected:
		QString compilationDirectory() const {return m_compilationDirectory;};
		
		
	private:
		QString m_compilationDirectory;
};


#endif





