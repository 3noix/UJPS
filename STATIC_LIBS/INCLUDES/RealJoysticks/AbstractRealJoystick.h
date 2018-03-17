#ifndef ABSTRACT_REAL_JOYSTICK
#define ABSTRACT_REAL_JOYSTICK


#include <QObject>
#include <QVector>
#include "JoystickChange.h"


class AbstractRealJoystick
{
	public:
		AbstractRealJoystick() = default;
		AbstractRealJoystick(const AbstractRealJoystick &other) = delete;
		AbstractRealJoystick(AbstractRealJoystick &&other) = delete;
		AbstractRealJoystick& operator=(const AbstractRealJoystick &other) = delete;
		AbstractRealJoystick& operator=(AbstractRealJoystick &&other) = delete;
		virtual ~AbstractRealJoystick() = default;
		
		virtual uint id() const = 0;
		virtual QString description() const = 0;
		virtual QString hardwareId() const = 0;
		virtual void readGameController() = 0;
		virtual QVector<JoystickChange> changes() = 0;
		
		virtual uint buttonCount() const = 0;
		virtual bool buttonPressed(uint button) const = 0;
		virtual QString buttonName(uint button) const = 0;
		virtual QStringList buttonsNames() const = 0;
		
		virtual uint axisCount() const = 0;
		virtual float axisValue(uint axis) const = 0;
		virtual QString axisName(uint axis) const = 0;
		virtual QStringList axesNames() const = 0;
};

Q_DECLARE_INTERFACE(AbstractRealJoystick,"AbstractRealJoystick")

#endif
