#ifndef ABSTRACT_PROFILE
#define ABSTRACT_PROFILE


#include <QObject>
#include <QString>
#include <QColor>
#include <QVector>
#include <QPair>
#include "JoystickChange.h"
#include "MappingModifRequest.h"
#include "LAYERS/LayersCombo.h"
#include "LAYERS/LayerCalculator.h"
#include "VirtualEventsQueue.h"
#include "AxisDirection.h"

class RealJoysticksManager;
class AbstractRealJoystick;
class VirtualJoystick;
class AbstractMapping;
class AbstractTrigger;
class AbstractAction;


class AbstractProfile : public QObject
{
	Q_OBJECT
	
	public:
		AbstractProfile();
		AbstractProfile(const AbstractProfile &other) = delete;
		AbstractProfile(AbstractProfile &&other) = delete;
		AbstractProfile& operator=(const AbstractProfile &other) = delete;
		AbstractProfile& operator=(AbstractProfile &&other) = delete;
		virtual ~AbstractProfile();
		
		// pure virtual functions (called by the window only)
		virtual bool play() = 0;	// executed when clicking "play"
		virtual bool stop() = 0;	// executed when clicking "stop"
		
		void runOneLoop();
		uint ms2cycles(uint msecs) const;
		void setTimeStep(int dtms);				// useful to count the number of cycles for pulses and delays
		void reset();							// call it before calling play a second time
		
		
	signals:
		void message(const QString &str, QColor color);
			
		
	public:
		// mapping functions useful for derived classes
		void Map(AbstractRealJoystick *rj, ControlType type, uint rnum, LayersCombo lc, AbstractTrigger *trig, AbstractAction *act);
		
		void MapButton(AbstractRealJoystick *rj, uint rButton, LayersCombo lc, VirtualJoystick *vj, uint vButton);
		void MapButtonTempo(AbstractRealJoystick *rj, uint rButton, LayersCombo lc, uint cycles, AbstractAction *action1, AbstractAction *action2);
		
		void MapAxis(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj, uint vAxis, AxisDirection d = AxisDirection::Normal);
		void MapAxisRelative(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj, uint vAxis, float timeMinToMax);
		void MapAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, const std::vector<float> &points, AbstractAction *actionPlus, AbstractAction *actionMoins);
		void MapAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, uint nbPoints, AbstractAction *actionPlus, AbstractAction *actionMoins);
		void MapAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, const std::vector<float> &points, const std::vector<AbstractAction*> actions);
		void MapAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, uint nbPoints, const std::vector<AbstractAction*> actions);
		void MapMergeAxes(AbstractRealJoystick *rj1, uint rAxis1, float k1, AbstractRealJoystick *rj2, uint rAxis2, float k2, LayersCombo lc, VirtualJoystick *vj, uint vAxis);
		
		void UnmapAll();
		void UnmapButton(AbstractRealJoystick *rj, uint rButton);
		void UnmapAxis(AbstractRealJoystick *rj, uint rAxis);
		
		void DoAction(AbstractAction *action, bool deleteWhenDone = true);
		
		
	protected:
		void registerRealJoystick(AbstractRealJoystick *rj);
		void registerVirtualJoystick(VirtualJoystick *vj);
		
		void registerLayerDim1(Layers::LayerDim1 layer1, AbstractRealJoystick *rj = nullptr, uint rButton = 0);
		void registerLayerDim2(Layers::LayerDim2 layer2, AbstractRealJoystick *rj = nullptr, uint rButton = 0);
		
		
	private:
		void addMapping(AbstractMapping *m);
		
		// the following 3 are used to manage mapping modifications requests while they are being processed
		void processPendingMappingsRequests();
		QVector<MappingModifRequest> m_mappingsRequests;
		bool m_isProcessingEvents;
		
		int m_dtms;
		
		LayerCalculator m_layerCalculator;
		QVector<JoystickChange> m_changes;
		QVector<AbstractMapping*> m_mappings;
		std::vector<AbstractRealJoystick*> m_realJoysticks;
		std::vector<VirtualJoystick*> m_virtualJoysticks;
		VirtualEventsQueue m_eventsQueue;
};


Q_DECLARE_INTERFACE(AbstractProfile,"AbstractProfile")


#endif

