#include "GameControllerDirectInput.h"
#include "GameControllerEvents.h"
#include <QtDebug>


///////////////////////////////////////////////////////////////////////////////
// RESUME
//
//  CONSTRUCTEUR
//
//  DESCRIPTION
//  HARDWARE ID
//  ID
//  IS VALID
//
//  AXES COUNT
//  BUTTONS COUNT
//  POVS COUNT
//  AXIS VALUE
//  BUTTON VALUE
//  POV VALUE
//
//  ENUM JOYSTICKS CALLBACK
//  ENUM OBJECTS CALLBACK
//  READ GAME CONTROLLER
//  HEXA STRING
///////////////////////////////////////////////////////////////////////////////


GameControllerDirectInput *joysticktoenume; //TODO: Dispense with this global pointer.
LPDIRECTINPUT8 g_pDI = nullptr;


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
GameControllerDirectInput::GameControllerDirectInput(uint id, QObject *parent) : GameController{parent}
{
	m_bFirstRead = true;
	
	m_id = id;
	m_valid = false;
	m_nbAxes = 0;
	m_nbButtons = 0;
	m_nbPovs = 0;
	
	HRESULT hr;
	m_pJoystick = nullptr;
	
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
	if (pJoyConfig)
	{
		pJoyConfig->Release();
		pJoyConfig = nullptr;
	}
	
	joysticktoenume = this;
	m_enumCounter = 0;
	if (FAILED(hr = g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &enumContext, DIEDFL_ATTACHEDONLY))) {qDebug() << "Error 3";}

	// Make sure we got a joystick
	if (!m_pJoystick)
	{
		//qDebug() << "Joystick not found";
		return;
	}
	
	//qDebug() << "Setting data format";
	if (FAILED(hr = m_pJoystick->SetDataFormat(&c_dfDIJoystick2))) {qDebug() << "Error 4";}
	
	if (FAILED(hr = m_pJoystick->EnumObjects(EnumObjectsCallback, (VOID*)NULL, DIDFT_ALL)))
	{
		qDebug() << "Error 6";
		return;
	}
	
	DIDEVICEINSTANCE joystickinfo;
	joystickinfo.dwSize = sizeof(joystickinfo);
	if (FAILED(hr = m_pJoystick->GetDeviceInfo(&joystickinfo))) {qDebug() << "Error 6";}
	if (hr==DIERR_INVALIDPARAM) {qDebug() << "DIERR_INVALIDPARAM";}
	
	m_description = QString::fromUtf16((ushort*)&(joystickinfo.tszProductName));
	m_hardwareId = GameControllerDirectInput::hexaString(joystickinfo.guidProduct.Data1);
	m_valid = true;
}



// DESCRIPTION ////////////////////////////////////////////////////////////////
QString GameControllerDirectInput::description() {return m_description;}
// HARDWARE ID ////////////////////////////////////////////////////////////////
QString GameControllerDirectInput::hardwareId() {return m_hardwareId;}
// ID /////////////////////////////////////////////////////////////////////////
uint GameControllerDirectInput::id() {return m_id;}
// IS VALID ///////////////////////////////////////////////////////////////////
bool GameControllerDirectInput::isValid() {return m_valid;}



// AXES COUNT /////////////////////////////////////////////////////////////////
uint GameControllerDirectInput::axesCount() {return m_nbAxes;}
// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint GameControllerDirectInput::buttonsCount() {return m_nbButtons;}
// POVS COUNT /////////////////////////////////////////////////////////////////
uint GameControllerDirectInput::povsCount() {return m_nbPovs;}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float GameControllerDirectInput::axisValue(uint axis)
{
	if (axis >= m_nbAxes) {return 0.0f;}
	return m_axesValues[axis];
}

// BUTTON VALUE ///////////////////////////////////////////////////////////////
bool GameControllerDirectInput::buttonValue(uint button)
{
	if (button >= m_nbButtons) {return false;}
	return m_buttonsValues[button];
}

// POV VALUE //////////////////////////////////////////////////////////////////
float GameControllerDirectInput::povValue(uint pov)
{
	if (pov >= m_nbPovs) {return 0.0f;}
	return m_povsValues[pov];
}




// ENUM JOYSTICKS CALLBACK ////////////////////////////////////////////////////
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	Q_UNUSED(pContext)
	//qDebug() << "EnumJoysticksCallback()" << joysticktoenume->m_enumCounter;
	if (joysticktoenume->m_enumCounter != joysticktoenume->m_id)
	{
		//qDebug() << "Skiping" << joysticktoenume->m_enumCounter;
		joysticktoenume->m_enumCounter++;
		return DIENUM_CONTINUE;
	}
	
	//auto pEnumContext = reinterpret_cast<DI_ENUM_CONTEXT*>( pContext );
	//if(pEnumContext->bPreferredJoyCfgValid && !IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
	//{
	//	//Maybe we should mark this as prefered in GameController
	//}
	
	// Get an interface to this joystick.
	HRESULT hr;
	hr = g_pDI->CreateDevice(pdidInstance->guidInstance, &(joysticktoenume->m_pJoystick), nullptr);
	
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
		if (FAILED(joysticktoenume->m_pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph))) {return DIENUM_STOP;}
	}
	//qDebug() << "JSObject Found";
	
	// Set the UI to reflect what objects the joystick supports
	if (pdidoi->guidType == GUID_XAxis)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Axis found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_YAxis)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Axis found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_ZAxis)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Axis found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_RxAxis)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Axis found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_RyAxis)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Axis found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_RzAxis)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Axis found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_Slider)
	{
		joysticktoenume->m_DIaxisGIIDs << pdidoi->guidType;
		//qDebug() << "Slider found";
		joysticktoenume->m_nbAxes++;
	}
	else if (pdidoi->guidType == GUID_POV)
	{
		//qDebug() << "POV found";
		//We add 4 buttons to represent this pov
		joysticktoenume->m_nbPovs++;
	}
	else if (pdidoi->guidType == GUID_Button)
	{
		//qDebug() << "Button found";
		joysticktoenume->m_nbButtons++;
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
void GameControllerDirectInput::readGameController()
{
	if (m_bFirstRead)
	{
		m_axesValues    = QVector<float>(m_nbAxes,0.0f);
		m_buttonsValues = QVector<bool>(m_nbButtons,false);
		m_povsValues    = QVector<float>(m_nbPovs,-1.0f);
	}
	
	// read joystick state
	HRESULT hr;
	DIJOYSTATE2 js; // DInput joystick state
	if (!m_pJoystick) {return;}
	hr = m_pJoystick->Poll();
	if (FAILED(hr))
	{
		hr = m_pJoystick->Acquire();
		while (hr == DIERR_INPUTLOST) {hr = m_pJoystick->Acquire();}
		return;
	}
	if (FAILED(hr = m_pJoystick->GetDeviceState(sizeof(DIJOYSTATE2), &js))) {return;}
	
	
	// Axes
	int slider = 0;
	for (uint i=0; i<m_nbAxes; i++)
	{
		float value = 0;
		GUID guidForThisAxis = m_DIaxisGIIDs[i];
		
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
		if (value != m_axesValues[i] || m_bFirstRead)
		{
			m_axesValues[i] = value;
			emit gameControllerAxisEvent(new GameControllerAxisEvent{m_id,i,value});
		}
	}
	
	
	//Buttons
	for (uint i=0; i<m_nbButtons; i++)
	{
		bool bPressed = (js.rgbButtons[i] & 0x80);
		if (bPressed != m_buttonsValues[i] || m_bFirstRead)
		{
			m_buttonsValues[i] = bPressed;
			emit gameControllerButtonEvent(new GameControllerButtonEvent{m_id,i,bPressed});
		}
	}
	
	
	// POVs
	for (uint i=0; i<m_nbPovs; i++)
	{
		DWORD povvalue = js.rgdwPOV[i];
		bool bPovCentered = (povvalue==-1u || (LOWORD(povvalue)==0xFFFFu));
		
		float povdegs = -1.0f;
		if (!bPovCentered) {povdegs = (float)povvalue * 0.01;}
		
		if (povdegs != m_povsValues[i] || m_bFirstRead)
		{
			m_povsValues[i] = povdegs;
			emit gameControllerPovEvent(new GameControllerPovEvent{m_id,i,povdegs});
		}
	}
	
	m_bFirstRead = false;
}

// HEXA STRING ////////////////////////////////////////////////////////////////
QString GameControllerDirectInput::hexaString(DWORD value)
{
	QString str = QString("%1").arg(QString::number(value,16).toUpper(),8,'0');
	if (str.size() != 8) {return QString();}
	return "VID_" + str.right(4) + "\\&PID_" + str.left(4);
}


