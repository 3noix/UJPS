#ifndef LOGITECH_X56_JOYSTICK
#define LOGITECH_X56_JOYSTICK


#include "RealJoysticks/RealJoystick.h"
#include "QtGameControllerModif/GameControllerEvents.h"
class GameController;

#define INSIDE_PLUGIN
#include "../../../include/LogitechX56Joystick.h"


class LogitechX56Joystick : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		LogitechX56Joystick(GameController *c);
		LogitechX56Joystick(const LogitechX56Joystick &other) = delete;
		LogitechX56Joystick(LogitechX56Joystick &&other) = delete;
		LogitechX56Joystick& operator=(const LogitechX56Joystick &other) = delete;
		LogitechX56Joystick& operator=(LogitechX56Joystick &&other) = delete;
		~LogitechX56Joystick() = default;
		
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
		void slotGameControllerAxisEvent(GameControllerAxisEvent event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
};


#endif

