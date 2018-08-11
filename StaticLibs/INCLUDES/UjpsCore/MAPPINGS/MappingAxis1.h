#ifndef MAPPING_AXIS_1
#define MAPPING_AXIS_1


#include "AbstractMapping.h"
#include <vector>
class AbstractAction;


class MappingAxis1 : public AbstractMapping
{
	public:
		MappingAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc,
						const std::vector<float> &points,
						AbstractAction *actionPlus,
						AbstractAction *actionMoins,
						VirtualEventsQueue &eventsQueue);
		MappingAxis1(const MappingAxis1 &other) = delete;
		MappingAxis1(MappingAxis1 &&other) = delete;
		MappingAxis1& operator=(const MappingAxis1 &other) = delete;
		MappingAxis1& operator=(MappingAxis1 &&other) = delete;
		virtual ~MappingAxis1();
		
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
		AbstractAction *m_actionPlus;
		AbstractAction *m_actionMoins;
		
		bool m_disable;
		uint m_previousZone;
		bool m_useActionPlus;
};

#endif

