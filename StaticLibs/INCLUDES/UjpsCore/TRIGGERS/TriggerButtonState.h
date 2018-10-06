#ifndef TRIGGER_BUTTON_STATE
#define TRIGGER_BUTTON_STATE


#include "AbstractTrigger.h"
#include "AbstractRealJoystick.h"


class TriggerButtonState : public AbstractTrigger
{
	public:
		TriggerButtonState(bool bDown) : AbstractTrigger{}, m_bDown{bDown} {};
		TriggerButtonState(const TriggerButtonState &other) = delete;
		TriggerButtonState(TriggerButtonState &&other) = delete;
		TriggerButtonState& operator=(const TriggerButtonState &other) = delete;
		TriggerButtonState& operator=(TriggerButtonState &&other) = delete;
		virtual ~TriggerButtonState() = default;
		
		virtual bool reactsToChanges() const override final {return false;};
		virtual bool reactsToStates() const override final {return true;};
		
		virtual bool isTriggered(AbstractRealJoystick *rj, ControlType t, uint rnum) const override final
		{
			return (rj != nullptr && t == ControlType::Button && rj->buttonPressed(rnum) == m_bDown);
		};
		
		virtual bool isTriggered(AbstractRealJoystick *rj, ControlType t, uint rnum, const JoystickChange &ch) const override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			Q_UNUSED(ch)
			return false;
		};
		
		
	private:
		bool m_bDown;
};


#endif

