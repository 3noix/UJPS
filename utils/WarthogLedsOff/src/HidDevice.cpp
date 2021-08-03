#include "HidDevice.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  IS OPERATIONNAL
//  OPEN HID DEVICE
//  OPEN HID DEVICE HELPER
//  COMPUTE REPORT LENGTH
//  WRITE DATA
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
HidDevice::HidDevice(USHORT vid, USHORT pid)
{
	m_hidDevHandle = NULL;
	m_vid = vid;
	m_pid = pid;
	m_reportLength = 0;
}

HidDevice::~HidDevice()
{
	if (m_hidDevHandle != NULL)
		CloseHandle(m_hidDevHandle);
}




// IS OPERATIONNAL ////////////////////////////////////////////////////////////
bool HidDevice::isOperationnal() const
{
	return (m_hidDevHandle != NULL);
}

// OPEN HID DEVICE ////////////////////////////////////////////////////////////
bool HidDevice::openHidDevice()
{
	bool b = this->openHidDeviceHelper();
	if (!b) {m_hidDevHandle = NULL;}
	this->computeReportLength();
	return b;
}

// OPEN HID DEVICE HELPER /////////////////////////////////////////////////////
bool HidDevice::openHidDeviceHelper()
{
	// 1) Get the HID Globally Unique ID from the OS
	GUID HidGuid;
	HidD_GetHidGuid(&HidGuid);
	
	
	// 2) Get an array of structures containing information about all attached and enumerated HIDs
	HDEVINFO HidDevInfo = SetupDiGetClassDevs(&HidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (HidDevInfo == INVALID_HANDLE_VALUE) {return false;}
	
	
	// 3) Step through the attached device list 1 by 1 and examine each of the attached devices.
	// When there are no more entries in the array of structures, the function will return false
	DWORD Index = 0;									// init to first index of array
	SP_DEVICE_INTERFACE_DATA devInfoData;				// Information structure for HID devices
	devInfoData.cbSize = sizeof(devInfoData);			// set to the size of the structure that will contain the device info data
	PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = NULL;	// device info data
	BOOL bResult = FALSE;
	
	do
	{
		// Get information about the HID device with the Index array entry
		bResult = SetupDiEnumDeviceInterfaces(HidDevInfo, 0, &HidGuid, Index, &devInfoData);
		
		// If we run into this condition, then there are no more entries to examine, we might as well return false at point
		if (bResult == FALSE)
		{
			// free memory
			if (detailData != NULL) {free(detailData);}
			SetupDiDestroyDeviceInfoList(HidDevInfo);
			return false;
		}
		
		// 3) Get the size of the DEVICE_INTERFACE_DETAIL_DATA structure.
		// The first call will return an error condition, but we'll get the size of the strucure
		DWORD DataSize;
		SetupDiGetDeviceInterfaceDetail(HidDevInfo, &devInfoData, NULL, 0, &DataSize, NULL);
		
		// allocate memory for the HidDevInfo structure
		if (detailData != NULL) {free(detailData);}
		detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(DataSize);
		detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		
		// 4) Now call the function with the correct size parameter.  This function will return data
		// from one of the array members that step #2 pointed to.  This way we can start to identify the
		// attributes of particular HID devices
		SetupDiGetDeviceInterfaceDetail(HidDevInfo, &devInfoData, detailData, DataSize, NULL, NULL);
		
		// 5) Open a file handle to the device.  Make sure the attibutes specify overlapped transactions
		// or the IN transaction may block the input thread
		m_hidDevHandle = CreateFile(detailData->DevicePath,
									GENERIC_WRITE,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									OPEN_EXISTING,
									FILE_FLAG_OVERLAPPED,
									NULL);
		
		// 6) Get the Device VID & PID to see if it's the device we want
		if (m_hidDevHandle != INVALID_HANDLE_VALUE)
		{
			HIDD_ATTRIBUTES HIDAttrib;
			HIDAttrib.Size = sizeof(HIDAttrib);
			HidD_GetAttributes(m_hidDevHandle, &HIDAttrib);
			//qDebug() << "VID " << ushortToHexaString(HIDAttrib.VendorID) << ", PID " << ushortToHexaString(HIDAttrib.ProductID);
			
			if ((HIDAttrib.VendorID == m_vid) && (HIDAttrib.ProductID == m_pid))
			{
				// free memory
				if (detailData != NULL) {free(detailData);}
				SetupDiDestroyDeviceInfoList(HidDevInfo);
				return true;
			}
			
			// 7) Close the Device Handle because we didn't find the device with the correct VID and PID
			CloseHandle(m_hidDevHandle);
		}
		++Index;
	} while (bResult == TRUE);
	
	// free memory
	if (detailData != NULL) {free(detailData);}
	SetupDiDestroyDeviceInfoList(HidDevInfo);
	return false;
}

// COMPUTE REPORT LENGTH //////////////////////////////////////////////////////
void HidDevice::computeReportLength()
{
	if (m_hidDevHandle == NULL) {return;}
	
	// get a handle to a buffer that describes the device's capabilities.  This line plus the following
	// two lines of code extract the report length the device is claiming to support
	PHIDP_PREPARSED_DATA HidParsedData;
	HidD_GetPreparsedData(m_hidDevHandle, &HidParsedData);
	
	// extract the capabilities info
	HIDP_CAPS Capabilities;
	HidP_GetCaps(HidParsedData, &Capabilities);
	HidD_FreePreparsedData(HidParsedData);
	
	// end
	m_reportLength = Capabilities.OutputReportByteLength;
}

// WRITE DATA /////////////////////////////////////////////////////////////////
bool HidDevice::writeData(quint8 data[], int taille)
{
	Q_UNUSED(taille)
	if (m_hidDevHandle == NULL) {return false;}
	
	HANDLE ReportEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // Create a new event for report capture
	OVERLAPPED HidOverlapped;
	// fill the HidOverlapped structure so that Windows knows which event to cause when the device sends an IN report
	HidOverlapped.hEvent = ReportEvent;
	HidOverlapped.Offset = 0;
	HidOverlapped.OffsetHigh = 0;
	
	BOOL bResult1 = WriteFile(m_hidDevHandle, &data[0], m_reportLength, NULL, (LPOVERLAPPED) &HidOverlapped);
	BOOL bResult2 = WaitForSingleObject(ReportEvent,1000);
	return (bResult1 == TRUE && bResult2 == TRUE);
}

