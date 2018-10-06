#ifndef TRIGGER_POV_CHANGE
#define TRIGGER_POV_CHANGE


#include "AbstractTrigger.h"
#include "AbstractRealJoystick.h"


class TriggerPovChange : public AbstractTrigger
{
	public:
		TriggerPovChange() : AbstractTrigger{} {};
		TriggerPovChange(const TriggerPovChange &other) = delete;
		TriggerPovChange(TriggerPovChange &&other) = delete;
		TriggerPovChange& operator=(const TriggerPovChange &other) = delete;
		TriggerPovChange& operator=(TriggerPovChange &&other) = delete;
		virtual ~TriggerPovChange() = default;
		
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
					t == ControlType::Pov &&
					ch.type == ControlType::Pov &&
					rnum == ch.numButtonAxisPov);
		};
};


#endif

