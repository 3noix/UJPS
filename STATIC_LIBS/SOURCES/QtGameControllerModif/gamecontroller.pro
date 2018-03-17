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
QT = core

DEFINES += QGAMECONTROLLER_LIBRARY

win32-g++:LIBS += -ldinput8 -ldxguid
win32:CONFIG += c++11

mac:LIBS += -framework IOKit
mac:LIBS += -framework CoreFoundation

INCLUDEPATH +=  ../../INCLUDES/QtGameControllerModif

SOURCES       +=  CODE/qgamecontroller.cpp
linux:SOURCES +=  CODE/qgamecontroller_linux.cpp
mac:SOURCES   +=  CODE/qgamecontroller_mac.cpp
win32:SOURCES +=  CODE/qgamecontroller_win.cpp

PUBLIC_HEADERS += ../../INCLUDES/QtGameControllerModif/qgamecontroller.h
PRIVATE_HEADERS +=  CODE/qgamecontroller_p.h
HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS









OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc