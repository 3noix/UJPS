#ifndef CURVE_POLYNOMIAL_3_NOTCENTERED
#define CURVE_POLYNOMIAL_3_NOTCENTERED


#include "AbstractAxisCurve.h"


class CurvePolynomial3NotCentered : public AbstractAxisCurve
{
	public:
		CurvePolynomial3NotCentered(float leftDZ = 0.0f, float rightDZ = 0.0f, float curve = 0.0f);
		CurvePolynomial3NotCentered(const CurvePolynomial3NotCentered &other) = delete;
		CurvePolynomial3NotCentered(CurvePolynomial3NotCentered &&other) = delete;
		CurvePolynomial3NotCentered& operator=(const CurvePolynomial3NotCentered &other) = delete;
		CurvePolynomial3NotCentered& operator=(CurvePolynomial3NotCentered &&other) = delete;
		virtual ~CurvePolynomial3NotCentered() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		float m_m;
		float m_M;
		float m_curveParam;
};

#endif
