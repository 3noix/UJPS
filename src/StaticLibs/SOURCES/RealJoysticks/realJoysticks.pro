CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = realJoysticks
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += websockets httpserver


win32-g++:LIBS += ../QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-msvc*:LIBS += ../QtGameControllerModif/$$MODE/QtGameControllerModif.lib


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

