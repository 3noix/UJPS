#ifndef ACTION_BUTTON_SET_CHANGE
#define ACTION_BUTTON_SET_CHANGE


#include "AbstractAction.h"
class VirtualJoystick;


class ActionButtonSetChange : public AbstractAction
{
	public:
		ActionButtonSetChange(VirtualJoystick *vj, uint vButton) :
			AbstractAction{},
			m_vj{vj},
			m_vButton{vButton}
		{};
		ActionButtonSetChange(const ActionButtonSetChange &other) = delete;
		ActionButtonSetChange(ActionButtonSetChange &&other) = delete;
		ActionButtonSetChange& operator=(const ActionButtonSetChange &other) = delete;
		ActionButtonSetChange& operator=(ActionButtonSetChange &&other) = delete;
		virtual ~ActionButtonSetChange() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			return {};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,ch.bButtonPressed,0.0},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			if (t == ControlType::Axis) {return {};}
			// we don't wait for a change in the real joystick button to update the virtual joystick button
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,rj->buttonPressed(rnum),0.0},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final
		{
			// we release the button immediatly
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,false,0.0},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final
		{
			// we release the button immediatly
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,false,0.0},{},{},0};
			return {ev};
		};
		
		
	private:
		VirtualJoystick *m_vj;
		uint m_vButton;
};

#endif

