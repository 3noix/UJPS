CONFIG(debug, debug|release) {
    DESTDIR = debug
}
CONFIG(release, debug|release) {
    DESTDIR = release
}


TEMPLATE = lib
TARGET = virtualJoysticks
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11


LIBS += ../../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

INCLUDEPATH +=  ../../INCLUDES/Other/ \
				../../INCLUDES/VirtualJoysticks/

HEADERS +=  ../../INCLUDES/VirtualJoysticks/VirtualJoystick.h
SOURCES +=  CODE/VirtualJoystick.cpp

