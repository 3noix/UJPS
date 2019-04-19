#ifndef GAME_CONTROLLERS_ENUM_THREAD
#define GAME_CONTROLLERS_ENUM_THREAD


#include <QThread>
#include <QMutex>
#include <QVector>
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
		QVector<GameController*> gameControllers();
		QVector<GameController*> releaseGameControllers();
		
		
	protected:
		virtual void run() override;
		
		
	private:
		QMutex m_mutex;
		bool m_bStop;
		bool m_b1by1;
		QVector<GameController*> m_joysticks;
};


#endif

