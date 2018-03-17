#include "JCurve.h"
#include "Lim.h"
#include <math.h>



JCurve::JCurve(float zoom) : AbstractAxisCurve()
{
	m_zoom = zoom;
}



float JCurve::run(float in)
{
	return (-m_zoom*in*in + in + m_zoom*in);
}

