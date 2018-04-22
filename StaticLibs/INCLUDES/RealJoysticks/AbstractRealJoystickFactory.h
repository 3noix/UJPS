#ifndef ABSTRACT_REAL_JOYSTICK_FACTORY
#define ABSTRACT_REAL_JOYSTICK_FACTORY


#include <QObject>
#include <QString>
class AbstractRealJoystick;
class QGameController;


class AbstractRealJoystickFactory
{
	public:
		AbstractRealJoystickFactory() = default;
		AbstractRealJoystickFactory(const AbstractRealJoystickFactory &other) = delete;
		AbstractRealJoystickFactory(AbstractRealJoystickFactory &&other) = delete;
		AbstractRealJoystickFactory& operator=(const AbstractRealJoystickFactory &other) = delete;
		AbstractRealJoystickFactory& operator=(AbstractRealJoystickFactory &&other) = delete;
		virtual ~AbstractRealJoystickFactory() = default;
		
		virtual QString supportedJoystick() const = 0;
		virtual AbstractRealJoystick* createRealJoystick(QGameController *c) = 0;
};

Q_DECLARE_INTERFACE(AbstractRealJoystickFactory,"AbstractRealJoystickFactory")

#endif
