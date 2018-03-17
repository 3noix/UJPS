#include "GenericPropertiesInfo.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  IS EMPTY
//  ADD PROPERTY
//  REMOVE PROPERTY
//  CONTAINS
//  PROPERTY
//  PROPERTIES
//
//  READ DATA
//  WRITE DATA
//
//  STRING 2 QLISTBOOL
//  STRING 2 QLISTDOUBLE
//  STRING 2 QLISTINT
//  STRING 2 QSTRINGLIST
//
//  QVARIANT 2 QLISTBOOL
//  QVARIANT 2 QLISTDOUBLE
//  QVARIANT 2 QLISTINT
//  QVARIANT 2 QSTRINGLIST
//
//  QLISTBOOL 2 STRING
//  QLISTDOUBLE 2 STRING
//  QLISTINT 2 STRING
//  QSTRINGLIST 2 STRING
//
//  QLISTBOOL 2 QVARIANT
//  QLISTDOUBLE 2 QVARIANT
//  QLISTINT 2 QVARIANT
//  QSTRINGLIST 2 QVARIANT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
GenericPropertiesInfo::GenericPropertiesInfo() :
	AbstractXmlInfo{"genericProperties"}
{
}

GenericPropertiesInfo::GenericPropertiesInfo(const QString &fileName) :
	AbstractXmlInfo{"genericProperties"}
{
	this->readFile(fileName);
}





// IS EMPTY ///////////////////////////////////////////////////////////////////
bool GenericPropertiesInfo::isEmpty() const
{
	return (m_properties.size() == 0);
}

// ADD PROPERTY ///////////////////////////////////////////////////////////////
void GenericPropertiesInfo::addProperty(const QString &name, QVariant v)
{
	m_properties.insert(name,v);
}

// REMOVE PROPERTY ////////////////////////////////////////////////////////////
bool GenericPropertiesInfo::removeProperty(const QString &name)
{
	return (m_properties.remove(name) > 0);
}

// CONTAINS ///////////////////////////////////////////////////////////////////
bool GenericPropertiesInfo::contains(const QString &name)
{
	return m_properties.contains(name);
}

bool GenericPropertiesInfo::contains(const QStringList &names)
{
	for (const QString &name : names)
	{
		if (!m_properties.contains(name))
		{return false;}
	}
	
	return true;
}

// PROPERTY ///////////////////////////////////////////////////////////////////
QVariant GenericPropertiesInfo::property(const QString &name)
{
	if (!m_properties.contains(name)) {return QVariant();}
	return m_properties[name];
}

// PROPERTIES /////////////////////////////////////////////////////////////////
QMap<QString,QVariant> GenericPropertiesInfo::properties() const
{
	return m_properties;
}





// READ DATA ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GenericPropertiesInfo::readData(QIODevice &device)
{
	// lecture détaillée du contexte
	QXmlStreamReader reader;
	reader.setDevice(&device);
	
	while (!reader.atEnd())
	{
		// lecture et gestion des erreurs
		QXmlStreamReader::TokenType token = reader.readNext();
		if (reader.hasError())
		{
			this->setErrorMessage("Error at line " + QString::number(reader.lineNumber()) + " : " + reader.errorString());
			return false;
		}
		
		// DTD
		if (token == QXmlStreamReader::DTD)
		{
			if (reader.dtdName() != this->xsdFileName())
			{
				this->setErrorMessage("The xml file is not a " + this->xsdFileName() + " file !");
				return false;
			}
		}
		
		// START ELEMENT
		else if (token == QXmlStreamReader::StartElement)
		{
			QString eltTag = reader.name().toString();
			if (eltTag == "PROPERTY")
			{
				QString propertyName = reader.attributes().value("name").toString();
				QString propertyTypeStr = reader.attributes().value("type").toString();
				QString propertyValueStr = reader.attributes().value("value").toString();
				
				if (propertyTypeStr == "bool")
				{
					if (propertyValueStr == "true") {m_properties[propertyName] = true;}
					else {m_properties[propertyName] = false;}
				}
				else if (propertyTypeStr == "double")
				{
					m_properties[propertyName] = propertyValueStr.toDouble();
				}
				else if (propertyTypeStr == "int")
				{
					m_properties[propertyName] = propertyValueStr.toInt();
				}
				else if (propertyTypeStr == "QString")
				{
					m_properties[propertyName] = propertyValueStr;
				}
				else if (propertyTypeStr == "QList-bool-")
				{
					m_properties[propertyName] = GenericPropertiesInfo::string2qlistbool(propertyValueStr);
				}
				else if (propertyTypeStr == "QList-double-")
				{
					m_properties[propertyName] = GenericPropertiesInfo::string2qlistdouble(propertyValueStr);
				}
				else if (propertyTypeStr == "QList-int-")
				{
					m_properties[propertyName] = GenericPropertiesInfo::string2qlistint(propertyValueStr);
				}
				else if (propertyTypeStr == "QStringList")
				{
					m_properties[propertyName] = GenericPropertiesInfo::string2qstringlist(propertyValueStr);
				}
			}
		}
	}
	
	return true;
}

// WRITE DATA //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GenericPropertiesInfo::writeData(QIODevice &device)
{
	if (!this->isValid()) {return false;}
	
	// ouverture
	if (!device.open(QIODevice::WriteOnly)) {return false;}
	QXmlStreamWriter writer;
	writer.setAutoFormatting(true);
	writer.setAutoFormattingIndent(-1);
	writer.setDevice(&device);
	
	// début
	QString dtdStr;
	dtdStr += "<!DOCTYPE genericProperties SYSTEM ";
	dtdStr += QChar((int)0x22);
	dtdStr += "genericProperties.xsd";
	dtdStr += QChar((int)0x22);
	dtdStr += ">";
	
	writer.writeStartDocument("1.0", false);
	writer.writeDTD(dtdStr);
	writer.writeStartElement("PROPERTIES");
	
	// properties
	QStringList keys = m_properties.uniqueKeys();
	for (const QString &key : keys)
	{
		QVariant v = m_properties[key];
		QString typeStr;
		QString valueStr;
		if (v.type() == QVariant::Bool)
		{
			typeStr = "bool";
			valueStr = (v.toBool() ? "true" : "false");
		}
		else if (v.type() == QVariant::Double)
		{
			typeStr = "double";
			valueStr = QString::number(v.toDouble());
		}
		else if (v.type() == QVariant::Int)
		{
			typeStr = "int";
			valueStr = QString::number(v.toInt());
		}
		else if (v.type() == QVariant::String)
		{
			typeStr = "QString";
			valueStr = v.toString();
		}
		else if (v.type() == QVariant::List)
		{
			QList<QVariant> vlist = v.toList();
			if (vlist.size() == 0)
			{
				typeStr = "QStringList";
				valueStr = "";
			}
			else
			{
				QVariant v0 = vlist[0];
				if (v0.type() == QVariant::Bool)
				{
					typeStr = "QList-bool-";
					valueStr = GenericPropertiesInfo::qlistbool2string(vlist);
				}
				else if (v0.type() == QVariant::Double)
				{
					typeStr = "QList-double-";
					valueStr = GenericPropertiesInfo::qlistdouble2string(vlist);
				}
				else if (v0.type() == QVariant::Int)
				{
					typeStr = "QList-int-";
					valueStr = GenericPropertiesInfo::qlistint2string(vlist);
				}
				else if (v0.type() == QVariant::String)
				{
					typeStr = "QStringList";
					valueStr = GenericPropertiesInfo::qstringlist2string(vlist);
				}
			}
		}
		
		writer.writeStartElement("PROPERTY");
		writer.writeAttribute("name",key);
		writer.writeAttribute("type",typeStr);
		writer.writeAttribute("value",valueStr);
		writer.writeEndElement();
	}
	
	// fin
	writer.writeEndElement();
	writer.writeEndDocument();
	return true;
}






// STRING 2 QLISTBOOL //////////////////////////////////////////////////////////////////////////////////////////////////////////
QList<QVariant> GenericPropertiesInfo::string2qlistbool(const QString &str)
{
	QStringList sl = str.split('|',QString::KeepEmptyParts);
	QList<QVariant> list;
	for (const QString &s : sl)
	{
		if (s == "true") {list.append(QVariant(true));}
		else {list.append(QVariant(false));}
	}
	return list;
}

// STRING 2 QLISTDOUBLE ////////////////////////////////////////////////////////////////////////////////////////////////////////
QList<QVariant> GenericPropertiesInfo::string2qlistdouble(const QString &str)
{
	QStringList sl = str.split('|',QString::KeepEmptyParts);
	QList<QVariant> list;
	for (const QString &s : sl) {list.append(QVariant(s.toDouble()));}
	return list;
}

// STRING 2 QLISTINT ///////////////////////////////////////////////////////////////////////////////////////////////////////////
QList<QVariant> GenericPropertiesInfo::string2qlistint(const QString &str)
{
	QStringList sl = str.split('|',QString::KeepEmptyParts);
	QList<QVariant> list;
	for (const QString &s : sl) {list.append(QVariant(s.toInt()));}
	return list;
}

// STRING 2 QSTRINGLIST ////////////////////////////////////////////////////////////////////////////////////////////////////////
QList<QVariant> GenericPropertiesInfo::string2qstringlist(const QString &str)
{
	QStringList sl = str.split('|',QString::KeepEmptyParts);
	QList<QVariant> list;
	for (const QString &s : sl) {list.append(QVariant(s));}
	return list;
}





// QVARIANT 2 QLISTBOOL ////////////////////////////////////////////////////////////////////////////////////////////////////////
QList<bool> GenericPropertiesInfo::qvariant2qlistbool(const QVariant &v)
{
	QList<bool> list;
	QList<QVariant> vlist = v.toList();
	if (vlist.size() == 0) {return list;}
	
	for (const QVariant &w : vlist) {list.append(w.toBool());}
	return list;
}

// QVARIANT 2 QLISTDOUBLE //////////////////////////////////////////////////////////////////////////////////////////////////////
QList<double> GenericPropertiesInfo::qvariant2qlistdouble(const QVariant &v)
{
	QList<double> list;
	QList<QVariant> vlist = v.toList();
	if (vlist.size() == 0) {return list;}
	
	for (const QVariant &w : vlist) {list.append(w.toDouble());}
	return list;
}

// QVARIANT 2 QLISTINT /////////////////////////////////////////////////////////////////////////////////////////////////////////
QList<int> GenericPropertiesInfo::qvariant2qlistint(const QVariant &v)
{
	QList<int> list;
	QList<QVariant> vlist = v.toList();
	if (vlist.size() == 0) {return list;}
	
	for (const QVariant &w : vlist) {list.append(w.toInt());}
	return list;
}

// QVARIANT 2 QSTRINGLIST //////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList GenericPropertiesInfo::qvariant2qstringlist(const QVariant &v)
{
	QStringList list;
	QList<QVariant> vlist = v.toList();
	if (vlist.size() == 0) {return list;}
	
	for (const QVariant &w : vlist) {list.append(w.toString());}
	return list;
}








// QLISTBOOL 2 STRING //////////////////////////////////////////////////////////////////////////////////////////////////////////
QString GenericPropertiesInfo::qlistbool2string(const QList<QVariant> &list)
{
	QString str;
	for (const QVariant &v : list)
	{
		QString temp = "false";
		if (v.toBool()) {temp = "true";}
		str += temp + "|";
	}
	
	str.resize(str.size()-1);
	return str;
}

// QLISTDOUBLE 2 STRING ////////////////////////////////////////////////////////////////////////////////////////////////////////
QString GenericPropertiesInfo::qlistdouble2string(const QList<QVariant> &list)
{
	QString str;
	for (const QVariant &v : list) {str += QString::number(v.toDouble()) + "|";}
	str.resize(str.size()-1);
	return str;
}

// QLISTINT 2 STRING ///////////////////////////////////////////////////////////////////////////////////////////////////////////
QString GenericPropertiesInfo::qlistint2string(const QList<QVariant> &list)
{
	QString str;
	for (const QVariant &v : list) {str += QString::number(v.toInt()) + "|";}
	str.resize(str.size()-1);
	return str;
}

// QSTRINGLIST 2 STRING ////////////////////////////////////////////////////////////////////////////////////////////////////////
QString GenericPropertiesInfo::qstringlist2string(const QList<QVariant> &list)
{
	QString str;
	for (const QVariant &v : list) {str += v.toString() + "|";}
	str.resize(str.size()-1);
	return str;
}






// QLISTBOOL 2 QVARIANT ////////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant GenericPropertiesInfo::qlistbool2qvariant(const QList<bool> &list)
{
	QList<QVariant> vlist;
	for (bool b : list) {vlist.append(QVariant(b));}
	return QVariant(vlist);
}

// QLISTDOUBLE 2 QVARIANT //////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant GenericPropertiesInfo::qlistdouble2qvariant(const QList<double> &list)
{
	QList<QVariant> vlist;
	for (double d : list) {vlist.append(QVariant(d));}
	return QVariant(vlist);
}

// QLISTINT 2 QVARIANT /////////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant GenericPropertiesInfo::qlistint2qvariant(const QList<int> &list)
{
	QList<QVariant> vlist;
	for (int i : list) {vlist.append(QVariant(i));}
	return QVariant(vlist);
}

// QSTRINGLIST 2 QVARIANT //////////////////////////////////////////////////////////////////////////////////////////////////////
QVariant GenericPropertiesInfo::qstringlist2qvariant(const QStringList &list)
{
	QList<QVariant> vlist;
	for (const QString &s : list) {vlist.append(QVariant(s));}
	return QVariant(vlist);
}






