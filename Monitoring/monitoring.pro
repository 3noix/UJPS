win32-g++:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
	LIBS += ../StaticLibs/SOURCES/RealJoysticks/debug/libRealJoysticks.a
}
win32-g++:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
	LIBS += ../StaticLibs/SOURCES/RealJoysticks/release/libRealJoysticks.a
}

win32-msvc*:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/QtGameControllerModif.lib
	LIBS += ../StaticLibs/SOURCES/RealJoysticks/debug/RealJoysticks.lib
}
win32-msvc*:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/QtGameControllerModif.lib
	LIBS += ../StaticLibs/SOURCES/RealJoysticks/release/RealJoysticks.lib
}


TEMPLATE = app
TARGET = Monitoring
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11
QT += core gui widgets charts

		
INCLUDEPATH +=  ../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../StaticLibs/INCLUDES/RealJoysticks/

HEADERS +=  CODE/MainWindow.h \
			CODE/WIDGETS/StandardJoystickWidget.h \
			CODE/WIDGETS/StandardJoystickWidgetRaw.h \
			CODE/WIDGETS/AxesWidget.h \
			CODE/WIDGETS/ButtonWidget.h \
			CODE/WIDGETS/PovWidgetDecorated.h \
			CODE/WIDGETS/PovWidget.h \
			CODE/WIDGETS/MyChartWidget.h \
			CODE/WIDGETS/MyCheckBox.h

SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/WIDGETS/StandardJoystickWidget.cpp \
			CODE/WIDGETS/StandardJoystickWidgetRaw.cpp \
			CODE/WIDGETS/AxesWidget.cpp \
			CODE/WIDGETS/ButtonWidget.cpp \
			CODE/WIDGETS/PovWidgetDecorated.cpp \
			CODE/WIDGETS/PovWidget.cpp \
			CODE/WIDGETS/MyChartWidget.cpp \
			CODE/WIDGETS/MyCheckBox.cpp

RESOURCES += resources.qrc
RC_FILE += icone.rc
