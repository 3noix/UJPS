CONFIG(debug, debug|release) {
	DESTDIR = debug
}
CONFIG(release, debug|release) {
	DESTDIR = release
}


TEMPLATE = lib
TARGET = QtGameControllerModif
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT = core

DEFINES += QGAMECONTROLLER_LIBRARY

win32-g++:LIBS += -ldinput8 -ldxguid

INCLUDEPATH +=  ../../INCLUDES/QtGameControllerModif

SOURCES +=  CODE/QGameController.cpp \
			CODE/QGameController_win.cpp

PUBLIC_HEADERS += ../../INCLUDES/QtGameControllerModif/QGameController.h
PRIVATE_HEADERS +=  CODE/QGameController_p.h
HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS


