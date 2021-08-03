CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = MFD_smart
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += widgets websockets


INCLUDEPATH += $$(UJPSPATH)/src/ControllersPlugins/include


HEADERS =   src/MfdWidget.h \
			src/default/MfdScene.h \
			src/default/MfdBezelSegmentH.h \
			src/default/MfdBezelSegmentV.h \
			src/default/MfdBezelCorner1.h \
			src/default/MfdBezelCorner2.h \
			src/default/MfdSquareButton.h \
			src/default/MfdRectangularButton.h \
			src/default/MfdScreen.h \
			src/default/Geometry.h \
			src/default/Brushs.h \
			src/custom/MfdTextItem.h \
			src/custom/MfdSelectableTextItem.h \
			src/custom/MyScene.h \
			src/custom/AbstractMfdPage.h \
			src/custom/MfdPage_PWR.h \
			src/custom/MfdPage_IFCS.h \
			src/custom/MfdPage_SYS.h \
			src/remote/ConnectionWidget.h \
			src/remote/RemoteJoystickClient.h


SOURCES =   src/main.cpp \
			src/MfdWidget.cpp \
			src/default/MfdScene.cpp \
			src/default/MfdBezelSegmentH.cpp \
			src/default/MfdBezelSegmentV.cpp \
			src/default/MfdBezelCorner1.cpp \
			src/default/MfdBezelCorner2.cpp \
			src/default/MfdSquareButton.cpp \
			src/default/MfdRectangularButton.cpp \
			src/default/MfdScreen.cpp \
			src/custom/MfdTextItem.cpp \
			src/custom/MfdSelectableTextItem.cpp \
			src/custom/MyScene.cpp \
			src/custom/MfdPage_PWR.cpp \
			src/custom/MfdPage_IFCS.cpp \
			src/custom/MfdPage_SYS.cpp \
			src/remote/ConnectionWidget.cpp \
			src/remote/RemoteJoystickClient.cpp

