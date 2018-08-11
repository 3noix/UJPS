win32-g++:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
	LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/debug/librealJoysticks.a
}
win32-g++:CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
	LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/release/librealJoysticks.a
}

win32-msvc*:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/debug/QtGameControllerModif.lib
	LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/debug/realJoysticks.lib
}
win32-msvc*:CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/release/QtGameControllerModif.lib
	LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/release/realJoysticks.lib
}


TEMPLATE = lib
TARGET = ThrustmasterWarthogThrottle
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += plugin c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc

win32-g++:LIBS += bin_lib_windows/x86/hid.lib
win32-g++:LIBS += bin_lib_windows/x86/setupapi.lib
win32-msvc*:LIBS += bin_lib_windows/x64/hid.lib
win32-msvc*:LIBS += bin_lib_windows/x64/setupapi.lib

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

