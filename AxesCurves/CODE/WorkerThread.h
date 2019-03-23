#ifndef WORKER_THREAD
#define WORKER_THREAD


#include <QThread>
#include <QMutex>
#include <QVector>
class GameController;


class WorkerThread : public QThread
{
	Q_OBJECT
	
	public:
		explicit WorkerThread(QObject *parent);
		WorkerThread(const WorkerThread &other) = delete;
		WorkerThread(WorkerThread &&other) = delete;
		WorkerThread& operator=(const WorkerThread &other) = delete;
		WorkerThread& operator=(WorkerThread &&other) = delete;
		virtual ~WorkerThread();
		
		void enumerateControllers();
		QVector<GameController*> gameControllers();
		QVector<GameController*> releaseGameControllers();
		
		
	protected:
		virtual void run() override;
		
		
	private:
		QMutex m_mutex;
		QVector<GameController*> m_joysticks;
};


#endif

