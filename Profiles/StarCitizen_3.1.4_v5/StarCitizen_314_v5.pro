win32-g++:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
	LIBS += ../../StaticLibs/SOURCES/RealJoysticks/debug/librealJoysticks.a
	LIBS += ../../StaticLibs/SOURCES/VirtualJoysticks/debug/libvirtualJoysticks.a
	LIBS += ../../StaticLibs/SOURCES/UjpsCore/debug/libujpsCore.a
}
win32-g++:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
	LIBS += ../../StaticLibs/SOURCES/RealJoysticks/release/librealJoysticks.a
	LIBS += ../../StaticLibs/SOURCES/VirtualJoysticks/release/libvirtualJoysticks.a
	LIBS += ../../StaticLibs/SOURCES/UjpsCore/release/libujpsCore.a
}

win32-msvc*:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/debug/QtGameControllerModif.lib
	LIBS += ../../StaticLibs/SOURCES/RealJoysticks/debug/realJoysticks.lib
	LIBS += ../../StaticLibs/SOURCES/VirtualJoysticks/debug/virtualJoysticks.lib
	LIBS += ../../StaticLibs/SOURCES/UjpsCore/debug/ujpsCore.lib
}
win32-msvc*:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/release/QtGameControllerModif.lib
	LIBS += ../../StaticLibs/SOURCES/RealJoysticks/release/realJoysticks.lib
	LIBS += ../../StaticLibs/SOURCES/VirtualJoysticks/release/virtualJoysticks.lib
	LIBS += ../../StaticLibs/SOURCES/UjpsCore/release/ujpsCore.lib
}


TEMPLATE = lib
TARGET = StarCitizen_314_v5
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += plugin c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


win32-g++:LIBS += ../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib
win32-msvc*:LIBS += ../../vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  ../../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../../StaticLibs/INCLUDES/Other/ \
				../../StaticLibs/INCLUDES/VirtualJoysticks/ \
				../../StaticLibs/INCLUDES/RealJoysticks/ \
				../../StaticLibs/INCLUDES/UjpsCore/ \
				../../ControllersPlugins/INCLUDES/

HEADERS +=  CODE/Profile.h
SOURCES +=  CODE/Profile.cpp

