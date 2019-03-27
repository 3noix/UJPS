CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = vigemWrapper
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += widgets xmlpatterns


win32-g++:LIBS += ../Settings/$$MODE/libsettings.a

win32-msvc*:LIBS += ../Settings/$$MODE/settings.lib


INCLUDEPATH +=  ../../INCLUDES/Settings/ \
				../../INCLUDES/VigemWrapper/


HEADERS +=  ../../INCLUDES/VigemWrapper/VigemPidWhiteLister.h \
			../../INCLUDES/VigemWrapper/VigemPidWhiteListerConsole.h \
			../../INCLUDES/VigemWrapper/VigemSettingsWidget.h


SOURCES +=  CODE/VigemPidWhiteLister.cpp \
			CODE/VigemPidWhiteListerConsole.cpp \
			CODE/VigemSettingsWidget.cpp

