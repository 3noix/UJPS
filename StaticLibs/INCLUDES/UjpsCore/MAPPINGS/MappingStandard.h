#ifndef MAPPING_STANDARD
#define MAPPING_STANDARD


#include "AbstractMapping.h"
class AbstractTrigger;
class AbstractAction;


class MappingStandard : public AbstractMapping
{
	public:
		MappingStandard(AbstractRealJoystick *rj, ControlType t, uint rnum, LayersCombo lc,
						AbstractTrigger *trigger,
						AbstractAction *action,
						VirtualEventsQueue &eventsQueue);
						
		MappingStandard(const MappingStandard &other) = delete;
		MappingStandard(MappingStandard &&other) = delete;
		MappingStandard& operator=(const MappingStandard &other) = delete;
		MappingStandard& operator=(MappingStandard &&other) = delete;
		virtual ~MappingStandard();
		
		virtual bool reactsToChanges() const override final;
		virtual bool reactsToStates() const override final;
		virtual bool isTriggered() override final;
		virtual bool isTriggered(const JoystickChange &ch) override final;
		virtual bool isMappingButton(AbstractRealJoystick *rj, uint rButton) const override final;
		virtual bool isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const override final;
		virtual bool isMappingPov(AbstractRealJoystick *rj, uint rPov) const override final;
		virtual bool isMappingRexec(uint id) const override final;
		virtual void performAction() override final;
		virtual void performAction(const JoystickChange &ch) override final;
		
		virtual void activateByLayerChange() override final;
		virtual void deactivateByLayerChange()  override final;
		virtual void aboutToBeDeleted() override final;
		
		
	private:
		AbstractRealJoystick *m_rj;
		ControlType m_type;
		uint m_rnum;
		
		bool m_disable;
		AbstractTrigger *m_trigger;
		AbstractAction *m_action;
};

#endif

