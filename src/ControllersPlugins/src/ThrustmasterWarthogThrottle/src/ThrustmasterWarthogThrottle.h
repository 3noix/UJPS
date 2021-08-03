#ifndef THRUSTMASTER_WARTHOG_THROTTLE
#define THRUSTMASTER_WARTHOG_THROTTLE


#include "RealJoysticks/RealJoystick.h"
#include "QtGameControllerModif/GameControllerEvents.h"
class WriteToHidThread;
class GameController;

#define INSIDE_PLUGIN
#include "../../../include/ThrustmasterWarthogThrottle.h"


class ThrustmasterWarthogThrottle : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		ThrustmasterWarthogThrottle(GameController *c);
		ThrustmasterWarthogThrottle(const ThrustmasterWarthogThrottle &other) = delete;
		ThrustmasterWarthogThrottle(ThrustmasterWarthogThrottle &&other) = delete;
		ThrustmasterWarthogThrottle& operator=(const ThrustmasterWarthogThrottle &other) = delete;
		ThrustmasterWarthogThrottle& operator=(ThrustmasterWarthogThrottle &&other) = delete;
		~ThrustmasterWarthogThrottle() = default;
		
		QString description() const override final;
		
		uint buttonsCount() const override final;
		bool buttonPressed(uint button) const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		uint povsCount() const override final;
		QString povName(uint pov) const override final;
		QStringList povsNames() const override final;
		
		void setData(const QString &str, QVariant v) override final;
		void flush() override final;
		
		
	private slots:
		void slotGameControllerButtonEvent(GameControllerButtonEvent event) override final;
		void slotGameControllerAxisEvent(GameControllerAxisEvent event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
		
		WriteToHidThread *m_thread;
		bool m_bFirstWrite;
		quint8 m_flags;
		quint8 m_brightness;
		bool m_dataModified;
		bool m_bLed1;
		bool m_bLed2;
		bool m_bLed3;
		bool m_bLed4;
		bool m_bLed5;
		bool m_bBackLit;
		quint8 bitChar(uint i);
};


#endif

