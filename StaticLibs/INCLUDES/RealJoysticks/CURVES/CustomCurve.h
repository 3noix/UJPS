#ifndef CUSTOM_CURVE
#define CUSTOM_CURVE


#include "AbstractAxisCurve.h"
#include <vector>


class CustomCurve : public AbstractAxisCurve
{
	public:
		CustomCurve(const std::vector<float> &points);
		CustomCurve(const CustomCurve &other) = delete;
		CustomCurve(CustomCurve &&other) = delete;
		CustomCurve& operator=(const CustomCurve &other) = delete;
		CustomCurve& operator=(CustomCurve &&other) = delete;
		virtual ~CustomCurve() = default;
		
		virtual float run(float in) override final;
		
		
	private:
		static float linear_interpolation(float in, const std::vector<float> &x, const std::vector<float> &y);
		
		std::vector<float> m_x;
		std::vector<float> m_y;
};

#endif
