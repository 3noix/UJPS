CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = UJPS_console
CONFIG += c++17 console
DESTDIR = ../../bin
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core gui network
DEFINES -= QT_NO_DEBUG


win32-g++:LIBS += ../StaticLibs/Settings/$$MODE/libsettings.a
win32-g++:LIBS += ../StaticLibs/VigemWrapper/$$MODE/libvigemWrapper.a
win32-g++:LIBS += ../StaticLibs/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../StaticLibs/RealJoysticks/$$MODE/libRealJoysticks.a
win32-g++:LIBS += ../StaticLibs/VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += ../StaticLibs/UjpsCore/$$MODE/libujpsCore.a
win32-g++:LIBS += ../../3rdparty/vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += ../StaticLibs/Settings/$$MODE/settings.lib
win32-msvc*:LIBS += ../StaticLibs/VigemWrapper/$$MODE/vigemWrapper.lib
win32-msvc*:LIBS += ../StaticLibs/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../StaticLibs/RealJoysticks/$$MODE/RealJoysticks.lib
win32-msvc*:LIBS += ../StaticLibs/VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += ../StaticLibs/UjpsCore/$$MODE/ujpsCore.lib
win32-msvc*:LIBS += ../../3rdparty/vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  ../../include


HEADERS +=  src/ProfileEngine.h \
			src/MessagesDirector.h
			
			
SOURCES +=  src/main_console.cpp \
			src/ProfileEngine.cpp \
			src/MessagesDirector.cpp


RC_FILE += icone.rc

