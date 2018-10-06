#ifndef AXES_ROTATOR
#define AXES_ROTATOR


#include "JoystickChange.h"
#include <QString>
#include <QVector>
#include <tuple>
class AbstractRealJoystick;


class AxesRotator
{
	public:
		AxesRotator(AbstractRealJoystick *j);
		AxesRotator(const AxesRotator &other) = delete;
		AxesRotator(AxesRotator &&other) = delete;
		AxesRotator& operator=(const AxesRotator &other) = delete;
		AxesRotator& operator=(AxesRotator &&other) = delete;
		~AxesRotator() = default;
		
		bool rotateAxes(uint axis1, uint axis2, float angle);
		uint removeAxisRotation(uint axis);
		
		QVector<JoystickChange> changes();
		float axisValue(uint axis) const;
		
		
	private:
		int searchAxis(uint axis) const;
		
		AbstractRealJoystick *m_j;
		QVector<std::tuple<uint,uint,float>> m_rotations;
		QVector<uint> m_rotatedAxes;
		const float piSur180 = 3.14159265f / 180.0f;
};


#endif

