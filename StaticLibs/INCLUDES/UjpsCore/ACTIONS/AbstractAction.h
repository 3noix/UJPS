#ifndef ABSTRACT_ACTION
#define ABSTRACT_ACTION


#include "VirtualEvent.h"
#include "JoystickChange.h"


class AbstractAction
{
	public:
		AbstractAction() = default;
		AbstractAction(const AbstractAction &other) = delete;
		AbstractAction(AbstractAction &&other) = delete;
		AbstractAction& operator=(const AbstractAction &other) = delete;
		AbstractAction& operator=(AbstractAction &&other) = delete;
		virtual ~AbstractAction() = default;
		
		virtual QVector<VirtualEvent> generateEvents() = 0;
		virtual QVector<VirtualEvent> generateEvents(const JoystickChange &ch) = 0;
		virtual uint additionalDelay() const {return 0;}; // for chain action only
		
		virtual QVector<VirtualEvent> activateByLayerChange(AbstractRealJoystick *rj, ControlType t, uint rnum) = 0;
		virtual QVector<VirtualEvent> deactivateByLayerChange() = 0;
		virtual QVector<VirtualEvent> aboutToBeDeleted() = 0;
};

#endif

