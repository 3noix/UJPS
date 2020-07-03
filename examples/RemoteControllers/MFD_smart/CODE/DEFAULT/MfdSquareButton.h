#ifndef MFD_SQUARE_BUTTON
#define MFD_SQUARE_BUTTON


#include <QGraphicsObject>


class MfdSquareButton : public QGraphicsObject
{
	Q_OBJECT
	
	public:
		explicit MfdSquareButton(uint button, QGraphicsItem *parent = nullptr);
		MfdSquareButton(const MfdSquareButton &other) = delete;
		MfdSquareButton(MfdSquareButton &&other) = delete;
		MfdSquareButton& operator=(const MfdSquareButton &other) = delete;
		MfdSquareButton& operator=(MfdSquareButton &&other) = delete;
		virtual ~MfdSquareButton() = default;
		
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		virtual QRectF boundingRect() const;
		
		
	protected:
		virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
		virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
		
		
	signals:
		void buttonChanged(uint button, bool bPressed);
		
		
	private:
		uint m_button;
		
		QRectF m_rect;
		qreal m_size, m_b, m_c;
		qreal m_r0, m_rb, m_rc;
		QPainterPath m_path1, m_path2, m_path3;
};


#endif

