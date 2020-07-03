#ifndef MAPPING_REXEC
#define MAPPING_REXEC


#include "AbstractMapping.h"
class AbstractAction;


class MappingRexec : public AbstractMapping
{
	public:
		MappingRexec(uint id, uint cycles, AbstractAction *action, VirtualEventsQueue &eventsQueue);
		MappingRexec(const MappingRexec &other) = delete;
		MappingRexec(MappingRexec &&other) = delete;
		MappingRexec& operator=(const MappingRexec &other) = delete;
		MappingRexec& operator=(MappingRexec &&other) = delete;
		virtual ~MappingRexec();
		
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
		uint m_id;
		uint m_cycles;
		uint m_compteur;
		AbstractAction *m_action;
		bool m_disable;
};


#endif

