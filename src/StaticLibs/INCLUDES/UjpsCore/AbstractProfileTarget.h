#ifndef ABSTRACT_PROFILE_TARGET
#define ABSTRACT_PROFILE_TARGET


#include "AbstractProfile.h"
#include <QVector>
#include <QMap>
#include "JoystickChange.h"
#include "../../SOURCES/UjpsCore/CODE/MappingModifRequest.h"
#include "../../SOURCES/UjpsCore/CODE/LAYERS/LayerCalculator.h"
#include "LAYERS/LayersCombo.h"
#include "VirtualEventsQueue.h"
#include "AxisDirection.h"

class AbstractRealJoystick;
class EnhancedJoystick;
class RemoteJoystickTcpServer;
class RemoteJoystickHttp;
class VirtualJoystick;
class AbstractMapping;
class AbstractTrigger;
class AbstractAction;
class AbstractAxisCurve;


class AbstractProfileTarget : public AbstractProfile
{
	Q_OBJECT
	
	public:
		AbstractProfileTarget();
		AbstractProfileTarget(const AbstractProfileTarget &other) = delete;
		AbstractProfileTarget(AbstractProfileTarget &&other) = delete;
		AbstractProfileTarget& operator=(const AbstractProfileTarget &other) = delete;
		AbstractProfileTarget& operator=(AbstractProfileTarget &&other) = delete;
		virtual ~AbstractProfileTarget();
		
		// public functions (called by the window only)
		virtual bool play() override;					// executed when clicking "play"
		virtual void run() override;					// executed at each time step
		virtual void stop() override;					// executed when clicking "stop"
		virtual bool isInitComplete() const override;	// to check if remote joysticks are all connected
			
		
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
		void MapMergeAxes(AbstractRealJoystick *rj1, uint rAxis1, float k1, AbstractRealJoystick *rj2, uint rAxis2, float k2, LayersCombo lc, VirtualJoystick *vj, uint vAxis, AbstractAxisCurve *curve = nullptr);
		void MapSplitAxis(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj1, uint vAxis1, VirtualJoystick *vj2, uint vAxis2);
		
		void MapPov(AbstractRealJoystick *rj, uint rPov, LayersCombo lc, VirtualJoystick *vj, uint vPov);
		
		void UnmapAll();
		void UnmapButton(AbstractRealJoystick *rj, uint rButton);
		void UnmapAxis(AbstractRealJoystick *rj, uint rAxis);
		void UnmapPov(AbstractRealJoystick *rj, uint rPov);
		
		void DoAction(AbstractAction *action, bool deleteWhenDone = true);
		bool startRexec(uint id, uint cycles, AbstractAction *action);
		bool startRexec(uint id, uint cycles, std::function<void()> fct);
		bool stopRexec(uint id);
		
		
	protected:
		EnhancedJoystick* registerRealJoystick(const QString &description, int num = 0);
		EnhancedJoystick* registerRemoteJoystickTcp(RemoteJoystickTcpServer *rjs);
		EnhancedJoystick* registerRemoteJoystickHttp(const QString &name, uint id, const QString &dirPath);
		VirtualJoystick* registerVirtualJoystick(uint id);
		
		void registerLayerDim1(Layers::LayerDim1 layer1, AbstractRealJoystick *rj = nullptr, uint rButton = 0);
		void registerLayerDim2(Layers::LayerDim2 layer2, AbstractRealJoystick *rj = nullptr, uint rButton = 0);
		
		
	private slots:
		void slotRemoteJoystickTcpConnected();
		
		
	private:
		// private pure virtual functions
		virtual bool setupJoysticks() = 0;	// called by "play" function
		virtual void runFirstStep() = 0;	// executed at the first run (called by "run")
		
		void addMapping(AbstractMapping *m);
		void UnmapRexec(uint id);
		
		// the following 3 are used to manage mapping modifications requests while they are being processed
		void processPendingMappingsRequests();
		QVector<MappingModifRequest> m_mappingsRequests;
		bool m_isProcessingEvents;
		
		bool m_bFirstStep;
		
		LayerCalculator m_layerCalculator;
		QVector<JoystickChange> m_changes;
		QVector<AbstractMapping*> m_mappings;
		std::vector<AbstractRealJoystick*> m_realJoysticks;
		std::vector<RemoteJoystickTcpServer*> m_remoteJoysticksTcp;
		std::vector<VirtualJoystick*> m_virtualJoysticks;
		VirtualEventsQueue m_eventsQueue;
		
		// for rexec
		QVector<uint> m_rexecIds;
		QMap<uint,AbstractAction*> m_rexecFunctionsActionsToDelete;
};


#endif

