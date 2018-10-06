CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = RemoteControllerTest_v4
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += network widgets


HEADERS =   CODE/MainWindow.h \
			CODE/ConnectionWidget.h \
			CODE/TextEdit.h \
			CODE/RemoteJoystickClient.h


SOURCES =   CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/ConnectionWidget.cpp \
			CODE/TextEdit.cpp \
			CODE/RemoteJoystickClient.cpp

