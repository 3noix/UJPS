CONFIG(debug, debug|release) {
    DESTDIR = debug
	LIBS += ../QtGameControllerModif/debug/libQtGameControllerModif.a
}
CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../QtGameControllerModif/release/libQtGameControllerModif.a
}


TEMPLATE = lib
TARGET = realJoysticks
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT += network

INCLUDEPATH +=  ../../INCLUDES/QtGameControllerModif/ \
				../../INCLUDES/Other/ \
				../../INCLUDES/RealJoysticks/


HEADERS +=  ../../INCLUDES/RealJoysticks/AbstractRealJoystickFactory.h \
			../../INCLUDES/RealJoysticks/RealJoysticksManager.h \
			../../INCLUDES/RealJoysticks/RealJoystick.h \
			../../INCLUDES/RealJoysticks/RemoteJoystickServer.h


SOURCES +=  CODE/RealJoysticksManager.cpp \
			CODE/RealJoystick.cpp \
			CODE/RemoteJoystickServer.cpp \
			CODE/EnhancedJoystick.cpp \
			CODE/CURVES/SCurve.cpp \
			CODE/CURVES/JCurve.cpp \
			CODE/CURVES/CustomCurve.cpp

