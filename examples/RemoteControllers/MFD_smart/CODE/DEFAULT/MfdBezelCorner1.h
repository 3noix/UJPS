#ifndef MFD_BEZEL_CORNER1
#define MFD_BEZEL_CORNER1


#include <QGraphicsObject>
class MfdRectangularButton;


class MfdBezelCorner1 : public QGraphicsObject
{
	Q_OBJECT
	
	public:
		explicit MfdBezelCorner1(uint buttonUp, const QString &buttonText, bool bFlip, QGraphicsItem *parent = nullptr);
		MfdBezelCorner1(const MfdBezelCorner1 &other) = delete;
		MfdBezelCorner1(MfdBezelCorner1 &&other) = delete;
		MfdBezelCorner1& operator=(const MfdBezelCorner1 &other) = delete;
		MfdBezelCorner1& operator=(MfdBezelCorner1 &&other) = delete;
		virtual ~MfdBezelCorner1() = default;
		
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		virtual QRectF boundingRect() const;
		
		void setLed(bool b);
		bool led() const;
		
		
	signals:
		void buttonChanged(uint button, bool bPressed);
		
		
	private:
		QPointF m_topLeft, m_rightBottom;
		QPainterPath m_path1, m_path2;
		QPolygonF m_screwPrint;
		bool m_bLedOn;
		
		MfdRectangularButton *m_button;
};


#endif

