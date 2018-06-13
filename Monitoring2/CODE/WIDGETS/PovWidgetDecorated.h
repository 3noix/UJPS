#ifndef POV_WIDGET_DECORATED
#define POV_WIDGET_DECORATED


#include <QWidget>
class QVBoxLayout;
class PovWidget;
class QLabel;


class PovWidgetDecorated : public QWidget
{
	Q_OBJECT
	
	public:
		PovWidgetDecorated(const QString &name, QWidget *parent = nullptr);
		PovWidgetDecorated(const PovWidgetDecorated &other) = delete;
		PovWidgetDecorated(PovWidgetDecorated &&other) = delete;
		PovWidgetDecorated& operator=(const PovWidgetDecorated &other) = delete;
		PovWidgetDecorated& operator=(PovWidgetDecorated &&other) = delete;
		virtual ~PovWidgetDecorated() = default;
		
		float angle() const;
		
		
	public slots:
		void slotSetAngle(float angle);
		
		
	private:
		QVBoxLayout *layout;
		PovWidget *p;
		QLabel *label;
};


#endif

