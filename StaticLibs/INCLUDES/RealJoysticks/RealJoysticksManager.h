#ifndef REAL_JOYSTICKS_MANAGER
#define REAL_JOYSTICKS_MANAGER

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QColor>
class AbstractRealJoystick;
class AbstractRealJoystickFactory;
class QGameController;
class QPluginLoader;


class RealJoysticksManager : public QObject
{
	Q_OBJECT
	
	public:
		RealJoysticksManager();
		RealJoysticksManager(const RealJoysticksManager &other) = delete;
		RealJoysticksManager(RealJoysticksManager &&other) = delete;
		RealJoysticksManager& operator=(const RealJoysticksManager &other) = delete;
		RealJoysticksManager& operator=(RealJoysticksManager &&other) = delete;
		virtual ~RealJoysticksManager();
		
		void loadPlugins(const QString &path);
		void searchForControllers();
		
		int nbJoysticks() const;
		QStringList joysticksNames() const;
		
		AbstractRealJoystick* joystick(int id) const;
		AbstractRealJoystick* joystick(const QString &joystickName) const;
		AbstractRealJoystick* releaseJoystick(int id);
		AbstractRealJoystick* releaseJoystick(const QString &joystickName);
		
		
	signals:
		void message(QString message, QColor color);
		
		
	private:
		AbstractRealJoystick* createJoystick(QGameController *c);
		
		QVector<AbstractRealJoystick*> m_joysticks;
		QVector<QPluginLoader*> m_loaders;
		QVector<AbstractRealJoystickFactory*> m_factories;
};

#endif
