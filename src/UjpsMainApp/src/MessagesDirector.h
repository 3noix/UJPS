#ifndef MESSAGES_DIRECTOR
#define MESSAGES_DIRECTOR


#include <QObject>
#include <QString>
#include <QColor>
#include <QVector>


class MessagesDirector : public QObject
{
	Q_OBJECT
	
	public:
		MessagesDirector(QObject *parent = 0);
		MessagesDirector(const MessagesDirector &other) = delete;
		MessagesDirector(MessagesDirector &&other) = delete;
		MessagesDirector& operator=(const MessagesDirector &other) = delete;
		MessagesDirector& operator=(MessagesDirector &&other) = delete;
		virtual ~MessagesDirector() = default;
		
		void startsListeningTo(QObject *o);
		void stopsListeningTo(QObject *o);
		
		
	private slots:
		void slotMessage(const QString &str, QColor color);
		
		
	private:
		QVector<QObject*> m_objectsListened;
};


#endif

