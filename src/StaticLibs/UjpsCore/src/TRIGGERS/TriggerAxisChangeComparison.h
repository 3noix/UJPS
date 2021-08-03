#ifndef TRIGGER_AXIS_CHANGE_COMPARISON
#define TRIGGER_AXIS_CHANGE_COMPARISON


#include "AbstractTrigger.h"
#include "../../../RealJoysticks/src/AbstractRealJoystick.h"


class TriggerAxisChangeComparison : public AbstractTrigger
{
	public:
		TriggerAxisChangeComparison(bool bgt, float thr) : AbstractTrigger{}, m_bgt{bgt}, m_thr{thr} {};
		TriggerAxisChangeComparison(const TriggerAxisChangeComparison &other) = delete;
		TriggerAxisChangeComparison(TriggerAxisChangeComparison &&other) = delete;
		TriggerAxisChangeComparison& operator=(const TriggerAxisChangeComparison &other) = delete;
		TriggerAxisChangeComparison& operator=(TriggerAxisChangeComparison &&other) = delete;
		virtual ~TriggerAxisChangeComparison() = default;
		
		virtual bool reactsToChanges() const override final {return true;};
		virtual bool reactsToStates() const override final {return false;};
		
		virtual bool isTriggered(AbstractRealJoystick *rj, ControlType t, uint rnum) const override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return false;
		};
		
		virtual bool isTriggered(AbstractRealJoystick *rj, ControlType t, uint rnum, const JoystickChange &ch) const override final
		{
			return (rj != nullptr && ch.joystick != nullptr &&
					rj->id() == ch.joystick->id() &&
					t == ControlType::Axis &&
					ch.type == ControlType::Axis &&
					rnum == ch.numButtonAxisPov &&
					((m_bgt && rj->axisValue(rnum) > m_thr) || (!m_bgt && rj->axisValue(rnum) < m_thr)));
		};
		
		
	private:
		bool m_bgt;
		float m_thr;
};


#endif

