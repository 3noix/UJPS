CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
	LIBS += ../StaticLibs/SOURCES/RealJoysticks/debug/libRealJoysticks.a
}
CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
	LIBS += ../StaticLibs/SOURCES/RealJoysticks/release/libRealJoysticks.a
}

TEMPLATE = app
TARGET = Monitoring1
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT += core gui widgets

		
INCLUDEPATH +=  ../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../StaticLibs/INCLUDES/RealJoysticks/ \

HEADERS +=  CODE/MainWindow.h \
			CODE/WIDGETS/StandardJoystickWidget.h \
			CODE/WIDGETS/AxesWidget.h \
			CODE/WIDGETS/ButtonWidget.h \
			CODE/WIDGETS/PovWidgetDecorated.h \
			CODE/WIDGETS/PovWidget.h

SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/WIDGETS/StandardJoystickWidget.cpp \
			CODE/WIDGETS/AxesWidget.cpp \
			CODE/WIDGETS/ButtonWidget.cpp \
			CODE/WIDGETS/PovWidgetDecorated.cpp \
			CODE/WIDGETS/PovWidget.cpp

RESOURCES += resources.qrc
RC_FILE += icone.rc
