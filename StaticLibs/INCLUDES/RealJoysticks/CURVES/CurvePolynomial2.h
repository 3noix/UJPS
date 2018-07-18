#ifndef J_CURVE
#define J_CURVE


#include "AbstractAxisCurve.h"


class CurvePolynomial2 : public AbstractAxisCurve
{
	public:
		CurvePolynomial2(float zoom);
		CurvePolynomial2(const CurvePolynomial2 &other) = delete;
		CurvePolynomial2(CurvePolynomial2 &&other) = delete;
		CurvePolynomial2& operator=(const CurvePolynomial2 &other) = delete;
		CurvePolynomial2& operator=(CurvePolynomial2 &&other) = delete;
		virtual ~CurvePolynomial2() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		float m_zoom;
};

#endif
