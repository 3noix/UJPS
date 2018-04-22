#ifndef REAL_JOYSTICK_FACTORY
#define REAL_JOYSTICK_FACTORY


#include "AbstractRealJoystickFactory.h"
#include "ThrustmasterTwcsThrottle.h"


class RealJoystickFactory : public QObject, public AbstractRealJoystickFactory
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "RealJoystickFactory")
	Q_INTERFACES(AbstractRealJoystickFactory)
	
		
	public:
		RealJoystickFactory() = default;
		RealJoystickFactory(const RealJoystickFactory &other) = delete;
		RealJoystickFactory(RealJoystickFactory &&other) = delete;
		RealJoystickFactory& operator=(const RealJoystickFactory &other) = delete;
		RealJoystickFactory& operator=(RealJoystickFactory &&other) = delete;
		~RealJoystickFactory() = default;
		
		QString supportedJoystick() const override final
		{
			return "TWCS Throttle";
		};
		
		AbstractRealJoystick* createRealJoystick(QGameController *c) override final
		{
			return new ThrustmasterTwcsThrottle{c};
		};
};

#endif
