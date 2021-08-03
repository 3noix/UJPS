#ifndef CURVE_EXP_CENTERED
#define CURVE_EXP_CENTERED


#include "AbstractAxisCurve.h"


class CurveExpCentered : public AbstractAxisCurve
{
	public:
		CurveExpCentered(float leftDZ, float centerDZ, float rightDZ, float curveParam, float zoom);
		CurveExpCentered(const CurveExpCentered &other) = delete;
		CurveExpCentered(CurveExpCentered &&other) = delete;
		CurveExpCentered& operator=(const CurveExpCentered &other) = delete;
		CurveExpCentered& operator=(CurveExpCentered &&other) = delete;
		virtual ~CurveExpCentered() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		float m_m;
		float m_M;
		float m_cM;
		float m_cm;
		float m_curveParam;
		float m_zoom;
};


#endif

