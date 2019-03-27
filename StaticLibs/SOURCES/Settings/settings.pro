CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = settings
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += widgets xmlpatterns


INCLUDEPATH +=  ../../INCLUDES/Settings/


HEADERS +=  ../../INCLUDES/Settings/ApplicationSettings.h \
			../../INCLUDES/Settings/AbstractSettingsWidget.h \
			../../INCLUDES/Settings/SettingsDialog.h \
			../../INCLUDES/Settings/MyFileDialog.h \
			../../INCLUDES/Settings/XML/AbstractXmlInfo.h \
			../../INCLUDES/Settings/XML/XmlValidationMessageHandler.h \
			../../INCLUDES/Settings/XML/GenericPropertiesInfo.h


SOURCES +=  CODE/otherFunctions.cpp \
			CODE/ApplicationSettings.cpp \
			CODE/SettingsDialog.cpp \
			CODE/MyFileDialog.cpp \
			CODE/XML/AbstractXmlInfo.cpp \
			CODE/XML/XmlValidationMessageHandler.cpp \
			CODE/XML/GenericPropertiesInfo.cpp


RESOURCES += resources.qrc

