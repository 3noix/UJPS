#ifndef ACTION_AXIS_INCREMENT
#define ACTION_AXIS_INCREMENT


#include "AbstractAction.h"
#include "VirtualJoystick.h"


class ActionAxisIncrement : public AbstractAction
{
	public:
		ActionAxisIncrement(VirtualJoystick *vj, uint vAxis, float increment) :
			AbstractAction{},
			m_vj{vj},
			m_vAxis{vAxis},
			m_increment{increment}
		{};
		ActionAxisIncrement(const ActionAxisIncrement &other) = delete;
		ActionAxisIncrement(ActionAxisIncrement &&other) = delete;
		ActionAxisIncrement& operator=(const ActionAxisIncrement &other) = delete;
		ActionAxisIncrement& operator=(ActionAxisIncrement &&other) = delete;
		virtual ~ActionAxisIncrement() = default;
		
		virtual std::vector<VirtualEvent> generateEvents() override final
		{
			float newValue = m_vj->getAxis(m_vAxis) + m_increment;
			return {VirtualEvent{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,newValue},{},{},0}};
		};
		
		virtual std::vector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			float newValue = m_vj->getAxis(m_vAxis) + m_increment;
			return {VirtualEvent{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,newValue},{},{},0}};
		};
		
		virtual std::vector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return {};
		};
		
		virtual std::vector<VirtualEvent> deactivateByLayerChange() override final {return {};};
		virtual std::vector<VirtualEvent> aboutToBeDeleted() override final {return {};};
		
		
	private:
		VirtualJoystick *m_vj;
		uint m_vAxis;
		float m_increment;
};


#endif

