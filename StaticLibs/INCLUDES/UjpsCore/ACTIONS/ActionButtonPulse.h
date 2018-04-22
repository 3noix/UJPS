#ifndef ACTION_BUTTON_PULSE
#define ACTION_BUTTON_PULSE


#include "AbstractAction.h"
class VirtualJoystick;


class ActionButtonPulse : public AbstractAction
{
	public:
		ActionButtonPulse(VirtualJoystick *vj, uint vButton, uint cycles = 4) :
			AbstractAction{},
			m_vj{vj},
			m_vButton{vButton},
			m_cycles{cycles}
		{};
		ActionButtonPulse(const ActionButtonPulse &other) = delete;
		ActionButtonPulse(ActionButtonPulse &&other) = delete;
		ActionButtonPulse& operator=(const ActionButtonPulse &other) = delete;
		ActionButtonPulse& operator=(ActionButtonPulse &&other) = delete;
		virtual ~ActionButtonPulse() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,true,0.0},{},{},0};
			VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,false,0.0},{},{},m_cycles};
			return {ev1,ev2};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev1{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,true,0.0},{},{},0};
			VirtualEvent ev2{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,false,0.0},{},{},m_cycles};
			return {ev1,ev2};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			// we do nothing, must be triggered again to generate a pulse
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return {};
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
		uint m_cycles;
};

#endif

