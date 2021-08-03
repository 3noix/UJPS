CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = ControllersInfo
CONFIG += c++17
DESTDIR = ../../bin
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets network


win32-g++:LIBS += ../StaticLibs/Settings/$$MODE/libsettings.a
win32-g++:LIBS += ../StaticLibs/VigemWrapper/$$MODE/libvigemWrapper.a
win32-g++:LIBS += ../StaticLibs/QtGameControllerModif/$$MODE/libQtGameControllerModif.a

win32-msvc*:LIBS += ../StaticLibs/Settings/$$MODE/settings.lib
win32-msvc*:LIBS += ../StaticLibs/VigemWrapper/$$MODE/vigemWrapper.lib
win32-msvc*:LIBS += ../StaticLibs/QtGameControllerModif/$$MODE/QtGameControllerModif.lib

		
INCLUDEPATH +=  ../../include


HEADERS +=  src/MainWindow.h


SOURCES +=  src/main.cpp \
			src/MainWindow.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

