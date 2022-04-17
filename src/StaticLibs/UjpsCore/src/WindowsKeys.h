#ifndef KEYS
#define KEYS


using uint = unsigned int;
// file established using this data: https://msdn.microsoft.com/fr-fr/library/windows/desktop/dd375731(v=vs.85).aspx
// or search "virtual key code" on microsoft msdn
// but here, only the codes that are fully compatible with hardware scan codes are listed


namespace Keys
{
	// modifiers
	const uint Key_LShift = 0xA0; // VK_LSHIFT
	const uint Key_RShift = 0xA1; // VK_RSHIFT
	const uint Key_LCtrl  = 0xA2; // VK_LCONTROL
	const uint Key_LAlt	  = 0xA4; // VK_LMENU
	
	// special keys
	const uint Key_Backspace = 0x08; // VK_BACK
	const uint Key_Tab       = 0x09; // VK_TAB
	const uint Key_Return    = 0x0D; // VK_RETURN
	const uint Key_CapsLock  = 0x14; // VK_CAPITAL
	const uint Key_Escape    = 0x1B; // VK_ESCAPE
	const uint Key_Space     = 0x20; // VK_SPACE
	
	// digits (the ones that are above letters)
	const uint Key_0 = 0x30;
	const uint Key_1 = 0x31;
	const uint Key_2 = 0x32;
	const uint Key_3 = 0x33;
	const uint Key_4 = 0x34;
	const uint Key_5 = 0x35;
	const uint Key_6 = 0x36;
	const uint Key_7 = 0x37;
	const uint Key_8 = 0x38;
	const uint Key_9 = 0x39;

	// digits (the ones from the numpad)
	const uint Key_Numpad0 = 0x60; // VK_NUMPAD0
	const uint Key_Numpad1 = 0x61; // VK_NUMPAD1
	const uint Key_Numpad2 = 0x62; // VK_NUMPAD2
	const uint Key_Numpad3 = 0x63; // VK_NUMPAD3
	const uint Key_Numpad4 = 0x64; // VK_NUMPAD4
	const uint Key_Numpad5 = 0x65; // VK_NUMPAD5
	const uint Key_Numpad6 = 0x66; // VK_NUMPAD6
	const uint Key_Numpad7 = 0x67; // VK_NUMPAD7
	const uint Key_Numpad8 = 0x68; // VK_NUMPAD8
	const uint Key_Numpad9 = 0x69; // VK_NUMPAD9
	const uint Key_NumpadMult = 0x6A; // VK_MULTIPLY
	const uint Key_NumpadAdd  = 0x6B; // VK_ADD
	const uint Key_NumpadSub  = 0x6D; // VK_SUBTRACT
	const uint Key_NumpadPt   = 0x6E; // VK_DECIMAL
	
	// letters
	const uint Key_A = 0x41;
	const uint Key_B = 0x42;
	const uint Key_C = 0x43;
	const uint Key_D = 0x44;
	const uint Key_E = 0x45;
	const uint Key_F = 0x46;
	const uint Key_G = 0x47;
	const uint Key_H = 0x48;
	const uint Key_I = 0x49;
	const uint Key_J = 0x4A;
	const uint Key_K = 0x4B;
	const uint Key_L = 0x4C;
	const uint Key_M = 0x4D;
	const uint Key_N = 0x4E;
	const uint Key_O = 0x4F;
	const uint Key_P = 0x50;
	const uint Key_Q = 0x51;
	const uint Key_R = 0x52;
	const uint Key_S = 0x53;
	const uint Key_T = 0x54;
	const uint Key_U = 0x55;
	const uint Key_V = 0x56;
	const uint Key_W = 0x57;
	const uint Key_X = 0x58;
	const uint Key_Y = 0x59;
	const uint Key_Z = 0x5A;
	
	// F keys
	const uint Key_F1  = 0x70; // VK_F1
	const uint Key_F2  = 0x71; // VK_F2
	const uint Key_F3  = 0x72; // VK_F3
	const uint Key_F4  = 0x73; // VK_F4
	const uint Key_F5  = 0x74; // VK_F5
	const uint Key_F6  = 0x75; // VK_F6
	const uint Key_F7  = 0x76; // VK_F7
	const uint Key_F8  = 0x77; // VK_F8
	const uint Key_F9  = 0x78; // VK_F9
	const uint Key_F10 = 0x79; // VK_F10
	const uint Key_F11 = 0x7A; // VK_F11
	const uint Key_F12 = 0x7B; // VK_F12
	const uint Key_F13 = 0x7C; // VK_F13
	const uint Key_F14 = 0x7D; // VK_F14
	const uint Key_F15 = 0x7E; // VK_F15
	const uint Key_F16 = 0x7F; // VK_F16
	const uint Key_F17 = 0x80; // VK_F17
	const uint Key_F18 = 0x81; // VK_F18
	const uint Key_F19 = 0x82; // VK_F19
	const uint Key_F20 = 0x83; // VK_F20
	const uint Key_F21 = 0x84; // VK_F21
	const uint Key_F22 = 0x85; // VK_F22
	const uint Key_F23 = 0x86; // VK_F23
	const uint Key_F24 = 0x87; // VK_F24
}


#endif

