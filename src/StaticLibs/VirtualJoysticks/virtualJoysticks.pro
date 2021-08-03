CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = virtualJoysticks
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc


win32-g++:LIBS += ../../../3rdparty/vJoy218SDK-291116/SDK/lib/vJoyInterface.lib
win32-msvc*:LIBS += ../../../3rdparty/vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


HEADERS +=  src/VirtualJoystick.h \
			src/VirtualJoystickPrivate.h
			
			
SOURCES +=  src/VirtualJoystick.cpp \
			src/VirtualJoystickPrivate.cpp

