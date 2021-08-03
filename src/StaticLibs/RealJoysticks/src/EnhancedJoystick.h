#ifndef ENHANCED_JOYSTICK
#define ENHANCED_JOYSTICK


#include "AbstractRealJoystick.h"
#include "../../../../include/Other/AbsoluteOrRelative.h"
#include "AxesRotator.h"
#include <array>
class AbstractAxisCurve;


class EnhancedJoystick : public AbstractRealJoystick
{
	public:
		EnhancedJoystick(AbstractRealJoystick *j, bool bOwn = true);
		EnhancedJoystick(const EnhancedJoystick &other) = delete;
		EnhancedJoystick(EnhancedJoystick &&other) = delete;
		EnhancedJoystick& operator=(const EnhancedJoystick &other) = delete;
		EnhancedJoystick& operator=(EnhancedJoystick &&other) = delete;
		virtual ~EnhancedJoystick();
		
		// reimplemented functions
		virtual uint id() const override final;
		virtual QString description() const override final;
		virtual QString hardwareId() const override final;
		virtual void readGameController() override final;
		virtual QVector<JoystickChange> changes() override final;
		
		virtual uint buttonsCount() const override final;
		virtual bool buttonPressed(uint button) const override final;
		virtual QString buttonName(uint button) const override final;
		virtual QStringList buttonsNames() const override final;
		
		virtual uint axesCount() const override final;
		virtual float axisValue(uint axis) const override final;
		virtual QString axisName(uint axis) const override final;
		virtual QStringList axesNames() const override final;
		
		virtual uint povsCount() const override final;
		virtual float povValue(uint pov) const override final;
		virtual QString povName(uint pov) const override final;
		virtual QStringList povsNames() const override final;
		
		virtual void setData(const QString &str, QVariant v) override final;
		virtual void flush() override final;
		
		// axes rotations
		bool rotateAxes(uint axis1, uint axis2, float angle);
		bool removeAxisRotation(uint axis);
		
		
		// decoration functions
		void setButtonLocked(uint button, bool locked);
		void setAxisLocked(uint axis, bool locked);
		void setAxisTrim(uint axis, float trim, AbsoluteOrRelative aor = AbsoluteOrRelative::Absolute);
		float axisRawValue(uint axis) const;
		void setPovLocked(uint pov, bool locked);
		
		void setCurve(uint axis, AbstractAxisCurve *curve);
		void removeCurve(uint axis);
		
		
	private:
		void updateAxis(uint axis);
		
		AbstractRealJoystick *m_j;
		AxesRotator m_axesRotator;
		bool m_bOwn;
		
		std::array<bool,128> m_buttonsLocked;
		std::array<bool,128> m_buttonsValuesBeforeLock;
		
		std::array<bool,8> m_axesLocked;
		std::array<float,8> m_axesTrim;
		std::array<float,8> m_axesValuesBeforeLock;
		std::array<AbstractAxisCurve*,8> m_axesCurves;
		std::vector<uint> m_axesToUpdate;
		
		std::array<bool,4> m_povsLocked;
		std::array<float,4> m_povsValuesBeforeLock;
};


#endif

