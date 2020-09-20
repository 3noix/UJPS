CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = settings
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets xmlpatterns


INCLUDEPATH +=  ../../INCLUDES/Settings/


HEADERS +=  ../../INCLUDES/Settings/ApplicationSettings.h \
			../../INCLUDES/Settings/AbstractSettingsWidget.h \
			../../INCLUDES/Settings/SettingsDialog.h \
			../../INCLUDES/Settings/MyFileDialog.h \
			../../INCLUDES/Settings/XML/GenericPropertiesInfo.h \
			CODE/XML/AbstractXmlInfo.h \
			CODE/XML/XmlValidationMessageHandler.h


SOURCES +=  CODE/otherFunctions.cpp \
			CODE/ApplicationSettings.cpp \
			CODE/SettingsDialog.cpp \
			CODE/MyFileDialog.cpp \
			CODE/XML/GenericPropertiesInfo.cpp \
			CODE/XML/AbstractXmlInfo.cpp \
			CODE/XML/XmlValidationMessageHandler.cpp


RESOURCES += resources.qrc

