#ifndef MICROSOFT_XBOX_360_GAMEPAD
#define MICROSOFT_XBOX_360_GAMEPAD


#include "RealJoystick.h"
class GameController;
class GameControllerAxisEvent;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/MicrosoftXbox360Gamepad.h"


class MicrosoftXbox360Gamepad : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		MicrosoftXbox360Gamepad(GameController *c);
		MicrosoftXbox360Gamepad(const MicrosoftXbox360Gamepad &other) = delete;
		MicrosoftXbox360Gamepad(MicrosoftXbox360Gamepad &&other) = delete;
		MicrosoftXbox360Gamepad& operator=(const MicrosoftXbox360Gamepad &other) = delete;
		MicrosoftXbox360Gamepad& operator=(MicrosoftXbox360Gamepad &&other) = delete;
		~MicrosoftXbox360Gamepad();
		
		QString description() const override final;
		
		uint buttonsCount() const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		uint povsCount() const override final;
		QString povName(uint pov) const override final;
		QStringList povsNames() const override final;
		
		void setData(const QString &str, QVariant v) override final;
		void flush() override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
		
		double m_leftMotorSpeed;
		double m_rightMotorSpeed;
		bool m_bFirstWrite;
		bool m_dataModified;
};


#endif

