CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = UJPS
CONFIG += c++17
DESTDIR = ../../bin
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets network
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
			src/hmi/MainWindow.h \
			src/hmi/TextEdit.h \
			src/compiler/AbstractCompiler.h \
			src/compiler/QtCompiler.h \
			src/compiler/QtCompilationProcess.h \
			src/compiler/CompilationWidget.h \
			src/settings/GeneralSettingsWidget.h
			
			
SOURCES +=  src/main.cpp \
			src/ProfileEngine.cpp \
			src/hmi/MainWindow.cpp \
			src/hmi/TextEdit.cpp \
			src/compiler/QtCompiler.cpp \
			src/compiler/QtCompilationProcess.cpp \
			src/compiler/CompilationWidget.cpp \
			src/settings/GeneralSettingsWidget.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

