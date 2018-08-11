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


win32-g++:LIBS += ../../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib
win32-msvc*:LIBS += ../../../vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib

INCLUDEPATH +=  ../../INCLUDES/Other/ \
				../../INCLUDES/VirtualJoysticks/

HEADERS +=  ../../INCLUDES/VirtualJoysticks/VirtualJoystick.h
SOURCES +=  CODE/VirtualJoystick.cpp

