#include "CurveExpNotCentered.h"
#include "../../../../../include/Other/Lim.h"
#include <math.h>
#include <QtGlobal>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  RUN
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurveExpNotCentered::CurveExpNotCentered(float leftDZ, float rightDZ, float curveParam, float zoom) : AbstractAxisCurve{}
{
	m_m = 0.02f * leftDZ - 1.0f;
	m_M = 1.0f - 0.02f * rightDZ;
	
	m_curveParam = curveParam;
	m_zoom = zoom;
}

// RUN ////////////////////////////////////////////////////////////////////////
float CurveExpNotCentered::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_M)
	{
		if (qAbs(m_curveParam) < 0.01f)
		{
			in = (in-m_m) / (m_M-m_m);
		}
		else
		{
			in = (exp(m_curveParam*(in-m_m)/(m_M-m_m))-1.0f) / (exp(m_curveParam)-1.0f);
		}
		in = 2.0f * in - 1.0f;
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(pow(1.41,m_zoom)*in,-1.0f,1.0f);
}

