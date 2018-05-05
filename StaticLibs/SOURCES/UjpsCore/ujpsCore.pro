CONFIG(debug, debug|release) {
	DESTDIR = debug
	LIBS += ../VirtualJoysticks/debug/libvirtualJoysticks.a
}
CONFIG(release, debug|release) {
	DESTDIR = release
	LIBS += ../VirtualJoysticks/release/libvirtualJoysticks.a
}


TEMPLATE = lib
TARGET = ujpsCore
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
CONFIG += c++11

LIBS += ../../../vJoy218SDK-291116/SDK/lib/vJoyInterface.lib

INCLUDEPATH +=  ../../INCLUDES/Other/ \
				../../INCLUDES/VirtualJoysticks/ \
				../../INCLUDES/RealJoysticks/ \
				../../INCLUDES/UjpsCore/

HEADERS +=  ../../INCLUDES/UjpsCore/AbstractProfile.h \
			../../INCLUDES/UjpsCore/VirtualEventsQueue.h \
			../../INCLUDES/UjpsCore/LAYERS/LayersCombo.h \
			../../INCLUDES/UjpsCore/LAYERS/LayerCalculator.h \
			../../INCLUDES/UjpsCore/MAPPINGS/AbstractMapping.h \
			../../INCLUDES/UjpsCore/MAPPINGS/MappingStandard.h \
			../../INCLUDES/UjpsCore/MAPPINGS/MappingTempo.h \
			../../INCLUDES/UjpsCore/MAPPINGS/MappingAxisRelative.h \
			../../INCLUDES/UjpsCore/MAPPINGS/MappingAxis1.h \
			../../INCLUDES/UjpsCore/MAPPINGS/MappingAxis2.h


SOURCES +=  CODE/AbstractProfile.cpp \
			CODE/VirtualEventsQueue.cpp \
			CODE/LAYERS/LayersCombo.cpp \
			CODE/LAYERS/LayerCalculator.cpp \
			CODE/MAPPINGS/MappingStandard.cpp \
			CODE/MAPPINGS/MappingTempo.cpp \
			CODE/MAPPINGS/MappingAxisRelative.cpp \
			CODE/MAPPINGS/MappingAxis1.cpp \
			CODE/MAPPINGS/MappingAxis2.cpp \
			CODE/MAPPINGS/MappingMergeAxes.cpp

