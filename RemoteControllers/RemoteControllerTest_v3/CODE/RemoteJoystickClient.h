#ifndef REMOTE_JOYSTICK_CLIENT
#define REMOTE_JOYSTICK_CLIENT


#include "AbstractRemoteJoystickClient.h"


class RemoteJoystickClient : public AbstractRemoteJoystickClient
{
	Q_OBJECT
	
	public:
		RemoteJoystickClient(QObject *parent = nullptr);
		RemoteJoystickClient(const RemoteJoystickClient &other) = delete;
		RemoteJoystickClient(RemoteJoystickClient &&other) = delete;
		RemoteJoystickClient& operator=(const RemoteJoystickClient &other) = delete;
		RemoteJoystickClient& operator=(RemoteJoystickClient &&other) = delete;
		virtual ~RemoteJoystickClient() = default;
		
		QString description() const override final;
		
		quint8 buttonsCount() const override final;
		QStringList buttonsNames() const override final;
		quint8 axesCount() const override final;
		QStringList axesNames() const override final;
		quint8 povsCount() const override final;
		QStringList povsNames() const override final;
		
		void setData(const QString &prop, QVariant v) override final;
		
		
	signals:
		void signalSetData(const QString &prop, QVariant v);
};

#endif

