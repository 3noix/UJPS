#ifndef VIRTUAL_JOYSTICK
#define VIRTUAL_JOYSTICK


#include <array>
#include <QObject>
#include <QString>
#include <QColor>
#include "vJoyModifiedInterface/stdafx.h"
#include "vJoyModifiedInterface/public.h"
#include "AbsoluteOrRelative.h"
using uint = unsigned int;

enum class RewriteOrNot
{
	CanRewrite,
	NoRewrite
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
		VirtualJoystick(uint id, uint nbButtons = 128, uint nbAxes = 8, bool bForcedInit = true);
		VirtualJoystick(const VirtualJoystick &other) = delete;
		VirtualJoystick(VirtualJoystick &&other) = delete;
		VirtualJoystick& operator=(const VirtualJoystick &other) = delete;
		VirtualJoystick& operator=(VirtualJoystick &&other) = delete;
		virtual ~VirtualJoystick();
		
		bool setButton(uint button, bool bPressed, RewriteOrNot ron = RewriteOrNot::NoRewrite);
		bool toggleButton(uint button, RewriteOrNot ron = RewriteOrNot::NoRewrite);
		bool getButton(uint button) const;
		bool setAxis(uint axis, float value, RewriteOrNot ron = RewriteOrNot::NoRewrite, TrimOrNot ton = TrimOrNot::NoTrim);
		float getAxis(uint axis) const;
		
		void setButtonLocked(uint button, bool locked);
		void setAxisLocked(uint axis, bool locked);
		void setAxisTrim(uint axis, float trim, AbsoluteOrRelative aor = AbsoluteOrRelative::Absolute);
		
		void resetReport();
		bool flush(bool bEvenIfNoChange = false);
		
		bool enableVJoyIfNot();
		void disableVJoy();
		bool isVJoyDeviceFree(uint numDevice);
		static void setVJoyConfigOptions(bool bUseIt, QString exeFilePath);
		
		
	signals:
		void message(const QString &str, QColor color);
		
		
	private:
		LONG getAxisPrivate(uint axis) const;
		
		uint m_id;
		bool m_reportModified;
		JOYSTICK_POSITION_V2 m_report; // vJoy HID report
		
		std::array<bool,128> m_buttonsLocked;
		std::array<bool,128> m_buttonsNoRewrite;
		std::array<bool,8> m_axesLocked;
		std::array<bool,8> m_axesNoRewrite;
		std::array<LONG,8> m_axesTrim;
		
		static uint m_nbInstances;
		static bool m_bUseVJoyConfigExe;
		static QString m_vJoyConfigExeDirPath;
		static QString m_vJoyConfigExeFileName;
};

#endif
