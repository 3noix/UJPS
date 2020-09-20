CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = StarCitizen_390_v1_basic
CONFIG += c++17 plugin
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a
win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/UjpsCore/$$MODE/libujpsCore.a
win32-g++:LIBS += $$(UJPSPATH)/3rdparty/vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib
win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += $$(UJPSPATH)/src/StaticLibs/SOURCES/UjpsCore/$$MODE/ujpsCore.lib
win32-msvc*:LIBS += $$(UJPSPATH)/3rdparty/vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  $$(UJPSPATH)/src/StaticLibs/INCLUDES/QtGameControllerModif/ \
				$$(UJPSPATH)/src/StaticLibs/INCLUDES/Other/ \
				$$(UJPSPATH)/src/StaticLibs/INCLUDES/VirtualJoysticks/ \
				$$(UJPSPATH)/src/StaticLibs/INCLUDES/RealJoysticks/ \
				$$(UJPSPATH)/src/StaticLibs/INCLUDES/UjpsCore/ \
				$$(UJPSPATH)/src/ControllersPlugins/INCLUDES/


HEADERS +=  CODE/Profile.h
SOURCES +=  CODE/Profile.cpp

