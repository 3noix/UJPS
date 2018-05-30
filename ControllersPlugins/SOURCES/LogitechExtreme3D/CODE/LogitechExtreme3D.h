#ifndef LOGITECH_EXTREME_3D
#define LOGITECH_EXTREME_3D


#include "RealJoystick.h"
class QGameController;
class QGameControllerButtonEvent;
class QGameControllerAxisEvent;


class LogitechExtreme3D : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		LogitechExtreme3D(QGameController *c);
		LogitechExtreme3D(const LogitechExtreme3D &other) = delete;
		LogitechExtreme3D(LogitechExtreme3D &&other) = delete;
		LogitechExtreme3D& operator=(const LogitechExtreme3D &other) = delete;
		LogitechExtreme3D& operator=(LogitechExtreme3D &&other) = delete;
		~LogitechExtreme3D() = default;
		
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
		QStringList m_buttonsNames;
		QStringList m_axesNames;
		
		
	public:
		static const uint TG    = 0;	// trigger
		static const uint THMB  = 1;	// thumb button
		static const uint SBDL  = 2;	// stick button down left
		static const uint SBDR  = 3;	// stick button down right
		static const uint SBUL  = 4;	// stick button up left
		static const uint SBUR  = 5;	// stick button up right
		static const uint BBUL  = 6;	// base button up left
		static const uint BBUR  = 7;	// base button up right
		static const uint BBML  = 8;	// base button middle left
		static const uint BBMR  = 9;	// base button middle right
		static const uint BBDL  = 10;	// base button down left
		static const uint BBDR  = 11;	// base button down right
		static const uint POVU  = 12;	// POV button up
		static const uint POVR  = 13;	// POV button right
		static const uint POVD  = 14;	// POV button down
		static const uint POVL  = 15;	// POV button left
		
		static const uint JOYX = 0;		// X stick axis
		static const uint JOYY = 1;		// Y stick axis
		static const uint JOYZ = 2;		// Z stick axis
		static const uint THR  = 3;		// throttle axis
};

#endif
