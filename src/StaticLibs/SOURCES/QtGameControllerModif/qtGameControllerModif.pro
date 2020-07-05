CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = QtGameControllerModif
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core


LIBS += -ldinput8 -ldxguid -lXInput


INCLUDEPATH +=  ../../INCLUDES/Other \
				../../INCLUDES/QtGameControllerModif


HEADERS +=  ../../INCLUDES/QtGameControllerModif/GameController.h \
			../../INCLUDES/QtGameControllerModif/GameControllersEnumThread.h \
			CODE/GameControllerDirectInput.h \
			CODE/GameControllerXInput.h


SOURCES +=  CODE/GameControllerDirectInput.cpp \
			CODE/GameControllersEnumThread.cpp \
			CODE/GameControllerEvents.cpp \
			CODE/GameControllerXInput.cpp \
			CODE/GameControllerEnumerator.cpp

