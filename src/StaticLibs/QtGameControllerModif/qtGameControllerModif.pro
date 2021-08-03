CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = QtGameControllerModif
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core


LIBS += -ldinput8 -ldxguid -lXInput


HEADERS +=  src/GameController.h \
			src/GameControllersEnumThread.h \
			src/GameControllerDirectInput.h \
			src/GameControllerXInput.h


SOURCES +=  src/GameControllerDirectInput.cpp \
			src/GameControllersEnumThread.cpp \
			src/GameControllerXInput.cpp \
			src/GameControllerEnumerator.cpp

