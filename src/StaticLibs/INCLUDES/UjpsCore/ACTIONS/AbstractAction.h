#ifndef ABSTRACT_ACTION
#define ABSTRACT_ACTION


#include "VirtualEvent.h"
#include "JoystickChange.h"
#include <vector>
class AbstractRealJoystick;


class AbstractAction
{
	public:
		AbstractAction() = default;
		AbstractAction(const AbstractAction &other) = delete;
		AbstractAction(AbstractAction &&other) = delete;
		AbstractAction& operator=(const AbstractAction &other) = delete;
		AbstractAction& operator=(AbstractAction &&other) = delete;
		virtual ~AbstractAction() = default;
		
		virtual std::vector<VirtualEvent> generateEvents() = 0;
		virtual std::vector<VirtualEvent> generateEvents(const JoystickChange &ch) = 0;
		virtual uint additionalDelay() const {return 0;}; // for chain action only
		
		virtual std::vector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) = 0;
		virtual std::vector<VirtualEvent> deactivateByLayerChange() = 0;
		virtual std::vector<VirtualEvent> aboutToBeDeleted() = 0;
};


#endif

