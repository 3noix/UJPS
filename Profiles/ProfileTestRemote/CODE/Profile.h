#ifndef PROFILE
#define PROFILE


#include "AbstractProfile.h"
class EnhancedJoystick;


class Profile : public AbstractProfile
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
		
		virtual bool play() override final;
		virtual bool stop() override final;
		
		
	private:
		// joysticks
		bool setupJoysticks();
		void init();
		
		RealJoysticksManager *rjm;
		EnhancedJoystick *tmwj; // for Thrustmaster Warthog Joystick
		EnhancedJoystick *rjse; // interface with the client application ...
		VirtualJoystick  *vj1;  // virtual joystick #1
};

#endif

