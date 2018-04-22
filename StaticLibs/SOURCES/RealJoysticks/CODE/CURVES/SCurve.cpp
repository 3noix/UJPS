#include "CURVES/SCurve.h"
#include "Lim.h"
#include <math.h>
#include <QtGlobal>



SCurve::SCurve(float leftDZ, float centerDZ, float rightDZ, float curveParam, float zoom) : AbstractAxisCurve()
{
	m_m = leftDZ + leftDZ - 1;
	m_M = 1 - rightDZ - rightDZ;
	m_cM = centerDZ;
	m_cm = -m_cM;
	
	m_curveParam = curveParam;
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
		if (qAbs(m_curveParam) < 0.01f)
			in = (in-m_cm) / (m_cm-m_m);
		else
			in = (1.0f-exp((m_cm-in)*m_curveParam)) / (exp((m_cm-m_m)*m_curveParam)-1.0f);
	}
	else if (in < m_cM)
	{
		in = 0.0f;
	}
	else if (in < m_M)
	{
		if (qAbs(m_curveParam) < 0.01f)
		{
			in = (in-m_cM) / (m_M-m_cM);
		}
		else
		{
			in = (exp((in-m_cM)*m_curveParam)-1.0f) / (exp((m_M-m_cM)*m_curveParam)-1.0f);
		}
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(pow(1.41,m_zoom)*in,-1.0f,1.0f);
}

