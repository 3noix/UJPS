#ifndef KEYS
#define KEYS


using uint = unsigned int;
// file established using this data: https://msdn.microsoft.com/fr-fr/library/windows/desktop/dd375731(v=vs.85).aspx
// or search "virtual key code" on microsoft msdn
// but here, only the codes that are fully compatible with hardware scan codes are listed


namespace Keys
{
	// modifiers
	const uint Key_LShift = 0xA0;
	const uint Key_RShift = 0xA1;
	const uint Key_LCtrl  = 0xA2;
	const uint Key_LAlt	  = 0xA4;
	
	// special keys
	const uint Key_Backspace = 0x08;
	const uint Key_Tab       = 0x09;
	const uint Key_Return    = 0x0D;
	const uint Key_CapsLock  = 0x14;
	const uint Key_Escape    = 0x1B;
	const uint Key_Space     = 0x20;
	
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
	const uint Key_F1  = 0x70;
	const uint Key_F2  = 0x71;
	const uint Key_F3  = 0x72;
	const uint Key_F4  = 0x73;
	const uint Key_F5  = 0x74;
	const uint Key_F6  = 0x75;
	const uint Key_F7  = 0x76;
	const uint Key_F8  = 0x77;
	const uint Key_F9  = 0x78;
	const uint Key_F10 = 0x79;
	const uint Key_F11 = 0x7A;
	const uint Key_F12 = 0x7B;
}


#endif

