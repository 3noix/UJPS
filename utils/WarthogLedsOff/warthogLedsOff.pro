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


HEADERS +=  CODE/HidDevice.h \
			CODE/VigemPidWhiteListerConsole.h


SOURCES +=  CODE/main.cpp \
			CODE/HidDevice.cpp \
			CODE/VigemPidWhiteListerConsole.cpp

