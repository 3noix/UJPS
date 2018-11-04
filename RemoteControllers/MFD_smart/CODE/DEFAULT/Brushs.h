#ifndef BRUSHS
#define BRUSHS


#include <QBrush>


struct Brushs
{
	QBrush gray1;
	QBrush gray2;
	QBrush gray3;
	QBrush interior;
	QBrush backlit;
	QBrush screw;
	QBrush screen;
	QBrush ledOn;
	QBrush ledOff;
};

const Brushs b
{
	QBrush{QColor{20,20,20}},		// gray1
	QBrush{QColor{50,50,50}},		// gray2
	QBrush{QColor{100,100,100}},	// gray3
	QBrush{QColor{80,90,80}},		// interior
	QBrush{QColor{0,230,0}},		// backlit
	QBrush{QColor{0,0,0}},			// screw
	QBrush{Qt::black},				// screen
	QBrush{QColor{0,190,0}},		// ledOn
	QBrush{QColor{10,60,10}}		// ledOff
};


#endif

