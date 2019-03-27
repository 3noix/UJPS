#ifndef ABSTRACT_XML_INFO
#define ABSTRACT_XML_INFO


#include <QString>
#include <QIODevice>


class AbstractXmlInfo
{
	public:
		explicit AbstractXmlInfo(const QString &xsdFileName);
		virtual ~AbstractXmlInfo() = default;
		
		bool readFile(const QString &fileName);
		bool writeFile(const QString &fileName);
		
		bool fromString(const QString &str);
		bool toString(QString &str);
		
		virtual bool isValid() const;
		bool fileError() const;
		QString errorMessage() const;
		QString fileName() const;
		
		
	protected:
		virtual bool readData(QIODevice &device) = 0;
		virtual bool writeData(QIODevice &device) = 0;
		
		bool readDataMain(QIODevice &device);
		bool checkData(QIODevice &device);
		void setErrorMessage(QString message);
		QString xsdFileName() const;
		
		
	private:
		bool m_error;
		QString m_errorMessage;
		QString m_fileName;
		QString m_xsdFileName;
};


#endif

