#ifndef MFD_SELECTABLE_TEXT_ITEM
#define MFD_SELECTABLE_TEXT_ITEM


#include <QGraphicsItemGroup>
#include <QFont>
#include <QBrush>
#include <QPen>
class QGraphicsSimpleTextItem;
class QGraphicsRectItem;


class MfdSelectableTextItem : public QGraphicsItemGroup
{
	public:
		explicit MfdSelectableTextItem(const QString &text, qreal fontSize, Qt::Alignment a, QGraphicsItem *parent = nullptr);
		MfdSelectableTextItem(const MfdSelectableTextItem &other) = delete;
		MfdSelectableTextItem(MfdSelectableTextItem &&other) = delete;
		MfdSelectableTextItem& operator=(const MfdSelectableTextItem &other) = delete;
		MfdSelectableTextItem& operator=(MfdSelectableTextItem &&other) = delete;
		virtual ~MfdSelectableTextItem() = default;
		
		QString text() const;
		
		void select();
		void unselect();
		void switchSelection();
		
		
	private:
		QGraphicsSimpleTextItem *m_textItem;
		QGraphicsRectItem *m_rectItem;
		
		QPointF m_posOffset;
		bool m_bSelected;
		QFont m_font;
		QRectF m_rect;
};


#endif

