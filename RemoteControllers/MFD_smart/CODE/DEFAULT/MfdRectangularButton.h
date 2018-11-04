#ifndef MFD_RECTANGULAR_BUTTON
#define MFD_RECTANGULAR_BUTTON


#include <QGraphicsObject>


class MfdRectangularButton : public QGraphicsObject
{
	Q_OBJECT
	
	public:
		explicit MfdRectangularButton(uint button, const QString &text, bool bFlip, QGraphicsItem *parent = nullptr);
		MfdRectangularButton(const MfdRectangularButton &other) = delete;
		MfdRectangularButton(MfdRectangularButton &&other) = delete;
		MfdRectangularButton& operator=(const MfdRectangularButton &other) = delete;
		MfdRectangularButton& operator=(MfdRectangularButton &&other) = delete;
		virtual ~MfdRectangularButton() = default;
		
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		virtual QRectF boundingRect() const;
		
		
	protected:
		virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
		virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
		
		
	signals:
		void buttonChanged(uint button, bool bPressed);
		
		
	private:
		uint m_button;
		uint m_currentButton;
		QString m_text;
		bool m_bFlip;
		
		QRectF m_rect, m_textRect;
		qreal m_dx, m_dy;
		qreal m_hArrow, m_arrowOffset, m_r0;
		
		QPainterPath m_path1;
		QPolygonF m_triangle, m_arrow;
		QRectF m_bar;
};


#endif

