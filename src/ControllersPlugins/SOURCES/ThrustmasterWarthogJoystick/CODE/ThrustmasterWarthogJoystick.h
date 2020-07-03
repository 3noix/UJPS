#ifndef THRUSTMASTER_WARTHOG_JOYSTICK
#define THRUSTMASTER_WARTHOG_JOYSTICK


#include "RealJoystick.h"
class GameController;
class GameControllerAxisEvent;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/ThrustmasterWarthogJoystick.h"


class ThrustmasterWarthogJoystick : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		ThrustmasterWarthogJoystick(GameController *c);
		ThrustmasterWarthogJoystick(const ThrustmasterWarthogJoystick &other) = delete;
		ThrustmasterWarthogJoystick(ThrustmasterWarthogJoystick &&other) = delete;
		ThrustmasterWarthogJoystick& operator=(const ThrustmasterWarthogJoystick &other) = delete;
		ThrustmasterWarthogJoystick& operator=(ThrustmasterWarthogJoystick &&other) = delete;
		~ThrustmasterWarthogJoystick() = default;
		
		QString description() const override final;
		
		uint buttonsCount() const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		uint povsCount() const override final;
		QString povName(uint pov) const override final;
		QStringList povsNames() const override final;
		
		
	protected slots:
		void slotGameControllerAxisEvent(GameControllerAxisEvent *event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
};


#endif

