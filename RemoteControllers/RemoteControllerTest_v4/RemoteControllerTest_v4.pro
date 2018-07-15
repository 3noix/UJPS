CONFIG(debug, debug|release) {
	DESTDIR = debug
}
CONFIG(release, debug|release) {
	DESTDIR = release
}


TEMPLATE = app
TARGET = RemoteControllerTest_v4
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += c++11
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

