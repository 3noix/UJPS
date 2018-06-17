#include "MessagesDirector.h"
#include <iostream>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  STARTS LISTENING TO
//  STOPS LISTENING TO
//  SLOT MESSAGE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
MessagesDirector::MessagesDirector(QObject *parent) : QObject(parent) {}


// STARTS LISTENING TO ////////////////////////////////////////////////////////
void MessagesDirector::startsListeningTo(QObject *o)
{
	if (!m_objectsListened.contains(o))
	{
		m_objectsListened << o;
		QObject::connect(o,SIGNAL(message(QString,QColor)),this,SLOT(slotMessage(QString,QColor)));
	}
}

// STOPS LISTENING TO /////////////////////////////////////////////////////////
void MessagesDirector::stopsListeningTo(QObject *o)
{
	if (m_objectsListened.contains(o))
	{
		m_objectsListened.removeAll(o);
		QObject::disconnect(o,SIGNAL(message(QString,QColor)),this,SLOT(slotMessage(QString,QColor)));
	}
}

// SLOT MESSAGE ///////////////////////////////////////////////////////////////
void MessagesDirector::slotMessage(const QString &str, QColor color)
{
	if (color != Qt::red)
		std::cout << qPrintable(str) << std::endl;
	else
		std::cerr << qPrintable(str) << std::endl;
}

