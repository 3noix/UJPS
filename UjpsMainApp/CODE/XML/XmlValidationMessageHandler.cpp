#include "XmlValidationMessageHandler.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  MESSAGE CONTENT
//  LINE
//  COLUMN
//  HANDLE MESSAGE
//  REMOVE HTML TAGS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
XmlValidationMessageHandler::XmlValidationMessageHandler() :
	QAbstractMessageHandler{},
	m_messageContent{},
	m_sourceLocation{}
{
}






// MESSAGE CONTENT ////////////////////////////////////////////////////////////
QString XmlValidationMessageHandler::messageContent() const
{
	return m_messageContent;
}

// LINE ///////////////////////////////////////////////////////////////////////
int XmlValidationMessageHandler::line() const
{
	return m_sourceLocation.line();
}

// COLUMN /////////////////////////////////////////////////////////////////////
int XmlValidationMessageHandler::column() const
{
	return m_sourceLocation.column();
}

// HANDLE MESSAGE /////////////////////////////////////////////////////////////
void XmlValidationMessageHandler::handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation)
{
	Q_UNUSED(type)
	Q_UNUSED(identifier)
	
	m_messageContent = XmlValidationMessageHandler::removeHtmlTags(description);
	m_sourceLocation = sourceLocation;
}

// REMOVE HTML TAGS ///////////////////////////////////////////////////////////
QString XmlValidationMessageHandler::removeHtmlTags(const QString &str)
{
	QString str2 = str;
	int nbCaracs = str2.size();
	//bool bCloseTag = false;
	int posLastCloseTag = -1;
	
	for (int i=nbCaracs-1; i>=0; --i)
	{
		if (str2[i] == '>')
		{
			//bCloseTag = true;
			posLastCloseTag = i;
		}
		else if (str2[i] == '<')
		{
			str2.remove(i,posLastCloseTag-i+1);
			//bCloseTag = false;
		}
	}
	
	return str2;
}






