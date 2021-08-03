CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = RemoteControllerTest_v4
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += widgets websockets


HEADERS =   src/MainWindow.h \
			src/ConnectionWidget.h \
			src/RemoteJoystickClient.h


SOURCES =   src/main.cpp \
			src/MainWindow.cpp \
			src/ConnectionWidget.cpp \
			src/RemoteJoystickClient.cpp

