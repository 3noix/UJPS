CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ujpsCore
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


win32-g++:LIBS += ../RealJoysticks/$$MODE/librealJoysticks.a
win32-g++:LIBS += ../VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += ../../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += ../RealJoysticks/$$MODE/realJoysticks.lib
win32-msvc*:LIBS += ../VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += ../../../vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


INCLUDEPATH +=  ../../INCLUDES/Other/ \
				../../INCLUDES/VirtualJoysticks/ \
				../../INCLUDES/RealJoysticks/ \
				../../INCLUDES/UjpsCore/


HEADERS +=  ../../INCLUDES/UjpsCore/AbstractProfile.h \
			../../INCLUDES/UjpsCore/AbstractProfileTarget.h


SOURCES +=  CODE/AbstractProfile.cpp \
			CODE/AbstractProfileTarget.cpp \
			CODE/VirtualEventsQueue.cpp \
			CODE/LAYERS/LayersCombo.cpp \
			CODE/LAYERS/LayerCalculator.cpp \
			CODE/MAPPINGS/MappingStandard.cpp \
			CODE/MAPPINGS/MappingTempo.cpp \
			CODE/MAPPINGS/MappingAxisRelative.cpp \
			CODE/MAPPINGS/MappingAxis1.cpp \
			CODE/MAPPINGS/MappingAxis2.cpp \
			CODE/MAPPINGS/MappingMergeAxes.cpp \
			CODE/MAPPINGS/MappingSplitAxis.cpp \
			CODE/MAPPINGS/MappingRexec.cpp

