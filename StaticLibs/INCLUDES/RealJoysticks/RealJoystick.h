#ifndef REAL_JOYSTICK
#define REAL_JOYSTICK


#include <QObject>
#include "AbstractRealJoystick.h"
#include "VirtualPovDefinition.h"
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
		
		virtual uint povsCount() const override;
		virtual float povValue(uint pov) const override;
		virtual QString povName(uint pov) const override;
		virtual QStringList povsNames() const override;
		
		virtual void setData(const QString &str, QVariant v) override;
		virtual void flush() override;
		
		
	private slots:
		virtual void slotGameControllerAxisEvent(QGameControllerAxisEvent *event);
		virtual void slotGameControllerButtonEvent(QGameControllerButtonEvent *event);
		virtual void slotGameControllerPovEvent(QGameControllerPovEvent *event);
		
		
	protected:
		void addVirtualPov(uint nUp, uint nRight, uint nDown, uint nLeft, const QString &povName);
		QVector<JoystickChange> m_changes;
		
		
	private:
		static float buttonsToPov(bool bUp, bool bRight, bool bDown, bool bLeft);
		uint buttonMapsPov(uint button) const;
		
		QGameController *m_controller;
		bool m_bTransformPovInto4Buttons;
		bool m_bTransform4ButtonsIntoPov;
		QVector<float> m_realPovsAngles; // to keep track of the last values
		QVector<VirtualPovDefinition> m_virtualPovsDef;
};

#endif
