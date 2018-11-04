#ifndef MFD_PAGE_POWER
#define MFD_PAGE_POWER


#include "AbstractMfdPage.h"
class MfdTextItem;
class QGraphicsSimpleTextItem;


class MfdPage_PWR : public AbstractMfdPage
{
	Q_OBJECT
	
	public:
		explicit MfdPage_PWR(QObject *parent);
		MfdPage_PWR(const MfdPage_PWR &other) = delete;
		MfdPage_PWR(MfdPage_PWR &&other) = delete;
		MfdPage_PWR& operator=(const MfdPage_PWR &other) = delete;
		MfdPage_PWR& operator=(MfdPage_PWR &&other) = delete;
		virtual ~MfdPage_PWR() = default;
		
		virtual void process(uint button, bool bPress) override final;
		
		
	private:
		MfdTextItem *textPowerPreset1Increase;
		MfdTextItem *textPowerPreset2Increase;
		MfdTextItem *textPowerPreset3Increase;
		MfdTextItem *textResetPowerDistribution;
		
		MfdTextItem *textPowerPreset1OnOff;
		MfdTextItem *textPowerPreset2OnOff;
		MfdTextItem *textPowerPreset3OnOff;
		MfdTextItem *textPowerOnOff;
};


#endif

