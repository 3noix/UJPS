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


win32-g++:LIBS += ../StaticLibs/SOURCES/Settings/$$MODE/libsettings.a
win32-g++:LIBS += ../StaticLibs/SOURCES/VigemWrapper/$$MODE/libvigemWrapper.a
win32-g++:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a

win32-msvc*:LIBS += ../StaticLibs/SOURCES/Settings/$$MODE/settings.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/VigemWrapper/$$MODE/vigemWrapper.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib

		
INCLUDEPATH +=  ../StaticLibs/INCLUDES/Settings/ \
				../StaticLibs/INCLUDES/VigemWrapper/ \
				../StaticLibs/INCLUDES/QtGameControllerModif/


HEADERS +=  CODE/MainWindow.h


SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

