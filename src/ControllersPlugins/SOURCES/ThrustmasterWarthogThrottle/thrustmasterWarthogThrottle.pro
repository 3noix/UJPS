CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ThrustmasterWarthogThrottle
CONFIG += c++17 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc


win32-g++:LIBS += ../../../../3rdparty/bin_lib_windows/x86/hid.lib
win32-g++:LIBS += ../../../../3rdparty/bin_lib_windows/x86/setupapi.lib
win32-g++:LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a

win32-msvc*:LIBS += ../../../../3rdparty/bin_lib_windows/x64/hid.lib
win32-msvc*:LIBS += ../../../../3rdparty/bin_lib_windows/x64/setupapi.lib
win32-msvc*:LIBS += ../../../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../../../StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib


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

