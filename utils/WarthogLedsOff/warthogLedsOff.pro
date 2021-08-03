CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = WarthogLedsOff
CONFIG += c++17 console
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += network



win32-g++:LIBS += ../../3rdparty/bin_lib_windows/x86/hid.lib
win32-g++:LIBS += ../../3rdparty/bin_lib_windows/x86/setupapi.lib

win32-msvc*:LIBS += ../../3rdparty/bin_lib_windows/x64/hid.lib
win32-msvc*:LIBS += ../../3rdparty/bin_lib_windows/x64/setupapi.lib


HEADERS +=  src/HidDevice.h \
			src/VigemPidWhiteListerConsole.h


SOURCES +=  src/main.cpp \
			src/HidDevice.cpp \
			src/VigemPidWhiteListerConsole.cpp

