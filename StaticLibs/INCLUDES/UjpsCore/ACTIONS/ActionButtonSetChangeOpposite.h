#ifndef ACTION_BUTTON_SET_CHANGE_OPPOSITE
#define ACTION_BUTTON_SET_CHANGE_OPPOSITE


#include "AbstractAction.h"
#include "AbstractRealJoystick.h"
class VirtualJoystick;


class ActionButtonSetChangeOpposite : public AbstractAction
{
	public:
		ActionButtonSetChangeOpposite(VirtualJoystick *vj, uint vButton) :
			AbstractAction{},
			m_vj{vj},
			m_vButton{vButton}
		{};
		ActionButtonSetChangeOpposite(const ActionButtonSetChangeOpposite &other) = delete;
		ActionButtonSetChangeOpposite(ActionButtonSetChangeOpposite &&other) = delete;
		ActionButtonSetChangeOpposite& operator=(const ActionButtonSetChangeOpposite &other) = delete;
		ActionButtonSetChangeOpposite& operator=(ActionButtonSetChangeOpposite &&other) = delete;
		virtual ~ActionButtonSetChangeOpposite() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			return {};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,!ch.bButtonPressed,0.0},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			if (t != ControlType::Button) {return {};}
			// we don't wait for a change in the real joystick button to update the virtual joystick button
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,!rj->buttonPressed(rnum),0.0},{},{},0};
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
		}
		
		
	private:
		VirtualJoystick *m_vj;
		uint m_vButton;
};

#endif

