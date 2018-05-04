#ifndef ABSTRACT_REAL_JOYSTICK
#define ABSTRACT_REAL_JOYSTICK


#include <QObject>
#include <QVector>
#include <QVariant>
#include "JoystickChange.h"
class QGameController;


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
		
		virtual uint buttonsCount() const = 0;
		virtual bool buttonPressed(uint button) const = 0;
		virtual QString buttonName(uint button) const = 0;
		virtual QStringList buttonsNames() const = 0;
		
		virtual uint axesCount() const = 0;
		virtual float axisValue(uint axis) const = 0;
		virtual QString axisName(uint axis) const = 0;
		virtual QStringList axesNames() const = 0;
		
		virtual void setData(const QString &str, QVariant v) = 0;
};

Q_DECLARE_INTERFACE(AbstractRealJoystick,"AbstractRealJoystick")

#endif
