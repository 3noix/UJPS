#ifndef TRIGGER_BUTTON_PRESS
#define TRIGGER_BUTTON_PRESS


#include "AbstractTrigger.h"
#include "AbstractRealJoystick.h"


class TriggerButtonPress : public AbstractTrigger
{
	public:
		TriggerButtonPress() : AbstractTrigger{} {};
		TriggerButtonPress(const TriggerButtonPress &other) = delete;
		TriggerButtonPress(TriggerButtonPress &&other) = delete;
		TriggerButtonPress& operator=(const TriggerButtonPress &other) = delete;
		TriggerButtonPress& operator=(TriggerButtonPress &&other) = delete;
		virtual ~TriggerButtonPress() = default;
		
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
					rnum == ch.numButtonOrAxis &&
					ch.bButtonPressed);
		};
};

#endif

