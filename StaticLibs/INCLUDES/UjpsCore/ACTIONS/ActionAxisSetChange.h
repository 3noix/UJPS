#ifndef ACTION_AXIS_SET_CHANGE
#define ACTION_AXIS_SET_CHANGE


#include "AbstractAction.h"
#include "AxisDirection.h"
#include "AbstractRealJoystick.h"
class VirtualJoystick;


class ActionAxisSetChange : public AbstractAction
{
	public:
		ActionAxisSetChange(VirtualJoystick *vj, uint vAxis, AxisDirection d) :
			AbstractAction{},
			m_vj{vj},
			m_vAxis{vAxis},
			m_direction{d}
		{};
		ActionAxisSetChange(const ActionAxisSetChange &other) = delete;
		ActionAxisSetChange(ActionAxisSetChange &&other) = delete;
		ActionAxisSetChange& operator=(const ActionAxisSetChange &other) = delete;
		ActionAxisSetChange& operator=(ActionAxisSetChange &&other) = delete;
		virtual ~ActionAxisSetChange() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			return {};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			if (m_direction == AxisDirection::Normal) {return {VirtualEvent{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,ch.axisValue},{},{},0}};}
			else {return {VirtualEvent{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,-ch.axisValue},{},{},0}};}
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			if (t == ControlType::Button) {return {};}
			// we don't wait for a change in the real joystick position to update the virtual joystick position
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,rj->axisValue(rnum)},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final
		{
			// we do nothing, the axis stays at its value
			return {};
		};
		
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final {return {};};
		
		
	private:
		VirtualJoystick *m_vj;
		uint m_vAxis;
		AxisDirection m_direction;
};

#endif

