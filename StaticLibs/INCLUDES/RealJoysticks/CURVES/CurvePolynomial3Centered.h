#ifndef CURVE_POLYNOMIAL_3_CENTERED
#define CURVE_POLYNOMIAL_3_CENTERED


#include "AbstractAxisCurve.h"


class CurvePolynomial3Centered : public AbstractAxisCurve
{
	public:
		CurvePolynomial3Centered(float leftDZ = 0.0f, float centerDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f);
		CurvePolynomial3Centered(const CurvePolynomial3Centered &other) = delete;
		CurvePolynomial3Centered(CurvePolynomial3Centered &&other) = delete;
		CurvePolynomial3Centered& operator=(const CurvePolynomial3Centered &other) = delete;
		CurvePolynomial3Centered& operator=(CurvePolynomial3Centered &&other) = delete;
		virtual ~CurvePolynomial3Centered() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		float m_m;
		float m_M;
		float m_cM;
		float m_cm;
		float m_curveParam;
};


#endif

