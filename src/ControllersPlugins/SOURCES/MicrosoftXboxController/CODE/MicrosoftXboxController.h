#ifndef MICROSOFT_XBOX_CONTROLLER
#define MICROSOFT_XBOX_CONTROLLER


#include "RealJoystick.h"
class GameController;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/MicrosoftXboxController.h"


class MicrosoftXboxController : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		MicrosoftXboxController(GameController *c);
		MicrosoftXboxController(const MicrosoftXboxController &other) = delete;
		MicrosoftXboxController(MicrosoftXboxController &&other) = delete;
		MicrosoftXboxController& operator=(const MicrosoftXboxController &other) = delete;
		MicrosoftXboxController& operator=(MicrosoftXboxController &&other) = delete;
		~MicrosoftXboxController();
		
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

