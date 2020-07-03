#ifndef MFD_TEXT_ITEM
#define MFD_TEXT_ITEM


#include <QGraphicsItemGroup>
#include <QFont>
#include <QBrush>
#include <QPen>
class QGraphicsSimpleTextItem;
class QGraphicsRectItem;


class MfdTextItem : public QGraphicsItemGroup
{
	public:
		explicit MfdTextItem(const QString &text, qreal fontSize = 2.0, Qt::Alignment a = Qt::AlignCenter, QGraphicsItem *parent = nullptr);
		MfdTextItem(const MfdTextItem &other) = delete;
		MfdTextItem(MfdTextItem &&other) = delete;
		MfdTextItem& operator=(const MfdTextItem &other) = delete;
		MfdTextItem& operator=(MfdTextItem &&other) = delete;
		virtual ~MfdTextItem() = default;
		
		QString text() const;
		void setActivated(bool b);
		bool isActivated() const;
		
		
	private:
		QGraphicsSimpleTextItem *m_textItem;
		QGraphicsRectItem *m_rectItem;
		
		QPointF m_posOffset;
		QFont m_font;
		QPen m_penActivated;
		QRectF m_rectActivated;
};


#endif

