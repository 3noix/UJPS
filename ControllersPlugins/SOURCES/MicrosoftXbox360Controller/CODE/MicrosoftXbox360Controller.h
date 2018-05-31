#ifndef MICROSOFT_XBOX_360_CONTROLLER
#define MICROSOFT_XBOX_360_CONTROLLER


#include "RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/MicrosoftXbox360Controller.h"


class MicrosoftXbox360Controller : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		MicrosoftXbox360Controller(QGameController *c);
		MicrosoftXbox360Controller(const MicrosoftXbox360Controller &other) = delete;
		MicrosoftXbox360Controller(MicrosoftXbox360Controller &&other) = delete;
		MicrosoftXbox360Controller& operator=(const MicrosoftXbox360Controller &other) = delete;
		MicrosoftXbox360Controller& operator=(MicrosoftXbox360Controller &&other) = delete;
		~MicrosoftXbox360Controller() = default;
		
		QString description() const override final;
		
		uint buttonsCount() const override final;
		bool buttonPressed(uint button) const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		
	protected slots:
		void slotGameControllerButtonEvent(QGameControllerButtonEvent *event) override final;
		void slotGameControllerAxisEvent(QGameControllerAxisEvent *event) override final;
		
		
	private:
		QStringList m_buttonsNames;
		QStringList m_axesNames;
};

#endif
