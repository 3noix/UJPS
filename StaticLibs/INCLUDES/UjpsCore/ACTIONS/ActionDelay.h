#ifndef ACTION_DELAY
#define ACTION_DELAY


#include "AbstractAction.h"


class Delay : public AbstractAction
{
	public:
		Delay(uint delay) :
			AbstractAction{},
			m_delay{delay}
		{};
		Delay(const Delay &other) = delete;
		Delay(Delay &&other) = delete;
		Delay& operator=(const Delay &other) = delete;
		Delay& operator=(Delay &&other) = delete;
		virtual ~Delay() = default;
		
		virtual QVector<VirtualEvent> generateEvents() override final
		{
			return {};
		};
		
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) override final
		{
			Q_UNUSED(ch)
			return {};
		};
		
		virtual uint additionalDelay() const override final
		{
			return m_delay;
		};
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) override final
		{
			Q_UNUSED(rj)
			Q_UNUSED(t)
			Q_UNUSED(rnum)
			return {};
		};
		
		virtual QVector<VirtualEvent> deactivateByLayerChange() override final {return {};};
		virtual QVector<VirtualEvent> aboutToBeDeleted() override final {return {};};
		
		
	private:
		uint m_delay;
};


#endif

