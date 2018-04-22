#ifndef TRIGGER_BUTTON_CHANGE
#define TRIGGER_BUTTON_CHANGE


#include "AbstractTrigger.h"
#include "AbstractRealJoystick.h"


class TriggerButtonChange : public AbstractTrigger
{
	public:
		TriggerButtonChange() : AbstractTrigger{} {};
		TriggerButtonChange(const TriggerButtonChange &other) = delete;
		TriggerButtonChange(TriggerButtonChange &&other) = delete;
		TriggerButtonChange& operator=(const TriggerButtonChange &other) = delete;
		TriggerButtonChange& operator=(TriggerButtonChange &&other) = delete;
		virtual ~TriggerButtonChange() = default;
		
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
					t == ControlType::Button &&
					ch.type == ControlType::Button &&
					rnum == ch.numButtonOrAxis);
		};
};

#endif

