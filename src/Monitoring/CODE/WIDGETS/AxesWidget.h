#ifndef AXES_WIDGET
#define AXES_WIDGET


#include <QGroupBox>
#include <vector>
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
		std::vector<uint> axesToDisplay() const;
		
		
	public slots:
		void slotSetValue(int i, float value);
		
		
	signals:
		void axisDisplayChanged(uint axis, bool bDisplay);
		
		
	private:
		float m_value;
		
		QGridLayout *layout;
		std::vector<MyCheckBox*> m_boxes;
		std::vector<QSlider*> m_sliders;
		std::vector<QLabel*> m_labels2;
};


#endif

