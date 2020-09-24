CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = settings
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT += widgets


INCLUDEPATH +=  ../../INCLUDES/Settings/


HEADERS +=  ../../INCLUDES/Settings/AbstractSettingsWidget.h \
			../../INCLUDES/Settings/SettingsDialog.h


SOURCES +=  CODE/otherFunctions.cpp \
			CODE/ApplicationSettings.cpp \
			CODE/SettingsDialog.cpp \
			CODE/MyFileDialog.cpp

