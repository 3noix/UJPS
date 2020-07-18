#ifndef ACTION_SEQUENCE
#define ACTION_SEQUENCE


#include "AbstractAction.h"
#include <vector>


class ActionSequence : public AbstractAction
{
	public:
		ActionSequence(std::vector<AbstractAction*> actions) :
			AbstractAction{},
			m_actions{actions},
			m_compteur{0}
		{};
		ActionSequence(std::initializer_list<AbstractAction*> actions) :
			AbstractAction{},
			m_actions{actions},
			m_compteur{0}
		{};
		ActionSequence(const ActionSequence &other) = delete;
		ActionSequence(ActionSequence &&other) = delete;
		ActionSequence& operator=(const ActionSequence &other) = delete;
		ActionSequence& operator=(ActionSequence &&other) = delete;
		virtual ~ActionSequence() {qDeleteAll(m_actions);};
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			QVector<VirtualEvent> events = m_actions[m_compteur]->generateEvents();
			++m_compteur;
			m_compteur %= m_actions.size();
			return events;
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			QVector<VirtualEvent> events = m_actions[m_compteur]->generateEvents(ch);
			++m_compteur;
			m_compteur %= m_actions.size();
			return events;
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
		uint m_compteur;
};


#endif

