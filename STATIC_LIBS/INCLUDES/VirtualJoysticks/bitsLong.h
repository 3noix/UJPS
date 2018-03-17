#ifndef BITS_LONG
#define BITS_LONG

// to play bitwise with 32 bits words
// we use qint32 defined in QtGlobal
// ... or LONG to ensure sync with vJoy

//#include <QtGlobal>

LONG one = 1L;
LONG bitLong(uint i)
{
	//Q_ASSERT(i < 32);
	return (one << i%32);
};

/*
const LONG bit0  = bitLong(0);	// 0x00000001L
const LONG bit1  = bitLong(1);	// 0x00000002L
const LONG bit2  = bitLong(2);	// 0x00000004L
const LONG bit3  = bitLong(3);	// 0x00000008L
const LONG bit4  = bitLong(4);	// 0x00000010L
const LONG bit5  = bitLong(5);	// 0x00000020L
const LONG bit6  = bitLong(6);	// 0x00000040L
const LONG bit7  = bitLong(7);	// 0x00000080L
const LONG bit8  = bitLong(8);	// 0x00000100L
const LONG bit9  = bitLong(9);	// 0x00000200L
const LONG bit10 = bitLong(10);	// 0x00000400L
const LONG bit11 = bitLong(11);	// 0x00000800L
const LONG bit12 = bitLong(12);	// 0x00001000L
const LONG bit13 = bitLong(13);	// 0x00002000L
const LONG bit14 = bitLong(14);	// 0x00004000L
const LONG bit15 = bitLong(15);	// 0x00008000L
const LONG bit16 = bitLong(16);	// 0x00010000L
const LONG bit17 = bitLong(17);	// 0x00020000L
const LONG bit18 = bitLong(18);	// 0x00040000L
const LONG bit19 = bitLong(19);	// 0x00080000L
const LONG bit20 = bitLong(20);	// 0x00100000L
const LONG bit21 = bitLong(21);	// 0x00200000L
const LONG bit22 = bitLong(22);	// 0x00400000L
const LONG bit23 = bitLong(23);	// 0x00800000L
const LONG bit24 = bitLong(24);	// 0x01000000L
const LONG bit25 = bitLong(25);	// 0x02000000L
const LONG bit26 = bitLong(26);	// 0x04000000L
const LONG bit27 = bitLong(27);	// 0x08000000L
const LONG bit28 = bitLong(28);	// 0x10000000L
const LONG bit29 = bitLong(29);	// 0x20000000L
const LONG bit30 = bitLong(30);	// 0x40000000L
const LONG bit31 = bitLong(31);	// 0x80000000L
*/

#endif

