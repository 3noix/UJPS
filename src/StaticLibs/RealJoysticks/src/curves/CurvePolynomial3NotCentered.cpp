#include "CurvePolynomial3NotCentered.h"
#include "../../../../../include/Other/Lim.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  RUN
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurvePolynomial3NotCentered::CurvePolynomial3NotCentered(float leftDZ, float rightDZ, float curve) : AbstractAxisCurve{}
{
	m_m = 0.02f * leftDZ - 1.0f;
	m_M = 1.0f - 0.02f * rightDZ;
	
	m_curveParam = curve;
}

// RUN ////////////////////////////////////////////////////////////////////////
float CurvePolynomial3NotCentered::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_M)
	{
		in = (in-m_m) / (m_M-m_m);
		in = m_curveParam * (in*in*in) + (1-m_curveParam) * in;
		in = 2.0f * in - 1.0f;
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(in,-1.0f,1.0f);
}

