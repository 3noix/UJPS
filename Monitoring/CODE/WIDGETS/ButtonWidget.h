#ifndef BUTTON_WIDGET
#define BUTTON_WIDGET


#include <QWidget>


class ButtonWidget : public QWidget
{
	Q_OBJECT
	
	public:
		ButtonWidget(int i, bool enabled, QWidget *parent = nullptr);
		ButtonWidget(const ButtonWidget &other) = delete;
		ButtonWidget(ButtonWidget &&other) = delete;
		ButtonWidget& operator=(const ButtonWidget &other) = delete;
		ButtonWidget& operator=(ButtonWidget &&other) = delete;
		virtual ~ButtonWidget() = default;
		
		bool isChecked() const;
		
		
	public slots:
		void slotSetChecked(bool checked);
		
		
	protected:
		virtual void paintEvent(QPaintEvent *e);
		
		
	private:
		bool m_enabled;
		bool m_checked;
		QString m_text;
};


#endif

