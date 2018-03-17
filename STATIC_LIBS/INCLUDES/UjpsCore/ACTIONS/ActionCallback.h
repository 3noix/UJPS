#ifndef ACTION_CALLBACK
#define ACTION_CALLBACK


#include "AbstractAction.h"
#include <functional>


class ActionCallback : public AbstractAction
{
	public:
		ActionCallback(std::function<void()> f) :
			AbstractAction{},
			m_function{f}
		{};
		ActionCallback(const ActionCallback &other) = delete;
		ActionCallback(ActionCallback &&other) = delete;
		ActionCallback& operator=(const ActionCallback &other) = delete;
		ActionCallback& operator=(ActionCallback &&other) = delete;
		virtual ~ActionCallback() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::Callback,{},{},m_function,0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::Callback,{},{},m_function,0};
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
		std::function<void()> m_function;
};

#endif

