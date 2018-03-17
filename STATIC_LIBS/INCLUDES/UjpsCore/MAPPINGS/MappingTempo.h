#ifndef MAPPING_TEMPO
#define MAPPING_TEMPO


#include "AbstractMapping.h"
class AbstractAction;


class MappingTempo : public AbstractMapping
{
	public:
		MappingTempo(AbstractRealJoystick *rj, uint rButton, LayersCombo lc,
						uint cycles,
						AbstractAction *action1,
						AbstractAction *action2,
						VirtualEventsQueue &eventsQueue);
		MappingTempo(const MappingTempo &other) = delete;
		MappingTempo(MappingTempo &&other) = delete;
		MappingTempo& operator=(const MappingTempo &other) = delete;
		MappingTempo& operator=(MappingTempo &&other) = delete;
		virtual ~MappingTempo();
		
		virtual bool reactsToChanges() const override final;
		virtual bool reactsToStates() const override final;
		virtual bool isTriggered() override final;
		virtual bool isTriggered(const JoystickChange &ch) override final;
		virtual bool isMappingButton(AbstractRealJoystick *rj, uint rButton) const override final;
		virtual bool isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const override final;
		virtual void performAction() override final;
		virtual void performAction(const JoystickChange &ch) override final;
		
		virtual void activateByLayerChange() override final;
		virtual void deactivateByLayerChange()  override final;
		virtual void aboutToBeDeleted() override final;
		
		
	private:
		AbstractRealJoystick *m_rj;
		uint m_rButton;
		uint m_cycles;
		AbstractAction *m_action1;
		AbstractAction *m_action2;
		
		bool m_disable;
		bool m_isRunning;
		uint m_compteur;
		bool m_useAction1;
};

#endif

