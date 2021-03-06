#ifndef VIRTUAL_JOYSTICK_PRIVATE
#define VIRTUAL_JOYSTICK_PRIVATE


#include <array>
#include "VirtualJoystick.h"
#include "vJoyModifiedInterface/stdafx.h"
#include "vJoyModifiedInterface/public.h"


class VirtualJoystickPrivate : public QObject
{
	Q_OBJECT
	
	public:
		VirtualJoystickPrivate(uint id, bool bForcedInit = true);
		VirtualJoystickPrivate(const VirtualJoystickPrivate &other) = delete;
		VirtualJoystickPrivate(VirtualJoystickPrivate &&other) = delete;
		VirtualJoystickPrivate& operator=(const VirtualJoystickPrivate &other) = delete;
		VirtualJoystickPrivate& operator=(VirtualJoystickPrivate &&other) = delete;
		virtual ~VirtualJoystickPrivate();
		
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
		LONG getAxisPrivate(uint axis) const;
		DWORD getPovPrivate(uint pov) const;
		
		uint m_id;
		bool m_reportModified;
		bool m_bUseDiscretePovs;
		JOYSTICK_POSITION_V2 m_report; // vJoy HID report
		
		std::array<bool,128> m_buttonsLocked;
		std::array<bool,128> m_buttonsHighPrio;
		std::array<bool,8> m_axesLocked;
		std::array<bool,8> m_axesHighPrio;
		std::array<LONG,8> m_axesTrim;
		std::array<bool,4> m_povsLocked;
		std::array<bool,4> m_povsHighPrio;
};

#endif
