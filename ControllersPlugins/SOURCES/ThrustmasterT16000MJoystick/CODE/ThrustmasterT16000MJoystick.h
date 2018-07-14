#ifndef THRUSTMASTER_T16000M_JOYSTICK
#define THRUSTMASTER_T16000M_JOYSTICK


#include "RealJoystick.h"
class GameController;
class GameControllerAxisEvent;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/ThrustmasterT16000MJoystick.h"


class ThrustmasterT16000MJoystick : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		ThrustmasterT16000MJoystick(GameController *c);
		ThrustmasterT16000MJoystick(const ThrustmasterT16000MJoystick &other) = delete;
		ThrustmasterT16000MJoystick(ThrustmasterT16000MJoystick &&other) = delete;
		ThrustmasterT16000MJoystick& operator=(const ThrustmasterT16000MJoystick &other) = delete;
		ThrustmasterT16000MJoystick& operator=(ThrustmasterT16000MJoystick &&other) = delete;
		~ThrustmasterT16000MJoystick() = default;
		
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
		
		
	private slots:
		void slotGameControllerAxisEvent(GameControllerAxisEvent *event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
};

#endif
