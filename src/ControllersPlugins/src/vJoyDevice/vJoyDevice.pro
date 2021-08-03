CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = vJoyDevice
CONFIG += c++17 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc


win32-g++:LIBS += ../../../StaticLibs/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../../../StaticLibs/RealJoysticks/$$MODE/libRealJoysticks.a

win32-msvc*:LIBS += ../../../StaticLibs/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../../../StaticLibs/RealJoysticks/$$MODE/RealJoysticks.lib


INCLUDEPATH +=  ../../../../include


HEADERS +=  src/RealJoystickFactory.h \
			src/vJoyDevice.h


SOURCES +=  src/vJoyDevice.cpp

