CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ProfileTestRemote
CONFIG += c++11 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


win32-g++:LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../../StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a
win32-g++:LIBS += ../../StaticLibs/SOURCES/VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += ../../StaticLibs/SOURCES/UjpsCore/$$MODE/libujpsCore.a
win32-g++:LIBS += ../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../../StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib
win32-msvc*:LIBS += ../../StaticLibs/SOURCES/VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += ../../StaticLibs/SOURCES/UjpsCore/$$MODE/ujpsCore.lib
win32-msvc*:LIBS += ../../vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  ../../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../../StaticLibs/INCLUDES/Other/ \
				../../StaticLibs/INCLUDES/VirtualJoysticks/ \
				../../StaticLibs/INCLUDES/RealJoysticks/ \
				../../StaticLibs/INCLUDES/UjpsCore/ \
				../../ControllersPlugins/INCLUDES/


HEADERS +=  CODE/Profile.h
SOURCES +=  CODE/Profile.cpp

