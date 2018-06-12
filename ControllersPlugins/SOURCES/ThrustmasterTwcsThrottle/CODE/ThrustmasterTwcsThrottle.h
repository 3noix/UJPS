#ifndef THRUSTMASTER_TWCS_THROTTLE
#define THRUSTMASTER_TWCS_THROTTLE


#include "RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/ThrustmasterTwcsThrottle.h"


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
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		uint povsCount() const override final;
		float povValue(uint pov) const override final;
		QString povName(uint pov) const override final;
		QStringList povsNames() const override final;
		
		
	private slots:
		void slotGameControllerAxisEvent(QGameControllerAxisEvent *event) override final;
		void slotGameControllerPovEvent(QGameControllerPovEvent *event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
};

#endif
