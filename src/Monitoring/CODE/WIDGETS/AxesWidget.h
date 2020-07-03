#ifndef AXES_WIDGET
#define AXES_WIDGET


#include <QGroupBox>
class QGridLayout;
class MyCheckBox;
class QSlider;
class QLabel;


class AxesWidget : public QGroupBox
{
	Q_OBJECT
	
	public:
		AxesWidget(const QStringList &names, QWidget *parent = nullptr);
		AxesWidget(const AxesWidget &other) = delete;
		AxesWidget(AxesWidget &&other) = delete;
		AxesWidget& operator=(const AxesWidget &other) = delete;
		AxesWidget& operator=(AxesWidget &&other) = delete;
		virtual ~AxesWidget() = default;
		
		float value(int i) const;
		QVector<uint> axesToDisplay() const;
		
		
	public slots:
		void slotSetValue(int i, float value);
		
		
	signals:
		void axisDisplayChanged(uint axis, bool bDisplay);
		
		
	private:
		float m_value;
		
		QGridLayout *layout;
		QVector<MyCheckBox*> m_boxes;
		QVector<QSlider*> m_sliders;
		QVector<QLabel*> m_labels2;
};


#endif

