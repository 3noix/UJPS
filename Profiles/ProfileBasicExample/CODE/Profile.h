#ifndef PROFILE
#define PROFILE


#include "AbstractProfileBasic.h"
class AbstractRealJoystick;


class Profile : public AbstractProfileBasic
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
		virtual void runOneStep(bool bInit) override final;
		
		AbstractRealJoystick *tmwj; // for Thrustmaster Warthog Joystick
		AbstractRealJoystick *tmwt; // for Thrustmaster Warthog Throttle
		AbstractRealJoystick *mfgx; // for MFG Crosswind V2 rudder pedals
		VirtualJoystick  *vj1;      // virtual joystick #1
		VirtualJoystick  *vj2;      // virtual joystick #2
};


#endif

