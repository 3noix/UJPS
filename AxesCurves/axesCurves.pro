CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = AxesCurves
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += core gui widgets charts
DEFINES -= QT_NO_DEBUG


win32-g++:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/libQtGameControllerModif.a
win32-g++:LIBS += ../StaticLibs/SOURCES/RealJoysticks/$$MODE/libRealJoysticks.a

win32-msvc*:LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/$$MODE/QtGameControllerModif.lib
win32-msvc*:LIBS += ../StaticLibs/SOURCES/RealJoysticks/$$MODE/RealJoysticks.lib


INCLUDEPATH +=  ../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../StaticLibs/INCLUDES/Other/ \
				../StaticLibs/INCLUDES/RealJoysticks/


HEADERS +=  CODE/MainWindow.h \
			CODE/CurveChartView.h \
			CODE/CURVES/AbstractAxisCurve.h \
			CODE/CURVES/GuiCurvePolynomial2.h \
			CODE/CURVES/GuiCurvePolynomial3Centered.h \
			CODE/CURVES/GuiCurvePolynomial3NotCentered.h \
			CODE/CURVES/GuiCurveExpCentered.h \
			CODE/CURVES/GuiCurveExpNotCentered.h


SOURCES +=  CODE/main.cpp \
			CODE/MainWindow.cpp \
			CODE/CurveChartView.cpp \
			CODE/CURVES/GuiCurvePolynomial2.cpp \
			CODE/CURVES/GuiCurvePolynomial3Centered.cpp \
			CODE/CURVES/GuiCurvePolynomial3NotCentered.cpp \
			CODE/CURVES/GuiCurveExpCentered.cpp \
			CODE/CURVES/GuiCurveExpNotCentered.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

