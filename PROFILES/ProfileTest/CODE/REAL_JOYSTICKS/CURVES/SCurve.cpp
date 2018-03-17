#include "SCurve.h"
#include "Lim.h"
#include <math.h>
#include <QtGlobal>



SCurve::SCurve(float lowerDZ, float centerDZ, float upperDZ, float curve, float zoom) : AbstractAxisCurve()
{
	m_m = lowerDZ + lowerDZ - 1;
	m_M = 1 - upperDZ - upperDZ;
	m_cM = centerDZ;
	m_cm = -m_cM;
	
	m_curve = curve;
	m_zoom = zoom;
}



float SCurve::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_cm)
	{
		if (qAbs(m_curve) < 0.01f)
			in = (in-m_cm) / (m_cm-m_m);
		else
			in = (1.0f-exp((m_cm-in)*m_curve)) / (exp((m_cm-m_m)*m_curve)-1.0f);
	}
	else if (in < m_cM)
	{
		in = 0.0f;
	}
	else if (in < m_M)
	{
		if (qAbs(m_curve) < 0.01f)
		{
			in = (in-m_cM) / (m_M-m_cM);
		}
		else
		{
			in = (exp((in-m_cM)*m_curve)-1.0f) / (exp((m_M-m_cM)*m_curve)-1.0f);
		}
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(pow(1.41,m_zoom)*in,-1.0f,1.0f);
}

