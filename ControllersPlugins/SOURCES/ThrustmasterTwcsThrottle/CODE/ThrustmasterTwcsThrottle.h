#ifndef THRUSTMASTER_TWCS_THROTTLE
#define THRUSTMASTER_TWCS_THROTTLE


#include "RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;


class ThrustmasterTwcsThrottle : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		ThrustmasterTwcsThrottle(QGameController *c);
		ThrustmasterTwcsThrottle(const ThrustmasterTwcsThrottle &other) = delete;
		ThrustmasterTwcsThrottle(ThrustmasterTwcsThrottle &&other) = delete;
		ThrustmasterTwcsThrottle& operator=(const ThrustmasterTwcsThrottle &other) = delete;
		ThrustmasterTwcsThrottle& operator=(ThrustmasterTwcsThrottle &&other) = delete;
		~ThrustmasterTwcsThrottle() = default;
		
		QString description() const override final;
		
		uint buttonsCount() const override final;
		bool buttonPressed(uint button) const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
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
		static const uint TBTN1  = 0;	// instinctive disconnect
		static const uint TBTN2  = 1;	// pinky button left
		static const uint TBTN3  = 2;	// pinky button right
		static const uint TBTN4  = 3;	// slider up
		static const uint TBTN5  = 4;	// slider down
		static const uint TLOCK  = 5;	// mini-stick pressed
		static const uint THAT1U = 6;	// central HAT up
		static const uint THAT1R = 7;	// central HAT right
		static const uint THAT1D = 8;	// central HAT down
		static const uint THAT1L = 9;	// central HAT left
		static const uint THAT3U = 10;	// lower HAT 3 up
		static const uint THAT3R = 11;	// lower HAT 3 right
		static const uint THAT3D = 12;	// lower HAT 3 down
		static const uint THAT3L = 13;	// lower HAT 3 left
		static const uint THAT2U = 14;	// upper HAT (POV) up
		static const uint THAT2R = 15;	// upper HAT (POV) right
		static const uint THAT2D = 16;	// upper HAT (POV) down
		static const uint THAT2L = 17;	// upper HAT (POV) left
		
		static const uint TTHR  = 0;	// throttle axis
		static const uint TRDR  = 1;	// rocker axis
		static const uint TMSTX = 2;	// mini-stick horizontal axis
		static const uint TMSTY = 3;	// mini-stick vertical axis
		static const uint TANT  = 4;	// antenna axis
		static const uint TFRP1 = 5;	// TFRP unknown axis 1 (TCSRUDDER?)
		static const uint TFRP2 = 6;	// TFRP unknown axis 2 (TCSLEFT?)
		static const uint TFRP3 = 7;	// TFRP unknown axis 3 (TCSRIGHT?)
};

#endif
