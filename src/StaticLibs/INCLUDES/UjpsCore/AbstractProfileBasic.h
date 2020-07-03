#ifndef ABSTRACT_PROFILE_BASIC
#define ABSTRACT_PROFILE_BASIC


#include "AbstractProfile.h"

class AbstractRealJoystick;
class RemoteJoystickServer;
class VirtualJoystick;


class AbstractProfileBasic : public AbstractProfile
{
	Q_OBJECT
	
	public:
		AbstractProfileBasic();
		AbstractProfileBasic(const AbstractProfileBasic &other) = delete;
		AbstractProfileBasic(AbstractProfileBasic &&other) = delete;
		AbstractProfileBasic& operator=(const AbstractProfileBasic &other) = delete;
		AbstractProfileBasic& operator=(AbstractProfileBasic &&other) = delete;
		virtual ~AbstractProfileBasic() = default;
		
		// public functions (called by the window only)
		virtual bool play() override;					// executed when clicking "play"
		virtual void run() override;					// executed at each time step
		virtual void stop() override;					// executed when clicking "stop"
		virtual bool isInitComplete() const override;	// to check if remote joysticks are all connected
		
		
	protected:
		AbstractRealJoystick* registerRealJoystick(const QString &description, int num = 0);
		void registerRealJoystick(RemoteJoystickServer *rjs);
		VirtualJoystick* registerVirtualJoystick(uint id);
		
		
	private slots:
		void slotRemoteJoystickConnected();
		
		
	private:
		// private pure virtual functions
		virtual bool setupJoysticks() = 0;			// called by "play" function
		virtual void runOneStep(bool bInit) = 0;	// executed at each run (called by "run")
		
		bool m_bFirstStep;
		
		std::vector<AbstractRealJoystick*> m_realJoysticksNoRemote;
		std::vector<RemoteJoystickServer*> m_remoteJoysticks;
		std::vector<VirtualJoystick*> m_virtualJoysticks;
};


#endif

