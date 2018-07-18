#ifndef MAPPING_MERGE_AXES
#define MAPPING_MERGE_AXES


#include "AbstractMapping.h"
class AbstractAxisCurve;


class MappingMergeAxes : public AbstractMapping
{
	public:
		MappingMergeAxes(AbstractRealJoystick *rj1, uint rAxis1, float k1,
						AbstractRealJoystick *rj2, uint rAxis2, float k2,
						LayersCombo lc,
						VirtualJoystick *vj, uint vAxis,
						AbstractAxisCurve *curve,
						VirtualEventsQueue &eventsQueue);
						
		MappingMergeAxes(const MappingMergeAxes &other) = delete;
		MappingMergeAxes(MappingMergeAxes &&other) = delete;
		MappingMergeAxes& operator=(const MappingMergeAxes &other) = delete;
		MappingMergeAxes& operator=(MappingMergeAxes &&other) = delete;
		virtual ~MappingMergeAxes();
		
		virtual bool reactsToChanges() const override final;
		virtual bool reactsToStates() const override final;
		virtual bool isTriggered() override final;
		virtual bool isTriggered(const JoystickChange &ch) override final;
		virtual bool isMappingButton(AbstractRealJoystick *rj, uint rButton) const override final;
		virtual bool isMappingAxis(AbstractRealJoystick *rj, uint rAxis) const override final;
		virtual bool isMappingPov(AbstractRealJoystick *rj, uint rPov) const override final;
		virtual void performAction() override final;
		virtual void performAction(const JoystickChange &ch) override final;
		
		virtual void activateByLayerChange() override final;
		virtual void deactivateByLayerChange()  override final;
		virtual void aboutToBeDeleted() override final;
		
		
	private:
		AbstractRealJoystick *m_rj1, *m_rj2;
		float m_k1, m_k2;
		VirtualJoystick *m_vj;
		uint m_rAxis1, m_rAxis2, m_vAxis;
		AbstractAxisCurve *m_curve;
		
		bool m_disable;
};

#endif

