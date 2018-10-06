#ifndef MAPPING_SPLIT_AXIS
#define MAPPING_SPLIT_AXIS


#include "AbstractMapping.h"


class MappingSplitAxis : public AbstractMapping
{
	public:
		MappingSplitAxis(AbstractRealJoystick *rj, uint rAxis1,
						LayersCombo lc,
						VirtualJoystick *vj1, uint vAxis1,
						VirtualJoystick *vj2, uint vAxis2,
						VirtualEventsQueue &eventsQueue);
						
		MappingSplitAxis(const MappingSplitAxis &other) = delete;
		MappingSplitAxis(MappingSplitAxis &&other) = delete;
		MappingSplitAxis& operator=(const MappingSplitAxis &other) = delete;
		MappingSplitAxis& operator=(MappingSplitAxis &&other) = delete;
		virtual ~MappingSplitAxis();
		
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
		VirtualJoystick *m_vj1, *m_vj2;
		uint m_rAxis, m_vAxis1, m_vAxis2;
		
		bool m_disable;
};


#endif

