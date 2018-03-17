#ifndef WARTHOG_THROTTLE
#define WARTHOG_THROTTLE


#include "../RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;
class RealJoysticksManager;


class WarthogThrottle : public RealJoystick
{
	Q_OBJECT
	friend class RealJoysticksManager;
	
	
	private:
		WarthogThrottle(QGameController *c);
		
		
	public:
		WarthogThrottle(const WarthogThrottle &other) = delete;
		WarthogThrottle(WarthogThrottle &&other) = delete;
		WarthogThrottle& operator=(const WarthogThrottle &other) = delete;
		WarthogThrottle& operator=(WarthogThrottle &&other) = delete;
		~WarthogThrottle() = default;
		
		QString description() const override final;
		
		uint buttonCount() const override final;
		bool buttonPressed(uint button) const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axisCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		
	private slots:
		void slotGameControllerButtonEvent(QGameControllerButtonEvent *event) override final;
		void slotGameControllerAxisEvent(QGameControllerAxisEvent *event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		
		
	public:
		static const uint SC       = 0;	// slew control
		static const uint MSP      = 1;	// MS = micro switch
		static const uint MSU      = 2;
		static const uint MSR      = 3;
		static const uint MSD      = 4;
		static const uint MSL      = 5;
		static const uint SPDF     = 6;	// speedbrake forward
		static const uint SPDB     = 7;	// speedbrake backward
		static const uint BSF      = 8;	// boat switch forward
		static const uint BSB      = 9;	// boat switch backward
		static const uint CHF      = 10;	// china hat forward
		static const uint CHB      = 11;	// china hat backward
		static const uint PSF      = 12;	// pinky switch forward
		static const uint PSB      = 13;	// pinky switch backward
		static const uint LTB      = 14;
		static const uint EFLNORM  = 15;	// engine left fuel norm
		static const uint EFRNORM  = 16;	// engine right fuel norm
		static const uint EOLMOTOR = 17;	// engine left oper motor
		static const uint EORMOTOR = 18;	// engine right oper motor
		static const uint APUON    = 19;	// APU switch
		static const uint LDGH     = 20;	// landing gear warning silence
		static const uint FLAPU    = 21;	// flaps up
		static const uint FLAPD    = 22;	// flapse down
		static const uint EACON    = 23;
		static const uint RDRNRM   = 24;	// radio altimeter norm
		static const uint APENG    = 25;	// engage autopilot
		static const uint APATT    = 26;	// autopilot path
		static const uint APALT    = 27;	// autopilot ALT
		static const uint IDLERON  = 28;	// idle right engine
		static const uint IDLELON  = 29;	// idle left engine
		static const uint EOLIGN   = 30;	// engine left oper ignition
		static const uint EORIGN   = 31;	// engine right oper ignition
		
		static const uint CSU      = 32;	// virtual: slew control UP
		static const uint CSR      = 33;	// virtual: slew control RIGHT
		static const uint CSD      = 34;	// virtual: slew control DOWN
		static const uint CSL      = 35;	// virtual: slew control LEFT
		static const uint EFLOVER  = 36;	// virtual: engine left fuel override
		static const uint EFROVER  = 37;	// virtual: engine right fuel override
		static const uint APUOFF   = 38;	// virtual
		static const uint EACOFF   = 39;	// virutal
		static const uint RDRDIS   = 40;	// virtual: radio altimeter disabled
		static const uint APDIS    = 41;	// virtual: APENG button not pressed
		static const uint IDLEROFF = 42;	// virtual
		static const uint IDLELOFF = 43;	// virtual
		static const uint EOLNORM  = 44;	// virtual
		static const uint EORNORM  = 45;	// virtual
		static const uint FLAPM    = 46;	// virtual: flaps middle
		static const uint SPDM     = 47;	// virtual: speedbrake middle
		static const uint BSM      = 48;	// virtual: boat switch middle
		static const uint CHM      = 49;	// virtual: china hat middle
		static const uint PSM      = 50;	// virtual: pinky switch middle
		static const uint APAH     = 51;	// virtual: autopilot ALT/HDG
		
		static const uint THR_LEFT  = 0;	// thrust left lever
		static const uint THR_RIGHT = 1;	// thrust right lever
		static const uint THR_FC    = 2;	// friction control
		static const uint SCX       = 3;	// slew control X
		static const uint SCY       = 4;	// slew control Y
};

#endif
