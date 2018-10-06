#ifndef ABSTRACT_MAPPING
#define ABSTRACT_MAPPING


#include "JoystickChange.h"
#include "../LAYERS/LayersCombo.h"
#include "../VirtualEventsQueue.h"
class AbstractRealJoystick;


class AbstractMapping
{
	public:
		AbstractMapping(LayersCombo lc, VirtualEventsQueue &eventsQueue) :
			m_layersCombo{lc},
			m_layerOk{false},
			m_eventsQueue{eventsQueue}
		{};
		AbstractMapping(const AbstractMapping &other) = delete;
		AbstractMapping(AbstractMapping &&other) = delete;
		AbstractMapping& operator=(const AbstractMapping &other) = delete;
		AbstractMapping& operator=(AbstractMapping &&other) = delete;
		virtual ~AbstractMapping() = default;
		
		virtual bool reactsToChanges() const = 0;
		virtual bool reactsToStates() const = 0;
		virtual bool isTriggered() = 0;
		virtual bool isTriggered(const JoystickChange &ch) = 0;
		virtual bool isMappingButton(AbstractRealJoystick *rj, uint rButton) const = 0;
		virtual bool isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const = 0;
		virtual bool isMappingPov(AbstractRealJoystick *rj, uint rPov) const = 0;
		virtual bool isMappingRexec(uint id) const = 0;
		virtual void performAction() = 0;
		virtual void performAction(const JoystickChange &ch) = 0;
		
		virtual void activateByLayerChange() = 0;
		virtual void deactivateByLayerChange() = 0;
		virtual void aboutToBeDeleted() = 0;
		
		void setLayer(Layer la)
		{
			bool bLayerSupported = this->isActiveInLayer(la);
			if (bLayerSupported && !m_layerOk)
			{
				m_layerOk = true;
				this->activateByLayerChange();
			}
			else if (!bLayerSupported && m_layerOk)
			{
				m_layerOk = false;
				this->deactivateByLayerChange();
			}
		};
		
		bool isActiveInLayer(Layer la) {return m_layersCombo.contains(la);};
		
		
	protected:
		void postEvent(VirtualEvent event) {m_eventsQueue.postEvent(event);};
		void postEvents(const QVector<VirtualEvent> &events) {m_eventsQueue.postEvents(events);};
		
		
	private:
		LayersCombo m_layersCombo;
		bool m_layerOk;
		VirtualEventsQueue &m_eventsQueue;
};


#endif

