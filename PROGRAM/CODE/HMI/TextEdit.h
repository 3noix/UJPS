#ifndef TEXT_EDIT
#define TEXT_EDIT


#include <QTextEdit>
#include <QColor>


class TextEdit : public QTextEdit
{
	Q_OBJECT
	
	public:
		explicit TextEdit(QWidget *parent = nullptr);
		TextEdit(const TextEdit &other) = delete;
		TextEdit(TextEdit &&other) = delete;
		TextEdit& operator=(const TextEdit &other) = delete;
		TextEdit& operator=(TextEdit &&other) = delete;
		virtual ~TextEdit() = default;
		
		
	public slots:
		void addMessage(const QString &msg, QColor color);
		
		
	private:
		void createActions();
		virtual void contextMenuEvent(QContextMenuEvent *event) override;
		
		QAction *actionClear, *actionCopy, *actionSelectAll;
		QMenu *m_menu;
};

#endif




