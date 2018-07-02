#ifndef VIRTUAL_JOYSTICK
#define VIRTUAL_JOYSTICK


#include <array>
#include <QObject>
#include <QString>
#include <QColor>
#include "vJoyModifiedInterface/stdafx.h"
#include "vJoyModifiedInterface/public.h"
#include "AbsoluteOrRelative.h"
#include "virtualjoysticks-global.h"
using uint = unsigned int;

const int g_MAPPING_REPEATER_DURATION = 5; // in seconds

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


class VIRTUALJOYSTICKS_EXPORT VirtualJoystick : public QObject
{
	Q_OBJECT
	
	public:
		VirtualJoystick(uint id, uint nbButtons = 128, uint nbAxes = 8, uint nbPovs = 0, bool bForcedInit = true);
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
		
		bool enableVJoyIfNot();
		void disableVJoy();
		bool isVJoyDeviceFree(uint numDevice);
		static void setVJoyConfigOptions(bool bUseIt, QString exeFilePath);
		
		
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
		
		static uint m_nbInstances;
		static bool m_bUseVJoyConfigExe;
		static QString m_vJoyConfigExeDirPath;
		static QString m_vJoyConfigExeFileName;
};

#endif
