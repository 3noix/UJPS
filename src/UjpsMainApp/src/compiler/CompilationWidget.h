#ifndef COMPILATION_WIDGET
#define COMPILATION_WIDGET


#include <QWidget>
class AbstractCompiler;
class QGridLayout;
class QCloseEvent;
class QPushButton;
class TextEdit;


class CompilationWidget : public QWidget
{
	Q_OBJECT
	
	public:
		explicit CompilationWidget(QWidget *parent = nullptr);
		CompilationWidget(const CompilationWidget &other) = delete;
		CompilationWidget(CompilationWidget &&other) = delete;
		CompilationWidget& operator=(const CompilationWidget &other) = delete;
		CompilationWidget& operator=(CompilationWidget &&other) = delete;
		virtual ~CompilationWidget();
		
		void setProjectDirectory(const QString &projectDir);
		
		
	public slots:
		void slotRun();
		void slotStop();
		void slotClose();
		void slotCompilationFinished();
		void slotMessage(const QString &message, const QColor &color);
		
		
	protected:
		virtual void closeEvent(QCloseEvent *event) override;
		virtual void keyPressEvent(QKeyEvent *event) override;
		
		
	private:
		void setupWidget();
		
		// data
		QString m_projectDirectory;
		
		// ihm
		QGridLayout *layout;
		TextEdit *textEdit;
		QPushButton *boutonRun, *boutonStop, *boutonClose;
		
		// compiler
		AbstractCompiler *m_compiler;
		QWidget *boxSettings;
};


#endif

