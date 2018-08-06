#ifndef AXES_WIDGET
#define AXES_WIDGET


#include <QGroupBox>
class QGridLayout;
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
		
		
	public slots:
		void slotSetValue(int i, float value);
		
		
	private:
		float m_value;
		
		QGridLayout *layout;
		QVector<QSlider*> m_sliders;
		QVector<QLabel*> m_labels2;
};


#endif

