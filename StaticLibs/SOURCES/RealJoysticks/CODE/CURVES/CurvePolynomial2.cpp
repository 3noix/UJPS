#include "CURVES/CurvePolynomial2.h"
#include "Lim.h"
#include <math.h>



CurvePolynomial2::CurvePolynomial2(float zoom) : AbstractAxisCurve()
{
	m_zoom = zoom;
}



float CurvePolynomial2::run(float in)
{
	return (-m_zoom*in*in + in + m_zoom*in);
}

