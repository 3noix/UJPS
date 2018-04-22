#ifndef REAL_JOYSTICK
#define REAL_JOYSTICK


#include <QObject>
#include "AbstractRealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;
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
		
		virtual uint buttonCount() const override;
		virtual bool buttonPressed(uint button) const override;
		virtual QString buttonName(uint button) const override;
		virtual QStringList buttonsNames() const override;
		
		virtual uint axisCount() const override;
		virtual float axisValue(uint axis) const override;
		virtual QString axisName(uint axis) const override;
		virtual QStringList axesNames() const override;
		
		virtual void setData(const QString &str, QVariant v) override;
		
		
	private slots:
		virtual void slotGameControllerButtonEvent(QGameControllerButtonEvent *event);
		virtual void slotGameControllerAxisEvent(QGameControllerAxisEvent *event);
		
		
	protected:
		QVector<JoystickChange> m_changes;
		
		
	private:
		QGameController *m_controller;
};

#endif
