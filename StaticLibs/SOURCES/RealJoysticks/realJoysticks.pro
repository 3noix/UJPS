win32-g++:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../QtGameControllerModif/debug/libQtGameControllerModif.a
}
win32-g++:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../QtGameControllerModif/release/libQtGameControllerModif.a
}

win32-msvc*:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../QtGameControllerModif/debug/QtGameControllerModif.lib
}
win32-msvc*:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../QtGameControllerModif/release/QtGameControllerModif.lib
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
			CODE/AxesRotator.cpp \
			CODE/CURVES/CurvePolynomial2.cpp \
			CODE/CURVES/CurvePolynomial3Centered.cpp \
			CODE/CURVES/CurvePolynomial3NotCentered.cpp \
			CODE/CURVES/CurveExpCentered.cpp \
			CODE/CURVES/CurveExpNotCentered.cpp \
			CODE/CURVES/CustomCurve.cpp

