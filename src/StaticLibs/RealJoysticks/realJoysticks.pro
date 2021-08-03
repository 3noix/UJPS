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


HEADERS +=  src/AbstractRealJoystickFactory.h \
			src/RealJoysticksManager.h \
			src/RealJoystick.h \
			src/RemoteJoystickServer.h


SOURCES +=  src/RealJoysticksManager.cpp \
			src/RealJoystick.cpp \
			src/RemoteJoystickServer.cpp \
			src/EnhancedJoystick.cpp \
			src/AxesRotator.cpp \
			src/curves/CurvePolynomial2.cpp \
			src/curves/CurvePolynomial3Centered.cpp \
			src/curves/CurvePolynomial3NotCentered.cpp \
			src/curves/CurveExpCentered.cpp \
			src/curves/CurveExpNotCentered.cpp \
			src/curves/CustomCurve.cpp

