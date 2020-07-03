#ifndef ACTION_KEY_SET_CHANGE
#define ACTION_KEY_SET_CHANGE


#include "AbstractAction.h"
#include "AbstractRealJoystick.h"


class ActionKeySetChange : public AbstractAction
{
	public:
		ActionKeySetChange(uint key, uint modifier = 0) :
			AbstractAction{},
			m_key{key},
			m_modifier{modifier}
		{};
		ActionKeySetChange(const ActionKeySetChange &other) = delete;
		ActionKeySetChange(ActionKeySetChange &&other) = delete;
		ActionKeySetChange& operator=(const ActionKeySetChange &other) = delete;
		ActionKeySetChange& operator=(ActionKeySetChange &&other) = delete;
		virtual ~ActionKeySetChange() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			return {};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{ch.bButtonPressed,m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(t)
			// we don't wait for a change in the real joystick button to update the key
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{rj->buttonPressed(rnum),m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final
		{
			// we release the button immediatly
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final
		{
			// we release the button immediatly
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},0};
			return {ev};
		};
		
		
	private:
		uint m_key;
		uint m_modifier;
};


#endif

