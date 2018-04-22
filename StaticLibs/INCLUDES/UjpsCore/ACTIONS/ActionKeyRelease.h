#ifndef ACTION_KEY_RELEASE
#define ACTION_KEY_RELEASE


#include "AbstractAction.h"


class ActionKeyRelease : public AbstractAction
{
	public:
		ActionKeyRelease(uint key, uint modifier = 0) :
			AbstractAction{},
			m_key{key},
			m_modifier{modifier}
		{};
		ActionKeyRelease(const ActionKeyRelease &other) = delete;
		ActionKeyRelease(ActionKeyRelease &&other) = delete;
		ActionKeyRelease& operator=(const ActionKeyRelease &other) = delete;
		ActionKeyRelease& operator=(ActionKeyRelease &&other) = delete;
		virtual ~ActionKeyRelease() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::Keyboard,{},KeyboardEvent{false,m_key,m_modifier},{},0};
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

