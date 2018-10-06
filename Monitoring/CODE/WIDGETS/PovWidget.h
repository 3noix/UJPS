#ifndef POV_WIDGET
#define POV_WIDGET


#include <QWidget>


class PovWidget : public QWidget
{
	Q_OBJECT
	
	public:
		PovWidget(QWidget *parent = nullptr);
		PovWidget(const PovWidget &other) = delete;
		PovWidget(PovWidget &&other) = delete;
		PovWidget& operator=(const PovWidget &other) = delete;
		PovWidget& operator=(PovWidget &&other) = delete;
		virtual ~PovWidget() = default;
		
		float angle() const;
		
		
	public slots:
		void slotSetAngle(float angle);
		
		
	protected:
		virtual void paintEvent(QPaintEvent *e);
		
		
	private:
		float m_angle;
};


#endif

