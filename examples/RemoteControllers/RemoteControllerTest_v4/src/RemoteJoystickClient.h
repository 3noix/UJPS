#ifndef REMOTE_JOYSTICK_CLIENT
#define REMOTE_JOYSTICK_CLIENT


#include <QObject>
#include <QWebSocket>


class RemoteJoystickClient : public QObject
{
	Q_OBJECT
	
	public:
		enum class State
		{
			NotConnected,
			Connecting,
			Connected,
			Error
		};
		
		explicit RemoteJoystickClient(QObject *parent = nullptr);
		RemoteJoystickClient(const RemoteJoystickClient &other) = delete;
		RemoteJoystickClient(RemoteJoystickClient &&other) = delete;
		RemoteJoystickClient& operator=(const RemoteJoystickClient &other) = delete;
		RemoteJoystickClient& operator=(RemoteJoystickClient &&other) = delete;
		virtual ~RemoteJoystickClient() = default;
		
		State state() const;
		
		
	signals:
		void stateChanged(State s);
		void error(QString str);
		void signalSetData(const QString &data);
		
		
	public slots:
		void slotConnect(const QString &hostName, quint16 wsPort);
		void slotDisconnect();
		void slotSendButtonInfo(uint button, bool bPressed);
		void slotSendAxisInfo(uint axis, float axisValue);
		void slotSendPovInfo(uint pov, float povValue);
		
		
	private slots:
		void slotConnected();
		void slotMessageReceived(const QString &msg);
		void slotDisconnected();
		void slotError(QAbstractSocket::SocketError socketError);
		
		
	private:
		void setState(State s);
		
		State m_state;
		QWebSocket m_webSocket;
};


#endif

