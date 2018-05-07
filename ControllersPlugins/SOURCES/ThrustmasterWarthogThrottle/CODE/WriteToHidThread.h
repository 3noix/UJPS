#ifndef WRITE_TO_HID_THREAD
#define WRITE_TO_HID_THREAD


#include <QList>
#include <QPair>
#include <QThread>
#include <QMutex>
class HidDevice;


class WriteToHidThread : public QThread
{
	Q_OBJECT
	
	public:
		explicit WriteToHidThread(QObject *parent);
		WriteToHidThread(const WriteToHidThread &other) = delete;
		WriteToHidThread(WriteToHidThread &&other) = delete;
		WriteToHidThread& operator=(const WriteToHidThread &other) = delete;
		WriteToHidThread& operator=(WriteToHidThread &&other) = delete;
		virtual ~WriteToHidThread();
		
		void launchWriteData(quint8 flags, quint8 brightness);
		
		
	protected:
		virtual void run() override final;
		
		
	private:
		void stop();
		QMutex m_mutex;
		bool m_abort;
		
		QList<QPair<quint8,quint8>> m_queue;
		HidDevice *m_hidDevice;
};

#endif

