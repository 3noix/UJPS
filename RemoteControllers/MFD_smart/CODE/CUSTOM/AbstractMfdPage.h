#ifndef ABSTRACT_MFD_PAGE
#define ABSTRACT_MFD_PAGE


#include <QObject>
#include <QGraphicsItemGroup>


class AbstractMfdPage : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
	
	public:
		explicit AbstractMfdPage(QObject *parent) : QObject{parent}, QGraphicsItemGroup{} {};
		AbstractMfdPage(const AbstractMfdPage &other) = delete;
		AbstractMfdPage(AbstractMfdPage &&other) = delete;
		AbstractMfdPage& operator=(const AbstractMfdPage &other) = delete;
		AbstractMfdPage& operator=(AbstractMfdPage &&other) = delete;
		virtual ~AbstractMfdPage() = default;
		
		virtual void process(uint button, bool bPress) = 0;
		
		
	signals:
		void buttonChanged2(uint button, bool bPressed);
};


#endif

