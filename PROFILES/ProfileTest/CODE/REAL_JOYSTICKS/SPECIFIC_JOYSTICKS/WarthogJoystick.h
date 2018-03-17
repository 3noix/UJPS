#ifndef WARTHOG_JOYSTICK
#define WARTHOG_JOYSTICK


#include "../RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;
class RealJoysticksManager;


class WarthogJoystick : public RealJoystick
{
	Q_OBJECT
	friend class RealJoysticksManager;
	
	
	private:
		WarthogJoystick(QGameController *c);
		
		
	public:
		WarthogJoystick(const WarthogJoystick &other) = delete;
		WarthogJoystick(WarthogJoystick &&other) = delete;
		WarthogJoystick& operator=(const WarthogJoystick &other) = delete;
		WarthogJoystick& operator=(WarthogJoystick &&other) = delete;
		~WarthogJoystick() = default;
		
		QString description() const override final;
		
		uint buttonCount() const override final;
		bool buttonPressed(uint button) const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axisCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		
	protected slots:
		void slotGameControllerButtonEvent(QGameControllerButtonEvent *event) override final;
		void slotGameControllerAxisEvent(QGameControllerAxisEvent *event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		
		
	public:
		static const uint TG1 = 0;		// trigger stage 1
		static const uint S2  = 1;		// Weapon release
		static const uint S3  = 2;		// NWS (nose wheel steering)
		static const uint S4  = 3;
		static const uint S1  = 4;		// MMCB (master mode control button)
		static const uint TG2 = 5;		// trigger stage 2
		static const uint H2U = 6;		// H2 = TMS
		static const uint H2R = 7;
		static const uint H2D = 8;
		static const uint H2L = 9;
		static const uint H3U = 10;	// H3 = DMS
		static const uint H3R = 11;
		static const uint H3D = 12;
		static const uint H3L = 13;
		static const uint H4U = 14;	// H4 = CMS
		static const uint H4R = 15;
		static const uint H4D = 16;
		static const uint H4L = 17;
		static const uint H4P = 18;
		static const uint H1U = 19;	// H1 = Trim switch / POV (4 virtual buttons)
		static const uint H1R = 20;
		static const uint H1D = 21;
		static const uint H1L = 22;
		
		static const uint JOYX = 0;
		static const uint JOYY = 1;
};

#endif
