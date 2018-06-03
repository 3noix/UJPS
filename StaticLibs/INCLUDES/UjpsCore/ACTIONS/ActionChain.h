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
		ActionChain(const ActionChain &other) = delete;
		ActionChain(ActionChain &&other) = delete;
		ActionChain& operator=(const ActionChain &other) = delete;
		ActionChain& operator=(ActionChain &&other) = delete;
		virtual ~ActionChain() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			m_delay = 0;
			QVector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				if (action->additionalDelay() > 0) {m_delay += action->additionalDelay();}
				
				QVector<VirtualEvent> eventsTemp = action->generateEvents();
				for (VirtualEvent &event : eventsTemp) {event.delay += m_delay;}
				events << eventsTemp;
			}
			return events;
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			m_delay = 0;
			QVector<VirtualEvent> events;
			for (AbstractAction *action : m_actions)
			{
				if (action->additionalDelay() > 0) {m_delay += action->additionalDelay();}
				
				QVector<VirtualEvent> eventsTemp = action->generateEvents(ch);
				for (VirtualEvent &event : eventsTemp) {event.delay += m_delay;}
				events << eventsTemp;
			}
			return events;
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			QVector<VirtualEvent> events;
			for (AbstractAction *action : m_actions) {events << action->activateByLayerChange(rj,t,rnum);}
			return events;
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final
		{
			QVector<VirtualEvent> events;
			for (AbstractAction *action : m_actions) {events << action->deactivateByLayerChange();}
			return events;
		};
		
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final
		{
			QVector<VirtualEvent> events;
			for (AbstractAction *action : m_actions) {events << action->deactivateByLayerChange();}
			return events;
		};
		
		
	private:
		std::vector<AbstractAction*> m_actions;
		uint m_delay;
};

#endif

