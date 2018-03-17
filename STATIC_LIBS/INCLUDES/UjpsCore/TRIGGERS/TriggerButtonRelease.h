#ifndef TRIGGER_BUTTON_RELEASE
#define TRIGGER_BUTTON_RELEASE


#include "AbstractTrigger.h"
#include "AbstractRealJoystick.h"


class TriggerButtonRelease : public AbstractTrigger
{
	public:
		TriggerButtonRelease() : AbstractTrigger{} {};
		TriggerButtonRelease(const TriggerButtonRelease &other) = delete;
		TriggerButtonRelease(TriggerButtonRelease &&other) = delete;
		TriggerButtonRelease& operator=(const TriggerButtonRelease &other) = delete;
		TriggerButtonRelease& operator=(TriggerButtonRelease &&other) = delete;
		virtual ~TriggerButtonRelease() = default;
		
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
					!ch.bButtonPressed);
		};
};

#endif

