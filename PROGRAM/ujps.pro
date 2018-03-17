CONFIG(debug, debug|release) {
    DESTDIR = debug
	LIBS += ../STATIC_LIBS/SOURCES/QtGameControllerModif/debug/libQtGameControllerModif.a \
			../STATIC_LIBS/SOURCES/VirtualJoysticks/debug/libvirtualJoysticks.a \
			../STATIC_LIBS/SOURCES/UjpsCore/debug/libujpsCore.a
}
CONFIG(release, debug|release) {
    DESTDIR = release
	LIBS += ../STATIC_LIBS/SOURCES/QtGameControllerModif/release/libQtGameControllerModif.a \
			../STATIC_LIBS/SOURCES/VirtualJoysticks/release/libvirtualJoysticks.a \
			../STATIC_LIBS/SOURCES/UjpsCore/release/libujpsCore.a
}


TEMPLATE = app
TARGET = UJPS
CONFIG += c++11
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT += widgets xmlpatterns
DEFINES -= QT_NO_DEBUG


LIBS += ../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

INCLUDEPATH +=  ../STATIC_LIBS/INCLUDES/QtGameControllerModif/ \
				../STATIC_LIBS/INCLUDES/Other/ \
				../STATIC_LIBS/INCLUDES/VirtualJoysticks/ \
				../STATIC_LIBS/INCLUDES/RealJoysticks/ \
				../STATIC_LIBS/INCLUDES/UjpsCore/


HEADERS +=  CODE/HMI/MainWindow.h \
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

