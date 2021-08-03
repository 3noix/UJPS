CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = ujpsCore
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc


win32-g++:LIBS += ../RealJoysticks/$$MODE/librealJoysticks.a
win32-g++:LIBS += ../VirtualJoysticks/$$MODE/libvirtualJoysticks.a
win32-g++:LIBS += ../../../3rdparty/vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

win32-msvc*:LIBS += ../RealJoysticks/$$MODE/realJoysticks.lib
win32-msvc*:LIBS += ../VirtualJoysticks/$$MODE/virtualJoysticks.lib
win32-msvc*:LIBS += ../../../3rdparty/vJoy218SDK-291116/SDK/lib/amd64/vJoyInterface.lib


HEADERS +=  src/AbstractProfile.h \
			src/AbstractProfileTarget.h \
			src/AbstractProfileBasic.h


SOURCES +=  src/AbstractProfile.cpp \
			src/AbstractProfileTarget.cpp \
			src/AbstractProfileBasic.cpp \
			src/VirtualEventsQueue.cpp \
			src/LAYERS/LayersCombo.cpp \
			src/LAYERS/LayerCalculator.cpp \
			src/MAPPINGS/MappingStandard.cpp \
			src/MAPPINGS/MappingTempo.cpp \
			src/MAPPINGS/MappingAxisRelative.cpp \
			src/MAPPINGS/MappingAxis1.cpp \
			src/MAPPINGS/MappingAxis2.cpp \
			src/MAPPINGS/MappingMergeAxes.cpp \
			src/MAPPINGS/MappingSplitAxis.cpp \
			src/MAPPINGS/MappingRexec.cpp

