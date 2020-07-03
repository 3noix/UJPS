#include "CURVES/CurvePolynomial3Centered.h"
#include "Lim.h"


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//  RUN
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
CurvePolynomial3Centered::CurvePolynomial3Centered(float leftDZ, float centerDZ, float rightDZ, float curve) : AbstractAxisCurve{}
{
	m_m = 0.02f * leftDZ - 1.0f;
	m_M = 1.0f - 0.02f * rightDZ;
	m_cM = 0.01f * centerDZ;
	m_cm = -m_cM;
	
	m_curveParam = curve;
}

// RUN ////////////////////////////////////////////////////////////////////////
float CurvePolynomial3Centered::run(float in)
{
	if (in < m_m)
	{
		in = -1.0f;
	}
	else if (in < m_cm)
	{
		in = (in-m_cm)/(m_cm-m_m);
		in = m_curveParam * (in*in*in) + (1-m_curveParam) * in;
	}
	else if (in < m_cM)
	{
		in = 0.0f;
	}
	else if (in < m_M)
	{
		in = (in-m_cM)/(m_M-m_cM);
		in = m_curveParam * (in*in*in) + (1-m_curveParam) * in;
	}
	else
	{
		in = 1.0f;
	}
	
	return lim<float>(in,-1.0f,1.0f);
}

