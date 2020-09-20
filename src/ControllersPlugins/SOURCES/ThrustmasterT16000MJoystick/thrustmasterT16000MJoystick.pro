CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ThrustmasterT16000MJoystick
CONFIG += c++17 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc


win32-g++:LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a

win32-msvc*:LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib


INCLUDEPATH +=  ../../../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../../../StaticLibs/INCLUDES/Other/ \
				../../../StaticLibs/INCLUDES/RealJoysticks/


HEADERS +=  CODE/RealJoystickFactory.h \
			CODE/ThrustmasterT16000MJoystick.h


SOURCES +=  CODE/ThrustmasterT16000MJoystick.cpp

