#ifndef PROFILE
#define PROFILE


#include "UjpsCore/AbstractProfileBasic.h"
class RemoteJoystickServer;


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
		
		RemoteJoystickServer *remote;
		VirtualJoystick  *vj1;
};


#endif

