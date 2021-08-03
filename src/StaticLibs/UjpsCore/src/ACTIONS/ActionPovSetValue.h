#ifndef ACTION_POV_SET_VALUE
#define ACTION_POV_SET_VALUE


#include "AbstractAction.h"
#include "../../../RealJoysticks/src/AbstractRealJoystick.h"
class VirtualJoystick;


class ActionPovSetValue : public AbstractAction
{
	public:
		ActionPovSetValue(VirtualJoystick *vj, uint vPov, float value) :
			AbstractAction{},
			m_vj{vj},
			m_vPov{vPov},
			m_value{value}
		{};
		ActionPovSetValue(const ActionPovSetValue &other) = delete;
		ActionPovSetValue(ActionPovSetValue &&other) = delete;
		ActionPovSetValue& operator=(const ActionPovSetValue &other) = delete;
		ActionPovSetValue& operator=(ActionPovSetValue &&other) = delete;
		virtual ~ActionPovSetValue() = default;
		
		virtual std::vector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Pov,m_vPov,false,m_value},{},{},0};
			return {ev};
		};
		
		virtual std::vector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Pov,m_vPov,false,m_value},{},{},0};
			return {ev};
		};
		
		virtual std::vector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			// we do nothing, it would really be to invasive
			return {};
		};
		
		virtual std::vector<VirtualEvent> deactivateByLayerChange() override final
		{
			// we do nothing, the pov stays at its value
			return {};
		};
		
		virtual std::vector<VirtualEvent> aboutToBeDeleted() override final {return {};};
		
		
	private:
		VirtualJoystick *m_vj;
		uint m_vPov;
		float m_value;
};


#endif

