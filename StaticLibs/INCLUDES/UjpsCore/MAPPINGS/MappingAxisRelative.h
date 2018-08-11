#ifndef MAPPING_AXIS_RELATIVE
#define MAPPING_AXIS_RELATIVE


#include "AbstractMapping.h"
class VirtualJoystick;


class MappingAxisRelative : public AbstractMapping
{
	public:
		MappingAxisRelative(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc,
						VirtualJoystick *vj, uint vAxis, float timeMinToMax,
						VirtualEventsQueue &eventsQueue);
						
		MappingAxisRelative(const MappingAxisRelative &other) = delete;
		MappingAxisRelative(MappingAxisRelative &&other) = delete;
		MappingAxisRelative& operator=(const MappingAxisRelative &other) = delete;
		MappingAxisRelative& operator=(MappingAxisRelative &&other) = delete;
		virtual ~MappingAxisRelative();
		
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
		uint m_rAxis;
		VirtualJoystick *m_vj;
		uint m_vAxis;
		float m_factor;
		
		bool m_disable;
};

#endif

