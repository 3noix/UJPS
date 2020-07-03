#ifndef ABSTRACT_TRIGGER
#define ABSTRACT_TRIGGER


#include "JoystickChange.h"
#include "ControlType.h"
class AbstractRealJoystick;


class AbstractTrigger
{
	public:
		AbstractTrigger() = default;
		AbstractTrigger(const AbstractTrigger &other) = delete;
		AbstractTrigger(AbstractTrigger &&other) = delete;
		AbstractTrigger& operator=(const AbstractTrigger &other) = delete;
		AbstractTrigger& operator=(AbstractTrigger &&other) = delete;
		virtual ~AbstractTrigger() = default;
		
		virtual bool reactsToChanges() const = 0;
		virtual bool reactsToStates() const = 0;
		virtual bool isTriggered(AbstractRealJoystick *rj, ControlType t, uint rnum) const = 0;
		virtual bool isTriggered(AbstractRealJoystick *rj, ControlType t, uint rnum, const JoystickChange &ch) const = 0;
};


#endif

