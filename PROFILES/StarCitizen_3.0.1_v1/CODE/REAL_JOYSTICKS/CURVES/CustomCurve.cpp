#include "CustomCurve.h"
#include "Lim.h"
#include "ExceptionBadCustomCurve.h"
#include <math.h>
#include <QtGlobal>

const float EPSILON = 1E-6;


CustomCurve::CustomCurve(const std::vector<float> &points) : AbstractAxisCurve()
{
	int m = points.size();
	if (m%2 != 0 || m == 0) {throw ExceptionBadCustomCurve{};}
	
	// the list of points must be defined as follow: {x1,y1, x2,y2, x3,y3, ...}
	int n = m / 2;
	m_x.resize(n);
	m_y.resize(n);
	
	for (int i=0; i<n; ++i)
	{
		m_x[i] = points[2*i];
		m_y[i] = points[2*i+1];
	}
}



float CustomCurve::run(float in)
{
	float a = linear_interpolation(in,m_x,m_y);
	return lim<float>(a,-1.0f,1.0f);
}

float CustomCurve::linear_interpolation(float in, const std::vector<float> &x, const std::vector<float> &y)
{
	int n = x.size();
	
	// constant extrapolation before
	if (in <= x[0])
	{
		return y[0];
	}
	// constant extrapolation after
	else if (in >= x[n-1])
	{
		return y[n-1];
	}
	// linear interpolation between
	else
	{
		int max = n - 1;
		int min = 0;
		int cour = 0;
		
		do
		{
			cour = (min + max) / 2;
			if (in < x[cour]) {max = cour;}
			else {min = cour;}
		} while (max != (min+1));
		
		float denom = x[min+1] - x[min];
		if (qAbs(denom) < EPSILON) {denom = EPSILON;}
		return (y[min] + (in - x[min]) * (y[min+1] - y[min]) / denom);
	}
}

