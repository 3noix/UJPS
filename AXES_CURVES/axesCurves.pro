CONFIG(debug, debug|release) {
    DESTDIR = debug
	LIBS += ../STATIC_LIBS/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
}
CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../STATIC_LIBS/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
}


TEMPLATE = app
TARGET = AxesCurves
CONFIG += c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += core gui widgets charts
DEFINES -= QT_NO_DEBUG


INCLUDEPATH +=  ../STATIC_LIBS/INCLUDES/QtGameControllerModif/ \
				../STATIC_LIBS/INCLUDES/Other/ \
				../STATIC_LIBS/INCLUDES/RealJoysticks/


HEADERS +=  CODE/MainWindow.h \
			CODE/CurveChartView.h \
			CODE/REAL_JOYSTICKS/RealJoysticksManager.h \
			CODE/REAL_JOYSTICKS/RealJoystick.h \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogJoystick.h \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogThrottle.h \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/MfgCrosswindRudderPedals.h \
			CODE/CURVES/AbstractAxisCurve.h \
			CODE/CURVES/JCurve.h \
			CODE/CURVES/SCurve.h


SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/CurveChartView.cpp \
			CODE/REAL_JOYSTICKS/RealJoysticksManager.cpp \
			CODE/REAL_JOYSTICKS/RealJoystick.cpp \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogJoystick.cpp \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogThrottle.cpp \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/MfgCrosswindRudderPedals.cpp \
			CODE/CURVES/JCurve.cpp \
			CODE/CURVES/SCurve.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

