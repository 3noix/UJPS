#ifndef S_CURVE
#define S_CURVE


#include "AbstractAxisCurve.h"


class SCurve : public AbstractAxisCurve
{
	public:
		SCurve(float lowerDZ, float centerDZ, float upperDZ, float curve, float zoom);
		SCurve(const SCurve &other) = delete;
		SCurve(SCurve &&other) = delete;
		SCurve& operator=(const SCurve &other) = delete;
		SCurve& operator=(SCurve &&other) = delete;
		virtual ~SCurve() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		//in=-1..1, lower=0..1, center=0..1, upper=0..1, trim=-1..1, curve=-32..32
		float m_m;
		float m_M;
		float m_cM;
		float m_cm;
		float m_curve;
		float m_zoom;
};

#endif
