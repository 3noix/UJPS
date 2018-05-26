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
		
		virtual void stop() override final;
		
		
	private:
		virtual bool setupJoysticks() override final;
		virtual void runFirstStep() override final;
		
		EnhancedJoystick *tmwj; // for Thrustmaster Warthog Joystick
		EnhancedJoystick *tmwt; // for Thrustmaster Warthog Throttle
		EnhancedJoystick *mfgx; // for MFG Crosswind V2 rudder pedals
		VirtualJoystick  *vj1;  // virtual joystick #1
		
		
		
		// control mode
		void setControlsGround();
		void setControlsFlightLanding();
		void setControlsFlightCruise();
		
		// targeting
		void browseHostileTargets();
		void browseAllTargets();
		void browseFriendTargets();
		void browsePinnedTargets();
		void previousTarget();
		void nextTarget();
		
		// shields
		void switchShieldsMode();
		void shieldsDownArrow();
		void shieldsUpArrow();
		void releaseLongiShieldsButtons();
		
		// stick trims
		void reset_dxxy_trims();
		void set_dxxy_trims();
		
		
		
		// shields and targeting modes
		uint ncPulse;
		bool m_bShieldsHorizontalMode;
		uint m_targetsTypeToCycle;
		
		// curves parameters
		const float k = 0.02f;
		const float DeadZone_L  = k * 3.0f;
		const float DeadZone_C  = k * 3.0f;
		const float DeadZone_C2 = k * 15.0f;
		const float DeadZone_R  = k * 3.0f;
		const float curveParam  = 3.0f;
		
		
		
		// control modes sub-functions
		void set_JOYXY_for_turnNthrottle();
		void set_JOYXY_for_turnNbrake();
		void set_JOYXY_for_landing();
		void set_JOYXY_for_strafe();
		void set_JOYXY_for_rollNpitch();
		
		void set_S4_for_horn();
		void set_S4_for_landing();
		void set_S4_for_nothing();
		
		void set_BUTTONS_for_landing();
		void set_BUTTONS_for_cruise();
		
		void set_THR_for_nothing();
		void set_THR_for_ground();
		void set_THR_for_landing();
		void set_THR_for_cruise();
		
		void set_THRLEFT_for_groundForward();
		void set_THRLEFT_for_groundBackward();
		void set_THRLEFT_for_verticalStrafe();
		void set_THRLEFT_for_nothing();
		void set_THRRIGHT_for_flightThrottle();
};

#endif

