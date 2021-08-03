#ifndef ACTION_POV_SET_CHANGE
#define ACTION_POV_SET_CHANGE


#include "AbstractAction.h"
#include "../../../RealJoysticks/src/AbstractRealJoystick.h"
class VirtualJoystick;


class ActionPovSetChange : public AbstractAction
{
	public:
		ActionPovSetChange(VirtualJoystick *vj, uint vPov) :
			AbstractAction{},
			m_vj{vj},
			m_vPov{vPov}
		{};
		ActionPovSetChange(const ActionPovSetChange &other) = delete;
		ActionPovSetChange(ActionPovSetChange &&other) = delete;
		ActionPovSetChange& operator=(const ActionPovSetChange &other) = delete;
		ActionPovSetChange& operator=(ActionPovSetChange &&other) = delete;
		virtual ~ActionPovSetChange() = default;
		
		virtual std::vector<VirtualEvent> generateEvents() override final
		{
			return {};
		};
		
		virtual std::vector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Pov,m_vPov,false,ch.axisOrPovValue},{},{},0};
			return {ev};
		};
		
		virtual std::vector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			if (t != ControlType::Pov) {return {};}
			// we don't wait for a change in the real joystick position to update the virtual joystick position
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Pov,m_vPov,false,rj->povValue(rnum)},{},{},0};
			return {ev};
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
};


#endif

