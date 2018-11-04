#ifndef MFD_BEZEL_CORNER2
#define MFD_BEZEL_CORNER2


#include <QGraphicsObject>
class MfdRectangularButton;


class MfdBezelCorner2 : public QGraphicsObject
{
	Q_OBJECT
	
	public:
		explicit MfdBezelCorner2(uint buttonUp, const QString &buttonText, bool bFlip, QGraphicsItem *parent = nullptr);
		MfdBezelCorner2(const MfdBezelCorner2 &other) = delete;
		MfdBezelCorner2(MfdBezelCorner2 &&other) = delete;
		MfdBezelCorner2& operator=(const MfdBezelCorner2 &other) = delete;
		MfdBezelCorner2& operator=(MfdBezelCorner2 &&other) = delete;
		virtual ~MfdBezelCorner2() = default;
		
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		virtual QRectF boundingRect() const;
		
		
	signals:
		void buttonChanged(uint button, bool bPressed);
		
		
	private:
		QPointF m_topLeft, m_rightBottom;
		QPainterPath m_path1, m_path2;
		QPolygonF m_screwPrint;
		
		MfdRectangularButton *m_button;
};


#endif

