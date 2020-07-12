CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = MFD_smart
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += widgets network


INCLUDEPATH += $$(UJPSPATH)/src/ControllersPlugins/INCLUDES


HEADERS =   CODE/MfdWidget.h \
			CODE/DEFAULT/MfdScene.h \
			CODE/DEFAULT/MfdBezelSegmentH.h \
			CODE/DEFAULT/MfdBezelSegmentV.h \
			CODE/DEFAULT/MfdBezelCorner1.h \
			CODE/DEFAULT/MfdBezelCorner2.h \
			CODE/DEFAULT/MfdSquareButton.h \
			CODE/DEFAULT/MfdRectangularButton.h \
			CODE/DEFAULT/MfdScreen.h \
			CODE/DEFAULT/Geometry.h \
			CODE/DEFAULT/Brushs.h \
			CODE/CUSTOM/MfdTextItem.h \
			CODE/CUSTOM/MfdSelectableTextItem.h \
			CODE/CUSTOM/MyScene.h \
			CODE/CUSTOM/AbstractMfdPage.h \
			CODE/CUSTOM/MfdPage_PWR.h \
			CODE/CUSTOM/MfdPage_IFCS.h \
			CODE/CUSTOM/MfdPage_SYS.h \
			CODE/REMOTE/ConnectionWidget.h \
			CODE/REMOTE/RemoteJoystickTcpClient.h


SOURCES =   CODE/main.cpp \
			CODE/MfdWidget.cpp \
			CODE/DEFAULT/MfdScene.cpp \
			CODE/DEFAULT/MfdBezelSegmentH.cpp \
			CODE/DEFAULT/MfdBezelSegmentV.cpp \
			CODE/DEFAULT/MfdBezelCorner1.cpp \
			CODE/DEFAULT/MfdBezelCorner2.cpp \
			CODE/DEFAULT/MfdSquareButton.cpp \
			CODE/DEFAULT/MfdRectangularButton.cpp \
			CODE/DEFAULT/MfdScreen.cpp \
			CODE/CUSTOM/MfdTextItem.cpp \
			CODE/CUSTOM/MfdSelectableTextItem.cpp \
			CODE/CUSTOM/MyScene.cpp \
			CODE/CUSTOM/MfdPage_PWR.cpp \
			CODE/CUSTOM/MfdPage_IFCS.cpp \
			CODE/CUSTOM/MfdPage_SYS.cpp \
			CODE/REMOTE/ConnectionWidget.cpp \
			CODE/REMOTE/RemoteJoystickTcpClient.cpp

