#ifndef MFG_CROSSWIND_RUDDER_PEDALS
#define MFG_CROSSWIND_RUDDER_PEDALS


#include "RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;


class MfgCrosswindRudderPedals : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		MfgCrosswindRudderPedals(QGameController *c);
		MfgCrosswindRudderPedals(const MfgCrosswindRudderPedals &other) = delete;
		MfgCrosswindRudderPedals(MfgCrosswindRudderPedals &&other) = delete;
		MfgCrosswindRudderPedals& operator=(const MfgCrosswindRudderPedals &other) = delete;
		MfgCrosswindRudderPedals& operator=(MfgCrosswindRudderPedals &&other) = delete;
		~MfgCrosswindRudderPedals() = default;
		
		QString description() const override final;
		
		uint buttonsCount() const override final;
		bool buttonPressed(uint button) const override final;
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		uint axesCount() const override final;
		float axisValue(uint axis) const override final;
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		
	private slots:
		void slotGameControllerButtonEvent(QGameControllerButtonEvent *event) override final;
		void slotGameControllerAxisEvent(QGameControllerAxisEvent *event) override final;
		
		
	private:
		QStringList m_axesNames;
		
		
	public:
		static const uint RUDDER    = 0;
		static const uint BRK_LEFT  = 1;
		static const uint BRK_RIGHT = 2;
};

#endif
