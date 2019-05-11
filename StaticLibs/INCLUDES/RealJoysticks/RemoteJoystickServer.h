#ifndef REMOTE_JOYSTICK_SERVER
#define REMOTE_JOYSTICK_SERVER


#include <QObject>
#include <QColor>
#include "AbstractRealJoystick.h"

class QTcpServer;
class QNetworkSession;
class QTcpSocket;


class RemoteJoystickServer : public QObject, public AbstractRealJoystick
{
	Q_OBJECT
	Q_INTERFACES(AbstractRealJoystick)
	
	
	public:
		RemoteJoystickServer(const QString &name, int portNumber, uint id, int msecTimeOut = 10000);
		RemoteJoystickServer(const RemoteJoystickServer &other) = delete;
		RemoteJoystickServer(RemoteJoystickServer &&other) = delete;
		RemoteJoystickServer& operator=(const RemoteJoystickServer &other) = delete;
		RemoteJoystickServer& operator=(RemoteJoystickServer &&other) = delete;
		virtual ~RemoteJoystickServer();
		
		bool isConnected() const;
		
		virtual uint id() const override final;
		virtual QString description() const override;
		virtual QString hardwareId() const override final;
		void readGameController() override final;
		QVector<JoystickChange> changes() override final;
		
		virtual uint buttonsCount() const override;
		virtual bool buttonPressed(uint button) const override;
		virtual QString buttonName(uint button) const override;
		virtual QStringList buttonsNames() const override;
		
		virtual uint axesCount() const override;
		virtual float axisValue(uint axis) const override;
		virtual QString axisName(uint axis) const override;
		virtual QStringList axesNames() const override;
		
		virtual uint povsCount() const override;
		virtual float povValue(uint pov) const override;
		virtual QString povName(uint pov) const override;
		virtual QStringList povsNames() const override;
		
		virtual void setData(const QString &str, QVariant v) override;
		virtual void flush() override;
		
		
	signals:
		void message(const QString &str, QColor color);
		void connected();
		void disconnected();
		
		
	private slots:
		void slotSessionOpened();
		void slotNewConnection();
		void slotReceiveData();
		void slotRemoveConnection();
		
		
	protected:
		QVector<JoystickChange> m_changes;
		
		
	private:
		QString m_name;
		int m_portNumber;
		uint m_id;
		int m_msecTimeOut;
		bool m_bConnected;
		bool m_bDestructionInProgress;
		
		quint16 m_dataSize;
		qint8 m_messageType;
		
		bool m_initialized;
		bool m_initFailed;
		uint m_nbButtons;
		uint m_nbAxes;
		uint m_nbPovs;
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
		std::array<bool,128> m_buttons;
		std::array<float,8> m_axes;
		std::array<float,4> m_povs;
		
		QNetworkSession *m_networkSession;
		QTcpServer *m_tcpServer;
		QTcpSocket *m_tcpSocket;
};


#endif

