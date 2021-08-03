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


HEADERS +=  src/AbstractSettingsWidget.h \
			src/SettingsDialog.h


SOURCES +=  src/otherFunctions.cpp \
			src/ApplicationSettings.cpp \
			src/SettingsDialog.cpp \
			src/MyFileDialog.cpp

