#include "GameControllerXInput.h"
#include "GameControllerEvents.h"
#include "Lim.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME
//
//  CONSTRUCTEUR
//  BYTE TO FLOAT
//  SHORT TO FLOAT
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
//  READ GAME CONTROLLER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
GameControllerXInput::GameControllerXInput(uint id, QObject *parent) : GameController{parent}
{
	m_id = id;
	m_bFirstRead = true;
	m_connected = false;
	
	m_buttonsMapping << XINPUT_GAMEPAD_DPAD_UP;			// 0
	m_buttonsMapping << XINPUT_GAMEPAD_DPAD_RIGHT;		// 1, reordered compared to XInput
	m_buttonsMapping << XINPUT_GAMEPAD_DPAD_DOWN;		// 2, reordered compared to XInput
	m_buttonsMapping << XINPUT_GAMEPAD_DPAD_LEFT;		// 3, reordered compared to XInput
	m_buttonsMapping << XINPUT_GAMEPAD_START;			// 4
	m_buttonsMapping << XINPUT_GAMEPAD_BACK;			// 5
	m_buttonsMapping << XINPUT_GAMEPAD_LEFT_THUMB;		// 6
	m_buttonsMapping << XINPUT_GAMEPAD_RIGHT_THUMB;		// 7
	m_buttonsMapping << XINPUT_GAMEPAD_LEFT_SHOULDER;	// 8
	m_buttonsMapping << XINPUT_GAMEPAD_RIGHT_SHOULDER;	// 9
	m_buttonsMapping << XINPUT_GAMEPAD_A;				// 10
	m_buttonsMapping << XINPUT_GAMEPAD_B;				// 11
	m_buttonsMapping << XINPUT_GAMEPAD_X;				// 12
	m_buttonsMapping << XINPUT_GAMEPAD_Y;				// 13
}

// BYTE TO FLOAT //////////////////////////////////////////////////////////////
float GameControllerXInput::byteToFloat(BYTE b)
{
	float v = b; // initially it is an unsigned char (0->255)
	return lim<float>(v/127.5-1.0f,-1.0f,1.0f); // eventually from -1.0f to 1.0f
}

// SHORT TO FLOAT /////////////////////////////////////////////////////////////
float GameControllerXInput::shortToFloat(SHORT s)
{
	float v = s; // initially it is a short (-32768->32767)
	return lim<float>((v+0.5f)/32767.5f,-1.0f,1.0f); // eventually from -1.0f to 1.0f
}






// DESCRIPTION ////////////////////////////////////////////////////////////////
QString GameControllerXInput::description() {return "Controller (XBOX 360 For Windows)";}
// HARDWARE ID ////////////////////////////////////////////////////////////////
QString GameControllerXInput::hardwareId() {return {};}
// ID /////////////////////////////////////////////////////////////////////////
uint GameControllerXInput::id() {return m_id + 100;}
// IS VALID ///////////////////////////////////////////////////////////////////
bool GameControllerXInput::isValid()
{
	if (m_bFirstRead) {this->readGameController();}
	return m_connected;
}



// AXES COUNT /////////////////////////////////////////////////////////////////
uint GameControllerXInput::axesCount() {return 6;}
// BUTTONS COUNT //////////////////////////////////////////////////////////////
uint GameControllerXInput::buttonsCount() {return 14;}
// POVS COUNT /////////////////////////////////////////////////////////////////
uint GameControllerXInput::povsCount() {return 0;}

// AXIS VALUE /////////////////////////////////////////////////////////////////
float GameControllerXInput::axisValue(uint axis)
{
	if (axis >= 6) {return 0.0f;}
	
	if (axis == 0)      {return byteToFloat(m_state.Gamepad.bLeftTrigger);}
	else if (axis == 1) {return byteToFloat(m_state.Gamepad.bRightTrigger);}
	else if (axis == 2) {return shortToFloat(m_state.Gamepad.sThumbLX);}
	else if (axis == 3) {return shortToFloat(m_state.Gamepad.sThumbLY);}
	else if (axis == 4) {return shortToFloat(m_state.Gamepad.sThumbRX);}
	else if (axis == 5) {return shortToFloat(m_state.Gamepad.sThumbRY);}
	
	return 0.0f;
}

// BUTTON VALUE ///////////////////////////////////////////////////////////////
bool GameControllerXInput::buttonValue(uint button)
{
	if (button >= (uint)m_buttonsMapping.size()) {return false;}
	return (m_state.Gamepad.wButtons & m_buttonsMapping[button]);
}

// POV VALUE //////////////////////////////////////////////////////////////////
float GameControllerXInput::povValue(uint pov)
{
	Q_UNUSED(pov)
	return -1.0f;
}






// READ GAME CONTROLLER ///////////////////////////////////////////////////////
void GameControllerXInput::readGameController()
{
	XINPUT_STATE state;
	memset(&state,0,sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(m_id,&state);
	m_connected = (result == ERROR_SUCCESS);
	if (!m_connected) {return;}
	if (m_state.dwPacketNumber == state.dwPacketNumber && !m_bFirstRead) {return;} // no change
	
	// buttons
	for (uint i=0; i<(uint)m_buttonsMapping.size(); ++i)
	{
		bool wasPressed = (m_state.Gamepad.wButtons & m_buttonsMapping[i]);
		bool isPressed  = (state.Gamepad.wButtons   & m_buttonsMapping[i]);
		if (wasPressed != isPressed || m_bFirstRead)
			emit gameControllerButtonEvent(GameControllerButtonEvent{this->id(),i,isPressed});
	}
	
	// axes
	bool leftTriggerChanged  = (m_state.Gamepad.bLeftTrigger  != state.Gamepad.bLeftTrigger);
	bool rightTriggerChanged = (m_state.Gamepad.bRightTrigger != state.Gamepad.bRightTrigger);
	bool thumbLXChanged = (m_state.Gamepad.sThumbLX != state.Gamepad.sThumbLX);
	bool thumbLYChanged = (m_state.Gamepad.sThumbLY != state.Gamepad.sThumbLY);
	bool thumbRXChanged = (m_state.Gamepad.sThumbRX != state.Gamepad.sThumbRX);
	bool thumbRYChanged = (m_state.Gamepad.sThumbRY != state.Gamepad.sThumbRY);
	
	if (leftTriggerChanged  || m_bFirstRead) {emit gameControllerAxisEvent(GameControllerAxisEvent{this->id(),0,byteToFloat(state.Gamepad.bLeftTrigger)});}
	if (rightTriggerChanged || m_bFirstRead) {emit gameControllerAxisEvent(GameControllerAxisEvent{this->id(),1,byteToFloat(state.Gamepad.bRightTrigger)});}
	if (thumbLXChanged || m_bFirstRead) {emit gameControllerAxisEvent(GameControllerAxisEvent{this->id(),2,shortToFloat(state.Gamepad.sThumbLX)});}
	if (thumbLYChanged || m_bFirstRead) {emit gameControllerAxisEvent(GameControllerAxisEvent{this->id(),3,shortToFloat(state.Gamepad.sThumbLY)});}
	if (thumbRXChanged || m_bFirstRead) {emit gameControllerAxisEvent(GameControllerAxisEvent{this->id(),4,shortToFloat(state.Gamepad.sThumbRX)});}
	if (thumbRYChanged || m_bFirstRead) {emit gameControllerAxisEvent(GameControllerAxisEvent{this->id(),5,shortToFloat(state.Gamepad.sThumbRY)});}
	
	// end
	m_state = state;
	m_bFirstRead = false;
}

