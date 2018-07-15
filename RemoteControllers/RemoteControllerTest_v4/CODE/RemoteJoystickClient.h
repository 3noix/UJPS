#ifndef REMOTE_JOYSTICK_CLIENT
#define REMOTE_JOYSTICK_CLIENT


#include <QObject>
#include <QDataStream>
#include <QAbstractSocket>
#include <QStringList>
class QTcpSocket;
class QNetworkSession;


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
		
		explicit RemoteJoystickClient(
			const QString &description,
			const QStringList &buttonsNames,
			const QStringList &axesNames,
			const QStringList &povsNames,
			QObject *parent = nullptr
		);
		RemoteJoystickClient(const RemoteJoystickClient &other) = delete;
		RemoteJoystickClient(RemoteJoystickClient &&other) = delete;
		RemoteJoystickClient& operator=(const RemoteJoystickClient &other) = delete;
		RemoteJoystickClient& operator=(RemoteJoystickClient &&other) = delete;
		virtual ~RemoteJoystickClient() = default;
		
		QString description() const;
		quint8 buttonsCount() const;
		QStringList buttonsNames() const;
		quint8 axesCount() const;
		QStringList axesNames() const;
		quint8 povsCount() const;
		QStringList povsNames() const;
		void setData(const QString &prop, QVariant v);
		
		State state() const;
		
		
	signals:
		void stateChanged(State s);
		void error(QString str);
		void signalSetData(const QString &prop, QVariant v);
		
		
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
		
		QString m_description;
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
		
		QString m_hostName;
		quint16 m_port;
		State m_state;
		QTcpSocket *m_tcpSocket;
		QNetworkSession *m_networkSession;
};

#endif

