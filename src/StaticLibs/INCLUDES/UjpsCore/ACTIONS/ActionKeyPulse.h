#ifndef ACTION_KEY_PULSE
#define ACTION_KEY_PULSE


#include "AbstractAction.h"


class ActionKeyPulse : public AbstractAction
{
	public:
		ActionKeyPulse(uint key, uint modifier = 0, uint cycles = 4) :
			AbstractAction{},
			m_key{key},
			m_modifier{modifier},
			m_cycles{cycles}
		{};
		ActionKeyPulse(const ActionKeyPulse &other) = delete;
		ActionKeyPulse(ActionKeyPulse &&other) = delete;
		ActionKeyPulse& operator=(const ActionKeyPulse &other) = delete;
		ActionKeyPulse& operator=(ActionKeyPulse &&other) = delete;
		virtual ~ActionKeyPulse() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev1{EventType::Keyboard,{},KeyboardEvent{true,m_key,m_modifier},{},0};
			VirtualEvent ev2{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},m_cycles};
			return {ev1,ev2};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev1{EventType::Keyboard,{},KeyboardEvent{true,m_key,m_modifier},{},0};
			VirtualEvent ev2{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},m_cycles};
			return {ev1,ev2};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return {};
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final
		{
			// we release the key immediatly
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final
		{
			// we release the key immediatly
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},0};
			return {ev};
		};
		
		
	private:
		uint m_key;
		uint m_modifier;
		uint m_cycles;
};


#endif

