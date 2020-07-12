CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = RemoteControllerTcpTest
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += network widgets


HEADERS =   CODE/MainWindow.h \
			CODE/ConnectionWidget.h \
			CODE/RemoteJoystickTcpClient.h


SOURCES =   CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/ConnectionWidget.cpp \
			CODE/RemoteJoystickTcpClient.cpp

