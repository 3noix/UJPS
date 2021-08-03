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


HEADERS +=  src/VigemPidWhiteLister.h \
			src/VigemSettingsWidget.h


SOURCES +=  src/VigemPidWhiteLister.cpp \
			src/VigemSettingsWidget.cpp

