#ifndef REAL_JOYSTICK
#define REAL_JOYSTICK


#include <QObject>
#include "AbstractRealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;
class QGameControllerPovEvent;
class RealJoysticksManager;


class RealJoystick : public QObject, public AbstractRealJoystick
{
	Q_OBJECT
	Q_INTERFACES(AbstractRealJoystick)
	friend class RealJoysticksManager;
	
	protected:
		RealJoystick(QGameController *c);
		
		
	public:
		RealJoystick(const RealJoystick &other) = delete;
		RealJoystick(RealJoystick &&other) = delete;
		RealJoystick& operator=(const RealJoystick &other) = delete;
		RealJoystick& operator=(RealJoystick &&other) = delete;
		virtual ~RealJoystick();
		
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
		
		virtual void setData(const QString &str, QVariant v) override;
		virtual void flush() override;
		
		
	private slots:
		virtual void slotGameControllerAxisEvent(QGameControllerAxisEvent *event);
		virtual void slotGameControllerButtonEvent(QGameControllerButtonEvent *event);
		virtual void slotGameControllerPovEvent(QGameControllerPovEvent *event);
		
		
	protected:
		QVector<JoystickChange> m_changes;
		
		
	private:
		QGameController *m_controller;
		QVector<float> m_povsAngles; // to keep track of the last values
};

#endif
