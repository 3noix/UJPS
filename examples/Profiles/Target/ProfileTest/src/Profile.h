#ifndef PROFILE
#define PROFILE


#include "UjpsCore/AbstractProfileTarget.h"
class EnhancedJoystick;
class AbstractAction;


class Profile : public AbstractProfileTarget
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Profile")
	Q_INTERFACES(AbstractProfile)
	
	
	public:
		Profile();
		Profile(const Profile &other) = delete;
		Profile(Profile &&other) = delete;
		Profile& operator=(const Profile &other) = delete;
		Profile& operator=(Profile &&other) = delete;
		virtual ~Profile();
		
		virtual void stop() override final;
		
		
	private:
		virtual bool setupJoysticks() override final;
		virtual void runFirstStep() override final;
		
		EnhancedJoystick *tmwj; // for Thrustmaster Warthog Joystick
		EnhancedJoystick *tmwt; // for Thrustmaster Warthog Throttle
		EnhancedJoystick *mfgx; // for MFG Crosswind V2 rudder pedals
		VirtualJoystick  *vj1;  // virtual joystick #1
		VirtualJoystick  *vj2;  // virtual joystick #2
		
		AbstractAction *actionTestRexec;
};


#endif

