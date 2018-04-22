#ifndef ACTION_KEY_PRESS
#define ACTION_KEY_PRESS


#include "AbstractAction.h"


class ActionKeyPress : public AbstractAction
{
	public:
		ActionKeyPress(uint key, uint modifier = 0) :
			AbstractAction{},
			m_key{key},
			m_modifier{modifier}
		{};
		ActionKeyPress(const ActionKeyPress &other) = delete;
		ActionKeyPress(ActionKeyPress &&other) = delete;
		ActionKeyPress& operator=(const ActionKeyPress &other) = delete;
		ActionKeyPress& operator=(ActionKeyPress &&other) = delete;
		virtual ~ActionKeyPress() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{true,m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{true,m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return {};
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final {return {};};
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final {return {};};
		
		
	private:
		uint m_key;
		uint m_modifier;
};

#endif

