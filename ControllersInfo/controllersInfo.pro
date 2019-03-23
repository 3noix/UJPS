CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = ControllersInfo
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += core gui widgets


win32-g++:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-msvc*:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib

		
INCLUDEPATH +=  ../StaticLibs/INCLUDES/QtGameControllerModif/


HEADERS +=  CODE/MainWindow.h \
			CODE/WorkerThread.h


SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/WorkerThread.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

