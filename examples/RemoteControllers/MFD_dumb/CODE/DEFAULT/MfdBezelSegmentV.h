#ifndef MFD_BEZEL_SEGMENT_V
#define MFD_BEZEL_SEGMENT_V


#include <QGraphicsObject>
#include <array>
class MfdSquareButton;


class MfdBezelSegmentV : public QGraphicsObject
{
	Q_OBJECT
	
	public:
		explicit MfdBezelSegmentV(std::array<uint,5> buttons, QGraphicsItem *parent = nullptr);
		MfdBezelSegmentV(const MfdBezelSegmentV &other) = delete;
		MfdBezelSegmentV(MfdBezelSegmentV &&other) = delete;
		MfdBezelSegmentV& operator=(const MfdBezelSegmentV &other) = delete;
		MfdBezelSegmentV& operator=(MfdBezelSegmentV &&other) = delete;
		virtual ~MfdBezelSegmentV() = default;
		
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		virtual QRectF boundingRect() const;
		
		
	signals:
		void buttonChanged(uint button, bool bPressed);
		
		
	private:
		QPointF m_topLeft, m_rightBottom;
		QPolygonF m_left1, m_right1;
		QPolygonF m_left2, m_right2;
		QPolygonF m_left3, m_right3;
		QPolygonF m_left4, m_right4;
		QPolygonF m_left5, m_right5;
		QRectF m_rect1, m_rect2, m_rect3, m_rect4, m_rect5;
		QRectF m_int12, m_int23, m_int34, m_int45;
		QRectF m_inside;
		
		MfdSquareButton *m_button1;
		MfdSquareButton *m_button2;
		MfdSquareButton *m_button3;
		MfdSquareButton *m_button4;
		MfdSquareButton *m_button5;
};


#endif

