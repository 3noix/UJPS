#ifndef GAME_CONTROLLERS_ENUM_THREAD
#define GAME_CONTROLLERS_ENUM_THREAD


#include <QThread>
#include <QMutex>
#include <vector>
class GameController;


class GameControllersEnumThread : public QThread
{
	Q_OBJECT
	
	public:
		explicit GameControllersEnumThread(QObject *parent);
		GameControllersEnumThread(const GameControllersEnumThread &other) = delete;
		GameControllersEnumThread(GameControllersEnumThread &&other) = delete;
		GameControllersEnumThread& operator=(const GameControllersEnumThread &other) = delete;
		GameControllersEnumThread& operator=(GameControllersEnumThread &&other) = delete;
		virtual ~GameControllersEnumThread();
		
		// start / stop computation
		void enumerateControllersAllAtOnce();
		void enumerateControllersOneByOne();
		void stop(); // has no effect with "enumerateControllersAllAtOnce"
		
		// retrieve results
		std::vector<GameController*> gameControllers();
		std::vector<GameController*> releaseGameControllers();
		
		
	signals:
		void done();
		
		
	protected:
		virtual void run() override;
		
		
	private:
		QMutex m_mutex;
		bool m_bStop;
		bool m_b1by1;
		std::vector<GameController*> m_joysticks;
};


#endif

