#ifndef ABSTRACT_AXIS_CURVE
#define ABSTRACT_AXIS_CURVE


class AbstractAxisCurve
{
	public:
		AbstractAxisCurve() = default;
		AbstractAxisCurve(const AbstractAxisCurve &other) = delete;
		AbstractAxisCurve(AbstractAxisCurve &&other) = delete;
		AbstractAxisCurve& operator=(const AbstractAxisCurve &other) = delete;
		AbstractAxisCurve& operator=(AbstractAxisCurve &&other) = delete;
		virtual ~AbstractAxisCurve() = default;
		
		virtual float run(float in) = 0;
};

#endif
