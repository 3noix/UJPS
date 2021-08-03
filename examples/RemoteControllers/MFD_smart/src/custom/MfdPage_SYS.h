#ifndef MFD_PAGE_SYSTEMS
#define MFD_PAGE_SYSTEMS


#include "AbstractMfdPage.h"
class MfdTextItem;


class MfdPage_SYS : public AbstractMfdPage
{
	Q_OBJECT
	
	public:
		explicit MfdPage_SYS(QObject *parent);
		MfdPage_SYS(const MfdPage_SYS &other) = delete;
		MfdPage_SYS(MfdPage_SYS &&other) = delete;
		MfdPage_SYS& operator=(const MfdPage_SYS &other) = delete;
		MfdPage_SYS& operator=(MfdPage_SYS &&other) = delete;
		virtual ~MfdPage_SYS() = default;
		
		virtual void process(uint button, bool bPress) override final;
		
		
	private:
		MfdTextItem *textFlightReady;
		MfdTextItem *textHeadLightsToggle;
		MfdTextItem *textOpenAllDoors;
		MfdTextItem *textCloseAllDoors;
		MfdTextItem *textLockAllDoors;
		MfdTextItem *textUnlockAllDoors;
};


#endif

