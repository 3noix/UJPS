CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = UJPS_console
CONFIG += c++11 console
DESTDIR = ../bin
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core gui xmlpatterns network
DEFINES -= QT_NO_DEBUG


win32-g++:LIBS += ../StaticLibs/SOURCES/Settings/$$MODE/libsettings.a
win32-g++:LIBS += ../StaticLibs/SOURCES/VigemWrapper/$$MODE/libvigemWrapper.a
win32-g++:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a
win32-g++:LIBS += ../StaticLibs/SOURCES/VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += ../StaticLibs/SOURCES/UjpsCore/$$MODE/libujpsCore.a
win32-g++:LIBS += ../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += ../StaticLibs/SOURCES/Settings/$$MODE/settings.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/VigemWrapper/$$MODE/vigemWrapper.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/UjpsCore/$$MODE/ujpsCore.lib
win32-msvc*:LIBS += ../vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  ../StaticLibs/INCLUDES/Settings/ \
				../StaticLibs/INCLUDES/VigemWrapper/ \
				../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../StaticLibs/INCLUDES/Other/ \
				../StaticLibs/INCLUDES/VirtualJoysticks/ \
				../StaticLibs/INCLUDES/RealJoysticks/ \
				../StaticLibs/INCLUDES/UjpsCore/


HEADERS +=  CODE/ProfileEngine.h \
			CODE/MessagesDirector.h
			
			
SOURCES +=  CODE/main_console.cpp \
			CODE/ProfileEngine.cpp \
			CODE/MessagesDirector.cpp


RC_FILE += icone.rc

