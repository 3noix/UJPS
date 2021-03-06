CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = vigemWrapper
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets network


win32-g++:LIBS += ../Settings/$$MODE/libsettings.a

win32-msvc*:LIBS += ../Settings/$$MODE/settings.lib


INCLUDEPATH +=  ../../INCLUDES/Settings/ \
				../../INCLUDES/VigemWrapper/


HEADERS +=  ../../INCLUDES/VigemWrapper/VigemPidWhiteLister.h \
			../../INCLUDES/VigemWrapper/VigemSettingsWidget.h


SOURCES +=  CODE/VigemPidWhiteLister.cpp \
			CODE/VigemSettingsWidget.cpp

