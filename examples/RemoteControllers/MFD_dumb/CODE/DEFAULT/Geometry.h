#ifndef GEOMETRY
#define GEOMETRY


struct Geometry
{
	qreal L0;
	qreal a0;
	qreal a1;
	qreal a2;
	qreal a3;
	
	qreal x0;
	qreal x1;
	qreal x2;
	qreal x3;
	qreal x4;
	qreal x5;
	
	qreal y1;
	qreal y2;
	qreal y3;
	qreal y4;
	qreal y5;
	qreal y6;
};

const Geometry g
{
	141.2,	// L0
	33.1,	// a0
	29.6,	// a1
	16.6,	// a2
	14.7,	// a3
	
	19.0,			// x0
	37.2,			// x1
	37.2+16.7,		// x2
	37.2+16.7*2.0,	// x3
	37.2+16.7*3.0,	// x4
	37.2+16.7*4.0,	// x5
	
	40.0,			// y1
	40.0+15.3,		// y2
	40.0+15.3*2.0,	// y3
	40.0+15.3*3.0,	// y4
	40.0+15.3*4.0,	// y5
	122.0			// y6
};


#endif

