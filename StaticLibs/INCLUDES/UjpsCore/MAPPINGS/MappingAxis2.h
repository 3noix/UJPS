#ifndef MAPPING_AXIS_2
#define MAPPING_AXIS_2


#include "AbstractMapping.h"
#include <vector>
class AbstractAction;


class MappingAxis2 : public AbstractMapping
{
	public:
		MappingAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc,
						const std::vector<float> &points,
						const std::vector<AbstractAction*> &actions,
						VirtualEventsQueue &eventsQueue);
		MappingAxis2(const MappingAxis2 &other) = delete;
		MappingAxis2(MappingAxis2 &&other) = delete;
		MappingAxis2& operator=(const MappingAxis2 &other) = delete;
		MappingAxis2& operator=(MappingAxis2 &&other) = delete;
		virtual ~MappingAxis2();
		
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
		uint computeZone(float axisValue);
		
		AbstractRealJoystick *m_rj;
		uint m_rAxis;
		std::vector<float> m_points;
		std::vector<AbstractAction*> m_actions;
		
		bool m_disable;
		uint m_previousZone;
		uint m_newZone;
};

#endif

