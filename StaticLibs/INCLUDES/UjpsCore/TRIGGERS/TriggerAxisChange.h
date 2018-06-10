#ifndef TRIGGER_AXIS_CHANGE
#define TRIGGER_AXIS_CHANGE


#include "AbstractTrigger.h"
#include "AbstractRealJoystick.h"


class TriggerAxisChange : public AbstractTrigger
{
	public:
		TriggerAxisChange() : AbstractTrigger{} {};
		TriggerAxisChange(const TriggerAxisChange &other) = delete;
		TriggerAxisChange(TriggerAxisChange &&other) = delete;
		TriggerAxisChange& operator=(const TriggerAxisChange &other) = delete;
		TriggerAxisChange& operator=(TriggerAxisChange &&other) = delete;
		virtual ~TriggerAxisChange() = default;
		
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
					rnum == ch.numButtonAxisPov);
		};
};

#endif

