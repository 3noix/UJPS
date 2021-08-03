#ifndef ACTION_BUTTON_RELEASE
#define ACTION_BUTTON_RELEASE


#include "AbstractAction.h"
class VirtualJoystick;


class ActionButtonRelease : public AbstractAction
{
	public:
		ActionButtonRelease(VirtualJoystick *vj, uint vButton) :
			AbstractAction{},
			m_vj{vj},
			m_vButton{vButton}
		{};
		ActionButtonRelease(const ActionButtonRelease &other) = delete;
		ActionButtonRelease(ActionButtonRelease &&other) = delete;
		ActionButtonRelease& operator=(const ActionButtonRelease &other) = delete;
		ActionButtonRelease& operator=(ActionButtonRelease &&other) = delete;
		virtual ~ActionButtonRelease() = default;
		
		virtual std::vector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,false,0.0},{},{},0};
			return {ev};
		};
		
		virtual std::vector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,false,0.0},{},{},0};
			return {ev};
		};
		
		virtual std::vector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return {};
		};
		virtual std::vector<VirtualEvent> deactivateByLayerChange() override final {return {};};
		virtual std::vector<VirtualEvent> aboutToBeDeleted() override final {return {};};
		
		
	private:
		VirtualJoystick *m_vj;
		uint m_vButton;
};


#endif

