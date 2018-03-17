CONFIG(debug, debug|release) {
    DESTDIR = debug
}
CONFIG(release, debug|release) {
    DESTDIR = release
}

TEMPLATE = app
TARGET = CleanQtProjects
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += console

SOURCES += main.cpp
