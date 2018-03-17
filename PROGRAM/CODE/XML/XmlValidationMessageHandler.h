#ifndef XML_VALIDATION_MESSAGE_HANDLER
#define XML_VALIDATION_MESSAGE_HANDLER


#include <QAbstractMessageHandler>


class XmlValidationMessageHandler : public QAbstractMessageHandler
{
	public:
		explicit XmlValidationMessageHandler();
		virtual ~XmlValidationMessageHandler() = default;
		
		QString messageContent() const;
		int line() const;
		int column() const;
		
		static QString removeHtmlTags(const QString &str);
		
		
	protected:
		virtual void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation) override;
		
		
	private:
		QString m_messageContent;
		QSourceLocation m_sourceLocation;
};


#endif





