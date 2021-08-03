CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = AxesCurves
CONFIG += c++17
DESTDIR = ../../bin
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets charts network
DEFINES -= QT_NO_DEBUG


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
			src/CurveChartView.h \
			src/curves/AbstractAxisCurve.h \
			src/curves/GuiCurvePolynomial2.h \
			src/curves/GuiCurvePolynomial3Centered.h \
			src/curves/GuiCurvePolynomial3NotCentered.h \
			src/curves/GuiCurveExpCentered.h \
			src/curves/GuiCurveExpNotCentered.h


SOURCES +=  src/main.cpp \
			src/MainWindow.cpp \
			src/CurveChartView.cpp \
			src/curves/GuiCurvePolynomial2.cpp \
			src/curves/GuiCurvePolynomial3Centered.cpp \
			src/curves/GuiCurvePolynomial3NotCentered.cpp \
			src/curves/GuiCurveExpCentered.cpp \
			src/curves/GuiCurveExpNotCentered.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

