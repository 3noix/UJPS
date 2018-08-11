win32-g++:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a
	LIBS += ../StaticLibs/SOURCES/VirtualJoysticks/debug/libvirtualJoysticks.a
	LIBS += ../StaticLibs/SOURCES/UjpsCore/debug/libujpsCore.a
}
win32-g++:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a
	LIBS += ../StaticLibs/SOURCES/VirtualJoysticks/release/libvirtualJoysticks.a
	LIBS += ../StaticLibs/SOURCES/UjpsCore/release/libujpsCore.a
}

win32-msvc*:CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/debug/QtGameControllerModif.lib
	LIBS += ../StaticLibs/SOURCES/VirtualJoysticks/debug/virtualJoysticks.lib
	LIBS += ../StaticLibs/SOURCES/UjpsCore/debug/ujpsCore.lib
}
win32-msvc*:CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../StaticLibs/SOURCES/QtGameControllerModif/release/QtGameControllerModif.lib
	LIBS += ../StaticLibs/SOURCES/VirtualJoysticks/release/virtualJoysticks.lib
	LIBS += ../StaticLibs/SOURCES/UjpsCore/release/ujpsCore.lib
}


TEMPLATE = app
TARGET = UJPS
CONFIG += c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT = core xmlpatterns gui widgets
DEFINES -= QT_NO_DEBUG


win32-g++:LIBS += ../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib
win32-msvc*:LIBS += ../vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib

INCLUDEPATH +=  ../StaticLibs/INCLUDES/QtGameControllerModif/ \
				../StaticLibs/INCLUDES/Other/ \
				../StaticLibs/INCLUDES/VirtualJoysticks/ \
				../StaticLibs/INCLUDES/RealJoysticks/ \
				../StaticLibs/INCLUDES/UjpsCore/


HEADERS +=  CODE/ProfileEngine.h \
			CODE/HMI/MainWindow.h \
			CODE/HMI/TextEdit.h \
			CODE/COMPILER/AbstractCompiler.h \
			CODE/COMPILER/QtCompiler.h \
			CODE/COMPILER/QtCompilationProcess.h \
			CODE/COMPILER/CompilationWidget.h \
			CODE/SETTINGS/ApplicationSettings.h \
			CODE/SETTINGS/AbstractSettingsWidget.h \
			CODE/SETTINGS/SettingsDialog.h \
			CODE/SETTINGS/MyFileDialog.h \
			CODE/SETTINGS/GeneralSettingsWidget.h \
			CODE/SETTINGS/VJoySettingsWidget.h \
			CODE/XML/AbstractXmlInfo.h \
			CODE/XML/XmlValidationMessageHandler.h \
			CODE/XML/GenericPropertiesInfo.h
			
			
SOURCES +=  CODE/main.cpp \
			CODE/ProfileEngine.cpp \
			CODE/otherFunctions.cpp \
			CODE/HMI/MainWindow.cpp \
			CODE/HMI/TextEdit.cpp \
			CODE/COMPILER/QtCompiler.cpp \
			CODE/COMPILER/QtCompilationProcess.cpp \
			CODE/COMPILER/CompilationWidget.cpp \
			CODE/SETTINGS/ApplicationSettings.cpp \
			CODE/SETTINGS/SettingsDialog.cpp \
			CODE/SETTINGS/MyFileDialog.cpp \
			CODE/SETTINGS/GeneralSettingsWidget.cpp \
			CODE/SETTINGS/VJoySettingsWidget.cpp \
			CODE/XML/AbstractXmlInfo.cpp \
			CODE/XML/XmlValidationMessageHandler.cpp \
			CODE/XML/GenericPropertiesInfo.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

