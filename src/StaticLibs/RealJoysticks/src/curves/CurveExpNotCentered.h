#ifndef CURVE_EXP_NOTCENTERED
#define CURVE_EXP_NOTCENTERED


#include "AbstractAxisCurve.h"


class CurveExpNotCentered : public AbstractAxisCurve
{
	public:
		CurveExpNotCentered(float leftDZ, float rightDZ, float curveParam, float zoom);
		CurveExpNotCentered(const CurveExpNotCentered &other) = delete;
		CurveExpNotCentered(CurveExpNotCentered &&other) = delete;
		CurveExpNotCentered& operator=(const CurveExpNotCentered &other) = delete;
		CurveExpNotCentered& operator=(CurveExpNotCentered &&other) = delete;
		virtual ~CurveExpNotCentered() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		float m_m;
		float m_M;
		float m_curveParam;
		float m_zoom;
};


#endif

