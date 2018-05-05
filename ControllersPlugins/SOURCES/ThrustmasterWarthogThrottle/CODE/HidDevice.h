#ifndef HID_DEVICE
#define HID_DEVICE


#include <QtGlobal>
#include <windows.h>
#include <setupapi.h>

extern "C" {
#include <hidsdi.h>
#include <hidpi.h>
}


class HidDevice
{
	public:
		HidDevice(USHORT vid, USHORT pid);
		HidDevice(const HidDevice &other) = delete;
		HidDevice(HidDevice &&other) = delete;
		HidDevice& operator=(const HidDevice &other) = delete;
		HidDevice& operator=(HidDevice &&other) = delete;
		~HidDevice();
		
		
		bool isOperationnal() const;
		bool openHidDevice();
		bool writeData(quint8 data[], int taille);
		
		
	private:
		bool openHidDeviceHelper();
		void computeReportLength();
		//QString ushortToHexaString(USHORT value);
		
		HANDLE m_hidDevHandle;
		USHORT m_vid;
		USHORT m_pid;
		DWORD m_reportLength;
};


#endif

