CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ProfileTestRemote
CONFIG += c++17 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/RealJoysticks/$$MODE/libRealJoysticks.a
win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/UjpsCore/$$MODE/libujpsCore.a
win32-g++:LIBS += $$(UJPSPATH)/3rdparty/vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/RealJoysticks/$$MODE/RealJoysticks.lib
win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/UjpsCore/$$MODE/ujpsCore.lib
win32-msvc*:LIBS += $$(UJPSPATH)/3rdparty/vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  $$(UJPSPATH)/include \
				$$(UJPSPATH)/src/ControllersPlugins/include


HEADERS +=  src/Profile.h
SOURCES +=  src/Profile.cpp

