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


HEADERS =   CODE/MainWindow.h \
			CODE/ConnectionWidget.h \
			CODE/RemoteJoystickClient.h


SOURCES =   CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/ConnectionWidget.cpp \
			CODE/RemoteJoystickClient.cpp

