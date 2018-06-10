#ifndef ABSTRACT_REMOTE_JOYSTICK_CLIENT
#define ABSTRACT_REMOTE_JOYSTICK_CLIENT


#include <QObject>
#include <QDataStream>
#include <QAbstractSocket>
class QTcpSocket;
class QNetworkSession;


class AbstractRemoteJoystickClient : public QObject
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
		
		explicit AbstractRemoteJoystickClient(QObject *parent = nullptr);
		AbstractRemoteJoystickClient(const AbstractRemoteJoystickClient &other) = delete;
		AbstractRemoteJoystickClient(AbstractRemoteJoystickClient &&other) = delete;
		AbstractRemoteJoystickClient& operator=(const AbstractRemoteJoystickClient &other) = delete;
		AbstractRemoteJoystickClient& operator=(AbstractRemoteJoystickClient &&other) = delete;
		virtual ~AbstractRemoteJoystickClient() = default;
		
		virtual QString description() const = 0;
		virtual quint8 buttonsCount() const = 0;
		virtual QStringList buttonsNames() const = 0;
		virtual quint8 axesCount() const = 0;
		virtual QStringList axesNames() const = 0;
		virtual quint8 povsCount() const = 0;
		virtual QStringList povsNames() const = 0;
		virtual void setData(const QString &prop, QVariant v) = 0;
		
		State state() const;
		
		
	signals:
		void stateChanged(State s);
		void error(QString str);
		
		
	public slots:
		void slotConnect(const QString &hostName, quint16 port);
		void slotDisconnect();
		void slotSendButtonInfo(quint8 button, bool bPressed);
		void slotSendAxisInfo(quint8 axis, float axisValue);
		void slotSendPovInfo(quint8 pov, float povValue);
		
		
	private slots:
		void slotSessionOpened();
		void slotConnected();
		void slotReceiveData();
		void slotDisconnected();
		void slotError(QAbstractSocket::SocketError socketError);
		
		
	private:
		void setState(State s);
		
		QString m_hostName;
		quint16 m_port;
		State m_state;
		QTcpSocket *m_tcpSocket;
		QNetworkSession *m_networkSession;
};

#endif

