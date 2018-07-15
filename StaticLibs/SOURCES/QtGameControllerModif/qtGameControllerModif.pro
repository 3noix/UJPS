CONFIG(debug, debug|release) {
	DESTDIR = debug
}
CONFIG(release, debug|release) {
	DESTDIR = release
}


TEMPLATE = lib
TARGET = QtGameControllerModif
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT = core


LIBS += -ldinput8 -ldxguid -lXInput


INCLUDEPATH +=  ../../INCLUDES/Other \
				../../INCLUDES/QtGameControllerModif


HEADERS +=  ../../INCLUDES/QtGameControllerModif/GameController.h \
			../../INCLUDES/QtGameControllerModif/GameControllerDirectInput.h \
			../../INCLUDES/QtGameControllerModif/GameControllerXInput.h


SOURCES +=  CODE/GameController.cpp \
			CODE/GameControllerDirectInput.cpp \
			CODE/GameControllerXInput.cpp \
			CODE/GameControllerEvents.cpp
