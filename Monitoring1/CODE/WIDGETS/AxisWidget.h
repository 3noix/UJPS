#ifndef AXIS_WIDGET
#define AXIS_WIDGET


#include <QWidget>
class QHBoxLayout;
class QSlider;
class QLabel;


class AxisWidget : public QWidget
{
	Q_OBJECT
	
	public:
		AxisWidget(const QString &name, QWidget *parent = nullptr);
		AxisWidget(const AxisWidget &other) = delete;
		AxisWidget(AxisWidget &&other) = delete;
		AxisWidget& operator=(const AxisWidget &other) = delete;
		AxisWidget& operator=(AxisWidget &&other) = delete;
		virtual ~AxisWidget() = default;
		
		float value() const;
		
		
	public slots:
		void slotSetValue(float value);
		
		
	private:
		float m_value;
		
		QHBoxLayout *layout;
		QLabel *label1;
		QSlider *slider;
		QLabel *label2;
};


#endif

