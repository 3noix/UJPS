#ifndef MFD_SCREEN
#define MFD_SCREEN


#include <QGraphicsObject>


class MfdScreen : public QGraphicsObject
{
	Q_OBJECT
	
	public:
		explicit MfdScreen(QGraphicsItem *parent = nullptr);
		MfdScreen(const MfdScreen &other) = delete;
		MfdScreen(MfdScreen &&other) = delete;
		MfdScreen& operator=(const MfdScreen &other) = delete;
		MfdScreen& operator=(MfdScreen &&other) = delete;
		virtual ~MfdScreen() = default;
		
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		virtual QRectF boundingRect() const;
		
		
	private:
		QPainterPath m_path;
		QPointF m_topLeft, m_rightBottom;
		QRectF m_rect;
};


#endif

