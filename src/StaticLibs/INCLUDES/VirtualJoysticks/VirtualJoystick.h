#ifndef VIRTUAL_JOYSTICK
#define VIRTUAL_JOYSTICK


#include <QObject>
#include <QString>
#include <QColor>
#include "AbsoluteOrRelative.h"
using uint = unsigned int;
class VirtualJoystickPrivate;


enum class Priority
{
	Low,
	High
};


enum class TrimOrNot
{
	UseTrim,
	NoTrim
};


class VirtualJoystick : public QObject
{
	Q_OBJECT
	
	public:
		VirtualJoystick(uint id, bool bForcedInit = true);
		VirtualJoystick(const VirtualJoystick &other) = delete;
		VirtualJoystick(VirtualJoystick &&other) = delete;
		VirtualJoystick& operator=(const VirtualJoystick &other) = delete;
		VirtualJoystick& operator=(VirtualJoystick &&other) = delete;
		virtual ~VirtualJoystick();
		
		bool setButton(uint button, bool bPressed, Priority p = Priority::High);
		bool toggleButton(uint button, Priority p = Priority::High);
		bool getButton(uint button) const;
		bool setAxis(uint axis, float value, Priority p = Priority::High, TrimOrNot ton = TrimOrNot::NoTrim);
		float getAxis(uint axis) const;
		bool setPov(uint pov, float value, Priority p = Priority::High);
		float getPov(uint pov) const;
		
		void setButtonLocked(uint button, bool locked);
		void setAxisLocked(uint axis, bool locked);
		void setAxisTrim(uint axis, float trim, AbsoluteOrRelative aor = AbsoluteOrRelative::Absolute);
		void setPovLocked(uint pov, bool locked);
		
		void resetReport();
		bool flush(bool bEvenIfNoChange = false);
		bool isVJoyDeviceFree(uint numDevice);
		
		
	signals:
		void message(const QString &str, QColor color);
		
		
	private:
		VirtualJoystickPrivate *m_pimpl;
};

#endif
