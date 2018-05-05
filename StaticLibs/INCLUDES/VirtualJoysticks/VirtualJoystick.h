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
		VirtualJoystick(uint id, uint nbButtons, bool bForcedInit = true);
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
		uint m_nbButtons;
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
		
		
	public:
		static const uint X       = 0;
		static const uint Y       = 1;
		static const uint Z       = 2;
		static const uint ROTX    = 3;
		static const uint ROTY    = 4;
		static const uint ROTZ    = 5;
		static const uint SLIDER0 = 6;
		static const uint SLIDER1 = 7;
		
		static const uint DX1   = 0;
		static const uint DX2   = 1;
		static const uint DX3   = 2;
		static const uint DX4   = 3;
		static const uint DX5   = 4;
		static const uint DX6   = 5;
		static const uint DX7   = 6;
		static const uint DX8   = 7;
		static const uint DX9   = 8;
		static const uint DX10  = 9;
		static const uint DX11  = 10;
		static const uint DX12  = 11;
		static const uint DX13  = 12;
		static const uint DX14  = 13;
		static const uint DX15  = 14;
		static const uint DX16  = 15;
		static const uint DX17  = 16;
		static const uint DX18  = 17;
		static const uint DX19  = 18;
		static const uint DX20  = 19;
		static const uint DX21  = 20;
		static const uint DX22  = 21;
		static const uint DX23  = 22;
		static const uint DX24  = 23;
		static const uint DX25  = 24;
		static const uint DX26  = 25;
		static const uint DX27  = 26;
		static const uint DX28  = 27;
		static const uint DX29  = 28;
		static const uint DX30  = 29;
		static const uint DX31  = 30;
		static const uint DX32  = 31;
		static const uint DX33  = 32;
		static const uint DX34  = 33;
		static const uint DX35  = 34;
		static const uint DX36  = 35;
		static const uint DX37  = 36;
		static const uint DX38  = 37;
		static const uint DX39  = 38;
		static const uint DX40  = 39;
		static const uint DX41  = 40;
		static const uint DX42  = 41;
		static const uint DX43  = 42;
		static const uint DX44  = 43;
		static const uint DX45  = 44;
		static const uint DX46  = 45;
		static const uint DX47  = 46;
		static const uint DX48  = 47;
		static const uint DX49  = 48;
		static const uint DX50  = 49;
		static const uint DX51  = 50;
		static const uint DX52  = 51;
		static const uint DX53  = 52;
		static const uint DX54  = 53;
		static const uint DX55  = 54;
		static const uint DX56  = 55;
		static const uint DX57  = 56;
		static const uint DX58  = 57;
		static const uint DX59  = 58;
		static const uint DX60  = 59;
		static const uint DX61  = 60;
		static const uint DX62  = 61;
		static const uint DX63  = 62;
		static const uint DX64  = 63;
		static const uint DX65  = 64;
		static const uint DX66  = 65;
		static const uint DX67  = 66;
		static const uint DX68  = 67;
		static const uint DX69  = 68;
		static const uint DX70  = 69;
		static const uint DX71  = 70;
		static const uint DX72  = 71;
		static const uint DX73  = 72;
		static const uint DX74  = 73;
		static const uint DX75  = 74;
		static const uint DX76  = 75;
		static const uint DX77  = 76;
		static const uint DX78  = 77;
		static const uint DX79  = 78;
		static const uint DX80  = 79;
		static const uint DX81  = 80;
		static const uint DX82  = 81;
		static const uint DX83  = 82;
		static const uint DX84  = 83;
		static const uint DX85  = 84;
		static const uint DX86  = 85;
		static const uint DX87  = 86;
		static const uint DX88  = 87;
		static const uint DX89  = 88;
		static const uint DX90  = 89;
		static const uint DX91  = 90;
		static const uint DX92  = 91;
		static const uint DX93  = 92;
		static const uint DX94  = 93;
		static const uint DX95  = 94;
		static const uint DX96  = 95;
		static const uint DX97  = 96;
		static const uint DX98  = 97;
		static const uint DX99  = 98;
		static const uint DX100 = 99;
		static const uint DX101 = 100;
		static const uint DX102 = 101;
		static const uint DX103 = 102;
		static const uint DX104 = 103;
		static const uint DX105 = 104;
		static const uint DX106 = 105;
		static const uint DX107 = 106;
		static const uint DX108 = 107;
		static const uint DX109 = 108;
		static const uint DX110 = 109;
		static const uint DX111 = 110;
		static const uint DX112 = 111;
		static const uint DX113 = 112;
		static const uint DX114 = 113;
		static const uint DX115 = 114;
		static const uint DX116 = 115;
		static const uint DX117 = 116;
		static const uint DX118 = 117;
		static const uint DX119 = 118;
		static const uint DX120 = 119;
		static const uint DX121 = 120;
		static const uint DX122 = 121;
		static const uint DX123 = 122;
		static const uint DX124 = 123;
		static const uint DX125 = 124;
		static const uint DX126 = 125;
		static const uint DX127 = 126;
		static const uint DX128 = 127;
};

#endif
