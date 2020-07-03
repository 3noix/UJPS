#ifndef LOGITECH_X56_JOYSTICK
#define LOGITECH_X56_JOYSTICK


#include "RealJoystick.h"
class GameController;
class GameControllerAxisEvent;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/LogitechX56Throttle.h"


class LogitechX56Throttle : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		LogitechX56Throttle(GameController *c);
		LogitechX56Throttle(const LogitechX56Throttle &other) = delete;
		LogitechX56Throttle(LogitechX56Throttle &&other) = delete;
		LogitechX56Throttle& operator=(const LogitechX56Throttle &other) = delete;
		LogitechX56Throttle& operator=(LogitechX56Throttle &&other) = delete;
		~LogitechX56Throttle() = default;
		
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

