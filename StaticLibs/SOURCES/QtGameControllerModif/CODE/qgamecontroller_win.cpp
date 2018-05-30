/***************************************************************************
 *   Copyright (C) 2014 M Wellings                                         *
 *   info@openforeveryone.co.uk                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "QGameController.h"
#include "QGameController_win_p.h"
#include <QtDebug>

///////////////////////////////////////////////////////////////////////////////
// RESUME
//
//  HEXA STRING
//  CONSTRUCTEUR
//  ENUM JOYSTICKS CALLBACK
//  ENUM OBJECTS CALLBACK
//  READ GAME CONTROLLER
///////////////////////////////////////////////////////////////////////////////


// HEXA STRING ////////////////////////////////////////////////////////////////
QString hexaString(DWORD value)
{
	QString str = QString("%1").arg(QString::number(value,16).toUpper(),8,'0');
	if (str.size() != 8) {return QString();}
	return "VID_" + str.right(4) + "\\&PID_" + str.left(4);
};


QGameControllerPrivate *joysticktoenume; //TODO: Dispense with this global pointer.
LPDIRECTINPUT8 g_pDI = nullptr;


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
QGameControllerPrivate::QGameControllerPrivate(uint id, QGameController *q) :
	q_ptr(q)
{
	m_bFirstRead = true;
	
	ID = id;
	Valid = false;
	nbAxes = 0;
	nbButtons = 0;
	nbPovs = 0;
	
	HRESULT hr;
	g_pJoystick = nullptr;
	
	// Register with DirectInput to get a pointer to an IDirectInput
	if (!g_pDI)
	{
		if (FAILED(hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDI, nullptr)))
			qDebug() << "Error 1";
	}
	
	IDirectInputJoyConfig8* pJoyConfig = nullptr;
	if (FAILED(hr = g_pDI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig))) {qDebug() << "Error 2";}

	DIJOYCONFIG PreferredJoyCfg;
	PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
	DI_ENUM_CONTEXT enumContext;
	enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
	enumContext.bPreferredJoyCfgValid = false;
	if (SUCCEEDED(pJoyConfig->GetConfig(0, &PreferredJoyCfg, DIJC_GUIDINSTANCE))) // This function is expected to fail if no joystick is attached
		enumContext.bPreferredJoyCfgValid = true;
	else
		//qDebug() << "bPreferredJoyCfgValid == false";
	SAFE_RELEASE(pJoyConfig);
	
	joysticktoenume = this;
	enumCounter = 0;
	if (FAILED(hr = g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &enumContext, DIEDFL_ATTACHEDONLY))) {qDebug() << "Error 3";}

	// Make sure we got a joystick
	if (!g_pJoystick)
	{
		//qDebug() << "Joystick not found";
		return;
	}
	
	//qDebug() << "Setting data format";
	if (FAILED(hr = g_pJoystick->SetDataFormat(&c_dfDIJoystick2))) {qDebug() << "Error 4";}
	
	if (FAILED(hr = g_pJoystick->EnumObjects(EnumObjectsCallback, (VOID*)NULL, DIDFT_ALL)))
	{
		qDebug() << "Error 6";
		return;
	}
	
	DIDEVICEINSTANCE joystickinfo;
	joystickinfo.dwSize = sizeof(joystickinfo);
	if (FAILED(hr = g_pJoystick->GetDeviceInfo(&joystickinfo))) {qDebug() << "Error 6";}
	if (hr==DIERR_INVALIDPARAM) {qDebug() << "DIERR_INVALIDPARAM";}
	
	Description = QString::fromUtf16((ushort*)&(joystickinfo.tszProductName));
	HardwareId = hexaString(joystickinfo.guidProduct.Data1);
	Valid = true;
}


// ENUM JOYSTICKS CALLBACK ////////////////////////////////////////////////////
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	Q_UNUSED(pContext)
	//qDebug() << "EnumJoysticksCallback()" << joysticktoenume->enumCounter;
	if (joysticktoenume->enumCounter != joysticktoenume->ID)
	{
		//qDebug() << "Skiping" << joysticktoenume->enumCounter;
		joysticktoenume->enumCounter++;
		return DIENUM_CONTINUE;
	}
	
	//auto pEnumContext = reinterpret_cast<DI_ENUM_CONTEXT*>( pContext );
	//if(pEnumContext->bPreferredJoyCfgValid && !IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
	//{
	//	//Maybe we should mark this as prefered in QGameController
	//}
	
	// Get an interface to this joystick.
	HRESULT hr;
	hr = g_pDI->CreateDevice(pdidInstance->guidInstance, &(joysticktoenume->g_pJoystick), nullptr);
	
	if (FAILED(hr))
	{
		qDebug() << "CreateDevice failed";
		return DIENUM_CONTINUE;
	}
	//qDebug() << "EnumJoysticksCallback() Joystick found";
	return DIENUM_STOP;
}


// ENUM OBJECTS CALLBACK //////////////////////////////////////////////////////
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	Q_UNUSED(pContext)
	//Set the range for axis
	if (pdidoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin = -1000;
		diprg.lMax = +1000;
		if (FAILED(joysticktoenume->g_pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph))) {return DIENUM_STOP;}
	}
	//qDebug() << "JSObject Found";
	
	// Set the UI to reflect what objects the joystick supports
	if (pdidoi->guidType == GUID_XAxis)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Axis found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_YAxis)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Axis found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_ZAxis)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Axis found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_RxAxis)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Axis found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_RyAxis)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Axis found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_RzAxis)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Axis found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_Slider)
	{
		joysticktoenume->DIaxisGIIDs.push_back(pdidoi->guidType);
		//qDebug() << "Slider found";
		joysticktoenume->nbAxes++;
	}
	else if (pdidoi->guidType == GUID_POV)
	{
		//qDebug() << "POV found";
		//We add 4 buttons to represent this pov
		joysticktoenume->nbPovs++;
	}
	else if (pdidoi->guidType == GUID_Button)
	{
		//qDebug() << "Button found";
		joysticktoenume->nbButtons++;
	}
	else if (pdidoi->guidType == GUID_Key)
	{
		//qDebug() << "Key found";
	}
	else if (pdidoi->guidType == GUID_Unknown)
	{
		//qDebug() << "Unknown object found";
	}
	
	// updated at each new button or pov found
	// (the beginning of readGameController is too late for that)
	return DIENUM_CONTINUE;
}


// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void QGameControllerPrivate::readGameController()
{
	Q_Q(QGameController);
	
	if (m_bFirstRead)
	{
		AxesValues    = QVector<float>(nbAxes,0.0f);
		ButtonsValues = QVector<bool>(nbButtons,false);
		PovsValues    = QVector<float>(nbPovs,-1.0f);
	}
	
	// read joystick state
	HRESULT hr;
	DIJOYSTATE2 js; // DInput joystick state
	if (!g_pJoystick) {return;}
	hr = g_pJoystick->Poll();
	if (FAILED(hr))
	{
		hr = g_pJoystick->Acquire();
		while (hr == DIERR_INPUTLOST) {hr = g_pJoystick->Acquire();}
		return;
	}
	if (FAILED(hr = g_pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &js))) {return;}
	
	
	// Axes
	int slider = 0;
	for (uint i=0; i<nbAxes; i++)
	{
		float value = 0;
		GUID guidForThisAxis = DIaxisGIIDs[i];
		
		if (guidForThisAxis == GUID_XAxis)
			value = (float)(js.lX);
		else if (guidForThisAxis == GUID_YAxis)
			value = (float)(js.lY);
		else if (guidForThisAxis == GUID_ZAxis)
			value = (float)(js.lZ);
		else if (guidForThisAxis == GUID_RxAxis)
			value = (float)(js.lRx);
		else if (guidForThisAxis == GUID_RyAxis)
			value = (float)(js.lRy);
		else if (guidForThisAxis == GUID_RzAxis)
			value = (float)(js.lRz);
		else if (guidForThisAxis == GUID_Slider)
		{
			value = (float)(js.rglSlider[slider]);
			slider++;
		}
		
		value = value * 0.001;
		if (value != AxesValues[i] || m_bFirstRead)
		{
			AxesValues[i] = value;
			emit(q->gameControllerAxisEvent(new QGameControllerAxisEvent(ID,i,value)));
		}
	}
	
	
	//Buttons
	for (uint i=0; i<nbButtons; i++)
	{
		bool bPressed = (js.rgbButtons[i] & 0x80);
		if (bPressed != ButtonsValues[i] || m_bFirstRead)
		{
			ButtonsValues[i] = bPressed;
			emit(q->gameControllerButtonEvent(new QGameControllerButtonEvent(ID,i,bPressed)));
		}
	}
	
	
	// POVs
	for (uint i=0; i<nbPovs; i++)
	{
		DWORD povvalue = js.rgdwPOV[i];
		bool bPovCentered = (povvalue==-1u || (LOWORD(povvalue)==0xFFFFu));
		
		float povdegs = -1.0f;
		if (!bPovCentered) {povdegs = (float)povvalue * 0.01;}
		
		if (povdegs != PovsValues[i] || m_bFirstRead)
		{
			PovsValues[i] = povdegs;
			emit(q->gameControllerPovEvent(new QGameControllerPovEvent(ID,i,povdegs)));
		}
	}
	
	m_bFirstRead = false;
}
