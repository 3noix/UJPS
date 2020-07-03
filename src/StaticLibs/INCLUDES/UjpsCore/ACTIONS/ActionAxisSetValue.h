#ifndef ACTION_AXIS_SET_VALUE
#define ACTION_AXIS_SET_VALUE


#include "AbstractAction.h"
#include "AxisDirection.h"
#include "AbstractRealJoystick.h"
class VirtualJoystick;


class ActionAxisSetValue : public AbstractAction
{
	public:
		ActionAxisSetValue(VirtualJoystick *vj, uint vAxis, float value) :
			AbstractAction{},
			m_vj{vj},
			m_vAxis{vAxis},
			m_value{value}
		{};
		ActionAxisSetValue(const ActionAxisSetValue &other) = delete;
		ActionAxisSetValue(ActionAxisSetValue &&other) = delete;
		ActionAxisSetValue& operator=(const ActionAxisSetValue &other) = delete;
		ActionAxisSetValue& operator=(ActionAxisSetValue &&other) = delete;
		virtual ~ActionAxisSetValue() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,m_value},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			VirtualEvent ev{EventType::VJoy,VJoyEvent{m_vj,ControlType::Axis,m_vAxis,false,m_value},{},{},0};
			return {ev};
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			// we do nothing, it would really be to invasive
			return {};
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
		float m_value;
};


#endif

