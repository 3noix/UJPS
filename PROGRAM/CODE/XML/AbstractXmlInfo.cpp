#include "AbstractXmlInfo.h"
#include "XmlValidationMessageHandler.h"

#include <QXmlSchemaValidator>
#include <QXmlSchema>
#include <QBuffer>
#include <QFile>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  READ DATA MAIN
//  READ FILE
//  WRITE FILE
//  FROM STRING
//  TO STRING
//
//  IS VALID
//  FILE ERROR
//  ERROR MESSAGE
//  SET ERROR MESSAGE
//  XSD FILE NAME
//  FILE NAME
//
//  CHECK DATA
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AbstractXmlInfo::AbstractXmlInfo(const QString &xsdFileName) :
	m_error{false},
	m_errorMessage{},
	m_fileName{},
	m_xsdFileName{xsdFileName}
{
}






// READ DATA MAIN /////////////////////////////////////////////////////////////
bool AbstractXmlInfo::readDataMain(QIODevice &device)
{
	if (!this->checkData(device)) {return false;}
	return this->readData(device);
}

// READ FILE //////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::readFile(const QString &fileName)
{
	m_fileName = fileName;
	QFile file(fileName);
	m_error = !this->readDataMain(file);
	return !m_error;
}

// WRITE FILE /////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::writeFile(const QString &fileName)
{
	m_fileName = fileName;
	QFile file(fileName);
	m_error = !this->writeData(file);
	return !m_error;
}

// FROM STRING ////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::fromString(const QString &str)
{
	m_fileName = "";
	QByteArray ar = str.toUtf8();
	QBuffer buf(&ar);
	m_error = !this->readDataMain(buf);
	return !m_error;
}

// TO STRING //////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::toString(QString &str)
{
	m_fileName = "";
	QByteArray ar;
	QBuffer buf(&ar);
	m_error = !this->writeData(buf);
	str = QString::fromUtf8(ar);
	return !m_error;
}







// IS VALID ///////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::isValid() const
{
	return true;
}

// FILE ERROR /////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::fileError() const
{
	return m_error;
}

// ERROR MESSAGE //////////////////////////////////////////////////////////////
QString AbstractXmlInfo::errorMessage() const
{
	return m_errorMessage;
}

// SET ERROR MESSAGE //////////////////////////////////////////////////////////
void AbstractXmlInfo::setErrorMessage(QString message)
{
	m_errorMessage = message;
}

// XSD FILE NAME //////////////////////////////////////////////////////////////
QString AbstractXmlInfo::xsdFileName() const
{
	return m_xsdFileName;
}

// FILE NAME //////////////////////////////////////////////////////////////////
QString AbstractXmlInfo::fileName() const
{
	return m_fileName;
}





// CHECK DATA /////////////////////////////////////////////////////////////////
bool AbstractXmlInfo::checkData(QIODevice &device)
{
	Q_INIT_RESOURCE(resources);
	
	// ouvrir le schéma
	QFile fileSchema(":/RESOURCES/XSD/" + m_xsdFileName + ".xsd");
	if (!fileSchema.open(QIODevice::ReadOnly))
	{
		m_errorMessage = "The xml schema " + m_xsdFileName + ".xsd cannot be opened !";
		return false;
	}
	
	// création des objets nécessaires à la validation
	XmlValidationMessageHandler messageHandler;
	QXmlSchema schema;
	schema.setMessageHandler(&messageHandler);
	schema.load(fileSchema.readAll());
	fileSchema.close();
	
	// vérifier que le schéma est valide
	if (!schema.isValid())
	{
		m_errorMessage = "The xml schema " + m_xsdFileName + ".xsd is not valid : ";
		m_errorMessage += "line " + QString::number(messageHandler.line()) + " : " + messageHandler.messageContent();
		return false;
	}
	
	// ouvrir le fichier
	if (!device.open(QIODevice::ReadOnly))
	{
		m_errorMessage = "The file cannot be opened";
		return false;
	}
	
	// vérifier que le fichier est conforme au schéma
	QXmlSchemaValidator validator(schema);
	if (!validator.validate(device.readAll()))
	{
		m_errorMessage = "The file is not coherent with " + m_xsdFileName + ".xsd : ";
		m_errorMessage += "line " + QString::number(messageHandler.line()) + " : ";
		m_errorMessage += messageHandler.messageContent();
		return false;
	}
	
	device.seek(0);
	return true;
}



