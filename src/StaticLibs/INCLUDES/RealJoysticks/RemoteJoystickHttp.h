#ifndef REMOTE_JOYSTICK_HTTP
#define REMOTE_JOYSTICK_HTTP


#include "AbstractRealJoystick.h"


class RemoteJoystickHttp : public AbstractRealJoystick
{
	public:
		RemoteJoystickHttp(const QString &name, uint id);
		RemoteJoystickHttp(const RemoteJoystickHttp &other) = delete;
		RemoteJoystickHttp(RemoteJoystickHttp &&other) = delete;
		RemoteJoystickHttp& operator=(const RemoteJoystickHttp &other) = delete;
		RemoteJoystickHttp& operator=(RemoteJoystickHttp &&other) = delete;
		virtual ~RemoteJoystickHttp() = default;
		
		QString url() const;
		
		virtual uint id() const override final;
		virtual QString description() const override final;
		virtual QString hardwareId() const override final;
		void readGameController() override final;
		QVector<JoystickChange> changes() override final;
		
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
		
		
	private:
		void addChange(const JoystickChange &ch);
		friend class UjpsHttpServer;
		
		QString m_name;
		uint m_id;
		
		uint m_nbButtons;
		uint m_nbAxes;
		uint m_nbPovs;
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		QStringList m_povsNames;
		std::array<bool,128> m_buttons;
		std::array<float,8> m_axes;
		std::array<float,4> m_povs;
		QVector<JoystickChange> m_changes;
};


#endif

