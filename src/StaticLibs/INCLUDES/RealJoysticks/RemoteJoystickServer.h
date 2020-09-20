#ifndef REMOTE_JOYSTICK_SERVER
#define REMOTE_JOYSTICK_SERVER


#include <QObject>
#include <list>
#include "AbstractRealJoystick.h"
class QHttpServer;
class QWebSocketServer;
class QWebSocket;


class RemoteJoystickServer : public QObject, public AbstractRealJoystick
{
	Q_OBJECT
	Q_INTERFACES(AbstractRealJoystick)
	
	
	public:
		RemoteJoystickServer(const QString &name, quint16 httpPort, quint16 wsPort, uint id, const QString &resourcesPath);
		RemoteJoystickServer(const RemoteJoystickServer &other) = delete;
		RemoteJoystickServer(RemoteJoystickServer &&other) = delete;
		RemoteJoystickServer& operator=(const RemoteJoystickServer &other) = delete;
		RemoteJoystickServer& operator=(RemoteJoystickServer &&other) = delete;
		virtual ~RemoteJoystickServer();
		
		bool isConnected() const;
		QString url() const;
		
		virtual uint id() const override final;
		virtual QString description() const override final;
		virtual QString hardwareId() const override final;
		virtual void readGameController() override final;
		virtual QVector<JoystickChange> changes() override final;
		
		virtual uint buttonsCount() const override final;
		virtual bool buttonPressed(uint button) const override final;
		virtual QString buttonName(uint button) const override final;
		virtual QStringList buttonsNames() const override final;
		
		virtual uint axesCount() const override final;
		virtual float axisValue(uint axis) const override final;
		virtual QString axisName(uint axis) const override final;
		virtual QStringList axesNames() const override final;
		
		virtual uint povsCount() const override final;
		virtual float povValue(uint pov) const override final;
		virtual QString povName(uint pov) const override final;
		virtual QStringList povsNames() const override final;
		
		virtual void setData(const QString &str, QVariant v) override final;
		virtual void flush() override final;
		
		
	signals:
		void connected();
		void disconnected();
		
		
	private slots:
		void slotNewWsConnection();
		void slotProcessMessage(const QString &msg);
		void slotWsSocketDisconnected();
		
		
	private:
		static QString ethernetLocalIpAddress(bool ipv6 = false);
		static QString data2string(QVariant v);
		
		bool listen(QString *errorMessage = nullptr);
		void close();
		
		QVector<JoystickChange> m_changes;
		
		QString m_name;
		quint16 m_httpPort;
		quint16 m_wsPort;
		uint m_id;
		QString m_resourcesPath;
		
		std::array<bool,128> m_buttons;
		std::array<float,8> m_axes;
		std::array<float,4> m_povs;
		
		bool m_bDestructionInProgress;
		QHttpServer *m_httpServer;
		QWebSocketServer *m_wsServer;
		std::list<QWebSocket*> m_wsClients;
};


#endif

