CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ProfileBasicExample
CONFIG += c++11 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


win32-g++:LIBS += ../../../src/StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../../../src/StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a
win32-g++:LIBS += ../../../src/StaticLibs/SOURCES/VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += ../../../src/StaticLibs/SOURCES/UjpsCore/$$MODE/libujpsCore.a
win32-g++:LIBS += ../../../3rdparty/vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += ../../../src/StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../../../src/StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib
win32-msvc*:LIBS += ../../../src/StaticLibs/SOURCES/VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += ../../../src/StaticLibs/SOURCES/UjpsCore/$$MODE/ujpsCore.lib
win32-msvc*:LIBS += ../../../3rdparty/vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  ../../../src/StaticLibs/INCLUDES/QtGameControllerModif/ \
				../../../src/StaticLibs/INCLUDES/Other/ \
				../../../src/StaticLibs/INCLUDES/VirtualJoysticks/ \
				../../../src/StaticLibs/INCLUDES/RealJoysticks/ \
				../../../src/StaticLibs/INCLUDES/UjpsCore/ \
				../../../src/ControllersPlugins/INCLUDES/


HEADERS +=  CODE/Profile.h
SOURCES +=  CODE/Profile.cpp

