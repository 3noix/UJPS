#ifndef REAL_JOYSTICKS_MANAGER
#define REAL_JOYSTICKS_MANAGER


#include <QObject>
#include <QStringList>
#include <QColor>
#include <vector>
class AbstractRealJoystick;
class AbstractRealJoystickFactory;
class GameController;
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
		void unloadPlugins();
		
		void fromGameControllers(std::vector<GameController*> &gcv);
		
		int nbJoysticks() const;
		QStringList joysticksNames() const;
		
		AbstractRealJoystick* joystick(uint id) const;
		AbstractRealJoystick* joystick(const QString &joystickName, int num = 0) const;
		std::vector<AbstractRealJoystick*> releaseAll();
		
		
	signals:
		void message(QString message, QColor color);
		
		
	private:
		AbstractRealJoystick* createJoystick(GameController *c);
		
		std::vector<AbstractRealJoystick*> m_joysticks;
		std::vector<QPluginLoader*> m_loaders;
		std::vector<AbstractRealJoystickFactory*> m_factories;
};


#endif

