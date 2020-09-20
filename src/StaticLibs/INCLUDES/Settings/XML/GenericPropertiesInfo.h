#ifndef GENERIC_PROPERTIES_INFO
#define GENERIC_PROPERTIES_INFO


#include <map>
#include <QVariant>
#include <QStringList>
#include "../../../SOURCES/Settings/CODE/XML/AbstractXmlInfo.h"


class GenericPropertiesInfo : public AbstractXmlInfo
{
	public:
		explicit GenericPropertiesInfo();
		explicit GenericPropertiesInfo(const QString &fileName);
		virtual ~GenericPropertiesInfo() = default;
		
		bool isEmpty() const;
		void addProperty(const QString &name, QVariant v);
		bool removeProperty(const QString &name);
		bool contains(const QString &name);
		bool contains(const QStringList &names);
		QVariant property(const QString &name);
		std::map<QString,QVariant> properties() const;
		
		
	protected:
		virtual bool readData(QIODevice &device) override;
		virtual bool writeData(QIODevice &device) override;
		
		
	private:
		std::map<QString,QVariant> m_properties;
		
		static QList<QVariant> string2qlistbool(const QString &str);
		static QList<QVariant> string2qlistdouble(const QString &str);
		static QList<QVariant> string2qlistint(const QString &str);
		static QList<QVariant> string2qstringlist(const QString &str);
		
		static QString qlistbool2string(const QList<QVariant> &list);
		static QString qlistdouble2string(const QList<QVariant> &list);
		static QString qlistint2string(const QList<QVariant> &list);
		static QString qstringlist2string(const QList<QVariant> &list);
		
		
	public:
		static QList<bool> qvariant2qlistbool(const QVariant &v);
		static QList<double> qvariant2qlistdouble(const QVariant &v);
		static QList<int> qvariant2qlistint(const QVariant &v);
		static QStringList qvariant2qstringlist(const QVariant &v);
		
		static QVariant qlistbool2qvariant(const QList<bool> &list);
		static QVariant qlistdouble2qvariant(const QList<double> &list);
		static QVariant qlistint2qvariant(const QList<int> &list);
		static QVariant qstringlist2qvariant(const QStringList &list);
};


#endif

