CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a \
			../../StaticLibs/SOURCES/RealJoysticks/debug/librealJoysticks.a \
			../../StaticLibs/SOURCES/VirtualJoysticks/debug/libvirtualJoysticks.a \
			../../StaticLibs/SOURCES/UjpsCore/debug/libujpsCore.a
}
CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a \
			../../StaticLibs/SOURCES/RealJoysticks/release/librealJoysticks.a \
			../../StaticLibs/SOURCES/VirtualJoysticks/release/libvirtualJoysticks.a \
			../../StaticLibs/SOURCES/UjpsCore/release/libujpsCore.a
}

TEMPLATE = lib
TARGET = StarCitizen_301_v1
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += plugin c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


LIBS += ../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib


INCLUDEPATH +=  ../../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../../StaticLibs/INCLUDES/Other/ \
				../../StaticLibs/INCLUDES/VirtualJoysticks/ \
				../../StaticLibs/INCLUDES/RealJoysticks/ \
				../../StaticLibs/INCLUDES/UjpsCore/ \
				../../ControllersPlugins/INCLUDES/

HEADERS +=  CODE/Profile.h
SOURCES +=  CODE/Profile.cpp

