CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a \
			../../../StaticLibs/SOURCES/RealJoysticks/debug/librealJoysticks.a
}
CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a \
			../../../StaticLibs/SOURCES/RealJoysticks/release/librealJoysticks.a
}

TEMPLATE = lib
TARGET = ThrustmasterWarthogThrottle
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += plugin c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc

LIBS += bin_lib_windows/x86/hid.lib
LIBS += bin_lib_windows/x86/setupapi.lib

INCLUDEPATH +=  ../../../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../../../StaticLibs/INCLUDES/Other/ \
				../../../StaticLibs/INCLUDES/RealJoysticks/


HEADERS +=  CODE/RealJoystickFactory.h \
			CODE/ThrustmasterWarthogThrottle.h \
			CODE/WriteToHidThread.h \
			CODE/HidDevice.h

SOURCES +=  CODE/ThrustmasterWarthogThrottle.cpp \
			CODE/WriteToHidThread.cpp \
			CODE/HidDevice.cpp

