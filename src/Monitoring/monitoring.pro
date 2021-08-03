CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = Monitoring
CONFIG += c++17
DESTDIR = ../../bin
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets charts network


win32-g++:LIBS += ../StaticLibs/Settings/$$MODE/libsettings.a
win32-g++:LIBS += ../StaticLibs/VigemWrapper/$$MODE/libvigemWrapper.a
win32-g++:LIBS += ../StaticLibs/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../StaticLibs/RealJoysticks/$$MODE/libRealJoysticks.a

win32-msvc*:LIBS += ../StaticLibs/Settings/$$MODE/settings.lib
win32-msvc*:LIBS += ../StaticLibs/VigemWrapper/$$MODE/vigemWrapper.lib
win32-msvc*:LIBS += ../StaticLibs/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../StaticLibs/RealJoysticks/$$MODE/RealJoysticks.lib


INCLUDEPATH +=  ../../include


HEADERS +=  src/MainWindow.h \
			src/widgets/StandardJoystickWidget.h \
			src/widgets/StandardJoystickWidgetRaw.h \
			src/widgets/AxesWidget.h \
			src/widgets/ButtonWidget.h \
			src/widgets/PovWidgetDecorated.h \
			src/widgets/PovWidget.h \
			src/widgets/MyChartWidget.h \
			src/widgets/MyCheckBox.h


SOURCES +=  src/main.cpp \
			src/MainWindow.cpp \
			src/widgets/StandardJoystickWidget.cpp \
			src/widgets/StandardJoystickWidgetRaw.cpp \
			src/widgets/AxesWidget.cpp \
			src/widgets/ButtonWidget.cpp \
			src/widgets/PovWidgetDecorated.cpp \
			src/widgets/PovWidget.cpp \
			src/widgets/MyChartWidget.cpp \
			src/widgets/MyCheckBox.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

