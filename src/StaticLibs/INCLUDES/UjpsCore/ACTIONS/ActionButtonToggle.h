#ifndef ACTION_BUTTON_TOGGLE
#define ACTION_BUTTON_TOGGLE


#include "AbstractAction.h"
#include "VirtualJoystick.h"


class ActionButtonToggle : public AbstractAction
{
	public:
		ActionButtonToggle(VirtualJoystick *vj, uint vButton) :
			AbstractAction{},
			m_vj{vj},
			m_vButton{vButton}
		{};
		ActionButtonToggle(const ActionButtonToggle &other) = delete;
		ActionButtonToggle(ActionButtonToggle &&other) = delete;
		ActionButtonToggle& operator=(const ActionButtonToggle &other) = delete;
		ActionButtonToggle& operator=(ActionButtonToggle &&other) = delete;
		virtual ~ActionButtonToggle() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,!m_vj->getButton(m_vButton),0.0},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,!m_vj->getButton(m_vButton),0.0},{},{},0};
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
		VirtualJoystick *m_vj;
		uint m_vButton;
};


#endif

