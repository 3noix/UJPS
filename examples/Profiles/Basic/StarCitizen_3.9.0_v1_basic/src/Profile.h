#ifndef PROFILE
#define PROFILE


#include "UjpsCore/AbstractProfileBasic.h"
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
		
		
	private:
		struct AxesData
		{
			float JOYX;
			float JOYY;
			float THRL;
			float THRR;
			float DRPED;
			float BRKL;
			float BRKR;
		};
		
		enum TargetingMode {All, Hostiles, Friends, Pinned};
		
		void processThe6FlightAxes(const AxesData &data) const;
		void processSpeedManagement() const;
		void processOtherFlightControls() const;
		void processTargeting() const;
		void processScan() const;
		void processWeaponsAndCm() const;
		void processPower() const;
		void processShields() const;
		void processGround(const AxesData &data) const;
		void processView() const;
		void processLeds(bool bInit) const;
		void processOther() const;
		
		AxesData getAxesData(bool bInit) const;
		float getLandingFactor(bool bLndMode) const;
		
		// "constants" that can be different function of the time-step
		uint nbCyclesPulseButton;
		uint nbCycles500ms;
		uint nbCycles1s;
		
		// constants
		const bool bTrimAtInit = true;
		const float thrlevx1 = -0.045f;
		const float thrlevx2 = 0.01f;
		
		const float kIntLndFactor = 0.5f;
		const float kIntLndFactorMin = 0.01f;
		const float kIntLndFactorRlim = 1.0f;
		const float kLndRollPitch = 1.0f;
		const float kIntSpdLim = 0.5f;
		const bool bShieldsHorzInit = true;
		
		const bool bUseBrkPedForGnd = false;
		const float BRKR_LDZ = 0.055f;
		const float BRKR_RDZ = 0.1f;
		
		const float dtLedsCycle = 3.0f;
		const float dtLedsFlash = 0.4f;
		const float dtLedsMin = 15.0f;
};


#endif

