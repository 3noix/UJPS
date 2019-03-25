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
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT = core


LIBS += -ldinput8 -ldxguid -lXInput


INCLUDEPATH +=  ../../INCLUDES/Other \
				../../INCLUDES/QtGameControllerModif


HEADERS +=  ../../INCLUDES/QtGameControllerModif/GameController.h \
			../../INCLUDES/QtGameControllerModif/GameControllerDirectInput.h \
			../../INCLUDES/QtGameControllerModif/GameControllerXInput.h \
			../../INCLUDES/QtGameControllerModif/GameControllersEnumThread.h


SOURCES +=  CODE/GameController.cpp \
			CODE/GameControllerDirectInput.cpp \
			CODE/GameControllerXInput.cpp \
			CODE/GameControllerEvents.cpp \
			CODE/GameControllersEnumThread.cpp

