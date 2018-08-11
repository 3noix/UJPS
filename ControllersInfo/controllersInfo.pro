win32-g++:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
}
win32-g++:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
}

win32-msvc*:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/QtGameControllerModif.lib
}
win32-msvc*:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/QtGameControllerModif.lib
}


TEMPLATE = app
TARGET = ControllersInfo
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT += core gui widgets

		
INCLUDEPATH +=  ../StaticLibs/INCLUDES/QtGameControllerModif/

HEADERS +=  CODE/MainWindow.h

SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp

RESOURCES += resources.qrc
RC_FILE += icone.rc
