CONFIG(debug, debug|release) {
    DESTDIR = debug
	LIBS += ../STATIC_LIBS/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
}
CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../STATIC_LIBS/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
}

TEMPLATE = app
TARGET = Monitoring
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT += core gui widgets

		
INCLUDEPATH +=  ../STATIC_LIBS/INCLUDES/QtGameControllerModif/ \
				../STATIC_LIBS/INCLUDES/RealJoysticks/ \

HEADERS +=  CODE/MainWindow.h \
			CODE/REAL_JOYSTICKS/RealJoysticksManager.h \
			CODE/REAL_JOYSTICKS/RealJoystick.h \
			CODE/WIDGETS/StandardJoystickWidget.h \
			CODE/WIDGETS/ButtonWidget.h

SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/REAL_JOYSTICKS/RealJoysticksManager.cpp \
			CODE/REAL_JOYSTICKS/RealJoystick.cpp \
			CODE/WIDGETS/StandardJoystickWidget.cpp \
			CODE/WIDGETS/ButtonWidget.cpp

RESOURCES += resources.qrc
RC_FILE += icone.rc
