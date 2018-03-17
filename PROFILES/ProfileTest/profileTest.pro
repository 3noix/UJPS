CONFIG(debug, debug|release) {
    DESTDIR = debug
	LIBS += ../../STATIC_LIBS/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a \
			../../STATIC_LIBS/SOURCES/VirtualJoysticks/debug/libvirtualJoysticks.a \
			../../STATIC_LIBS/SOURCES/UjpsCore/debug/libujpsCore.a
}
CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../../STATIC_LIBS/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a \
			../../STATIC_LIBS/SOURCES/VirtualJoysticks/release/libvirtualJoysticks.a \
			../../STATIC_LIBS/SOURCES/UjpsCore/release/libujpsCore.a
}

TEMPLATE = lib
TARGET = ProfileTest
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += plugin c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


LIBS += ../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib


INCLUDEPATH +=  ../../STATIC_LIBS/INCLUDES/QtGameControllerModif/ \
				../../STATIC_LIBS/INCLUDES/Other/ \
				../../STATIC_LIBS/INCLUDES/VirtualJoysticks/ \
				../../STATIC_LIBS/INCLUDES/RealJoysticks/ \
				../../STATIC_LIBS/INCLUDES/UjpsCore/


HEADERS +=  CODE/Profile.h \
			CODE/REAL_JOYSTICKS/RealJoysticksManager.h \
			CODE/REAL_JOYSTICKS/EnhancedJoystick.h \
			CODE/REAL_JOYSTICKS/RealJoystick.h \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogJoystick.h \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogThrottle.h \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/MfgCrosswindRudderPedals.h \
			CODE/REAL_JOYSTICKS/CURVES/SCurve.h \
			CODE/REAL_JOYSTICKS/CURVES/JCurve.h \
			CODE/REAL_JOYSTICKS/CURVES/CustomCurve.h
			

SOURCES +=  CODE/Profile.cpp \
			CODE/REAL_JOYSTICKS/RealJoysticksManager.cpp \
			CODE/REAL_JOYSTICKS/EnhancedJoystick.cpp \
			CODE/REAL_JOYSTICKS/RealJoystick.cpp \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogJoystick.cpp \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/WarthogThrottle.cpp \
			CODE/REAL_JOYSTICKS/SPECIFIC_JOYSTICKS/MfgCrosswindRudderPedals.cpp \
			CODE/REAL_JOYSTICKS/CURVES/SCurve.cpp \
			CODE/REAL_JOYSTICKS/CURVES/JCurve.cpp \
			CODE/REAL_JOYSTICKS/CURVES/CustomCurve.cpp

