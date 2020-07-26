#ifndef ACTION_CHAIN
#define ACTION_CHAIN


#include "AbstractAction.h"
#include <vector>


class ActionChain : public AbstractAction
{
	public:
		ActionChain(std::vector<AbstractAction*> actions) :
			AbstractAction{},
			m_actions{actions},
			m_delay{0}
		{};
		ActionChain(std::initializer_list<AbstractAction*> actions) :
			AbstractAction{},
			m_actions{actions},
			m_delay{0}
		{};
		ActionChain(const ActionChain &other) = delete;
		ActionChain(ActionChain &&other) = delete;
		ActionChain& operator=(const ActionChain &other) = delete;
		ActionChain& operator=(ActionChain &&other) = delete;
		virtual ~ActionChain() {qDeleteAll(m_actions);};
		
		virtual std::vector<VirtualEvent> generateEvents() override final
		{
			m_delay = 0;
			std::vector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				if (action->additionalDelay() > 0) {m_delay += action->additionalDelay();}
				
				std::vector<VirtualEvent> eventsTemp = action->generateEvents();
				for (VirtualEvent event : eventsTemp)
				{
					event.delay += m_delay;
					events.push_back(event);
				}
			}
			return events;
		};
		
		virtual std::vector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			m_delay = 0;
			std::vector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				if (action->additionalDelay() > 0) {m_delay += action->additionalDelay();}
				
				std::vector<VirtualEvent> eventsTemp = action->generateEvents(ch);
				for (VirtualEvent event : eventsTemp)
				{
					event.delay += m_delay;
					events.push_back(event);
				}
			}
			return events;
		};
		
		virtual std::vector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			std::vector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				for (const VirtualEvent &event : action->activateByLayerChange(rj,t,rnum))
					events.push_back(event);
			}
			return events;
		};
		
		virtual std::vector<VirtualEvent> deactivateByLayerChange() override final
		{
			std::vector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				for (const VirtualEvent &event : action->deactivateByLayerChange())
					events.push_back(event);
			}
			return events;
		};
		
		virtual std::vector<VirtualEvent> aboutToBeDeleted() override final
		{
			std::vector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				for (const VirtualEvent &event : action->aboutToBeDeleted())
					events.push_back(event);
			}
			return events;
		};
		
		
	private:
		std::vector<AbstractAction*> m_actions;
		uint m_delay;
};


#endif

