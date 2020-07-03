#ifndef ACTION_BUTTON_PRESS
#define ACTION_BUTTON_PRESS


#include "AbstractAction.h"
class VirtualJoystick;


class ActionButtonPress : public AbstractAction
{
	public:
		ActionButtonPress(VirtualJoystick *vj, uint vButton) :
			AbstractAction{},
			m_vj{vj},
			m_vButton{vButton}
		{};
		ActionButtonPress(const ActionButtonPress &other) = delete;
		ActionButtonPress(ActionButtonPress &&other) = delete;
		ActionButtonPress& operator=(const ActionButtonPress &other) = delete;
		ActionButtonPress& operator=(ActionButtonPress &&other) = delete;
		virtual ~ActionButtonPress() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,true,0.0},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Button,m_vButton,true,0.0},{},{},0};
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

