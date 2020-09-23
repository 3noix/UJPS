#ifndef APPLICATION_SETTINGS
#define APPLICATION_SETTINGS


#include "XML/GenericPropertiesInfo.h"


class ApplicationSettings
{
	public:
		static ApplicationSettings& instance();
		
		bool readFile();
		bool writeFile();
		
		bool isEmpty() const;
		QVariant property(const QString &name);
		bool setProperty(const QString &name, const QVariant &value);
		bool removeProperty(const QString &name);
		bool contains(const QString &name);
		
		
	private:
		ApplicationSettings() = default;
		ApplicationSettings(const ApplicationSettings &s) = default;
		ApplicationSettings(ApplicationSettings &&s) = default;
		ApplicationSettings& operator=(const ApplicationSettings& s) = delete;
		ApplicationSettings& operator=(ApplicationSettings &&s) = delete;
		~ApplicationSettings() = default;
		
		static ApplicationSettings m_instance;
		GenericPropertiesInfo m_settings;
};


#endif

