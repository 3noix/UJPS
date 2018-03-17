#ifndef REAL_JOYSTICKS_MANAGER
#define REAL_JOYSTICKS_MANAGER


#include <QVector>
#include <QStringList>
class AbstractRealJoystick;
class QGameController;


class RealJoysticksManager
{
	public:
		RealJoysticksManager();
		RealJoysticksManager(const RealJoysticksManager &other) = delete;
		RealJoysticksManager(RealJoysticksManager &&other) = delete;
		RealJoysticksManager& operator=(const RealJoysticksManager &other) = delete;
		RealJoysticksManager& operator=(RealJoysticksManager &&other) = delete;
		virtual ~RealJoysticksManager();
		
		int nbJoysticks() const;
		QStringList joysticksNames() const;
		
		AbstractRealJoystick* joystick(int id) const;
		AbstractRealJoystick* joystick(const QString &joystickName) const;
		AbstractRealJoystick* releaseJoystick(int id);
		AbstractRealJoystick* releaseJoystick(const QString &joystickName);
		
		
	private:
		AbstractRealJoystick* createJoystick(QGameController *c);
		QVector<AbstractRealJoystick*> m_joysticks;
};

#endif
