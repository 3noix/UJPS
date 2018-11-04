#ifndef MFD_PAGE_IFCS
#define MFD_PAGE_IFCS


#include "AbstractMfdPage.h"
class MfdTextItem;


class MfdPage_IFCS : public AbstractMfdPage
{
	Q_OBJECT
	
	public:
		explicit MfdPage_IFCS(QObject *parent);
		MfdPage_IFCS(const MfdPage_IFCS &other) = delete;
		MfdPage_IFCS(MfdPage_IFCS &&other) = delete;
		MfdPage_IFCS& operator=(const MfdPage_IFCS &other) = delete;
		MfdPage_IFCS& operator=(MfdPage_IFCS &&other) = delete;
		virtual ~MfdPage_IFCS() = default;
		
		virtual void process(uint button, bool bPress) override final;
		
		
	private:
		MfdTextItem *textMatchTargetVelocity;
		MfdTextItem *textGForceSafetyToggle;
		MfdTextItem *textComStabToggle;
		MfdTextItem *textEspToggle;
		MfdTextItem *textLandingGearToggle;
		MfdTextItem *textAutoland;
		MfdTextItem *textQuantumDriveToggle;
};


#endif

