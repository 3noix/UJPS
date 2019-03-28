CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = Monitoring
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += core gui widgets charts xmlpatterns network


win32-g++:LIBS += ../StaticLibs/SOURCES/Settings/$$MODE/libsettings.a
win32-g++:LIBS += ../StaticLibs/SOURCES/VigemWrapper/$$MODE/libvigemWrapper.a
win32-g++:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a

win32-msvc*:LIBS += ../StaticLibs/SOURCES/Settings/$$MODE/settings.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/VigemWrapper/$$MODE/vigemWrapper.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib


INCLUDEPATH +=  ../StaticLibs/INCLUDES/Settings/ \
				../StaticLibs/INCLUDES/VigemWrapper/ \
				../StaticLibs/INCLUDES/QtGameControllerModif/ \
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

