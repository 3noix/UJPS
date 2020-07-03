#include "MfdPage_SYS.h"
#include "MfdTextItem.h"
#include "../DEFAULT/Geometry.h"

#include "../MfdControls.h"
#include "ThrustmasterMfdCougar.h"
namespace TMFD = ThrustmasterMfdCougar;


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  PROCESS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MfdPage_SYS::MfdPage_SYS(QObject *parent) : AbstractMfdPage{parent}
{
	textFlightReady      = new MfdTextItem{"FLT READY", 2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	textHeadLightsToggle = new MfdTextItem{"LIGHTS",    2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	
	textFlightReady->setPos(g.x0,g.y1);
	textHeadLightsToggle->setPos(g.x0,g.y2);
	
	textOpenAllDoors   = new MfdTextItem{"OPEN DOORS",   2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textCloseAllDoors  = new MfdTextItem{"CLOSE DOORS",  2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textLockAllDoors   = new MfdTextItem{"LOCK DOORS",   2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textUnlockAllDoors = new MfdTextItem{"UNLOCK DOORS", 2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	
	textOpenAllDoors->setPos(g.x6,g.y1);
	textCloseAllDoors->setPos(g.x6,g.y2);
	textLockAllDoors->setPos(g.x6,g.y3);
	textUnlockAllDoors->setPos(g.x6,g.y4);
}

// PROCESS ////////////////////////////////////////////////////////////////////
void MfdPage_SYS::process(uint button, bool bPress)
{
	if (button == TMFD::OSB20)
	{
		emit buttonChanged2(MfdControls::FlightReady,bPress);
		textFlightReady->setActivated(bPress);
	}
	else if (button == TMFD::OSB19)
	{
		emit buttonChanged2(MfdControls::HeadLightsToggle,bPress);
		textHeadLightsToggle->setActivated(bPress);
	}
	else if (button == TMFD::OSB6)
	{
		emit buttonChanged2(MfdControls::OpenAllDoors,bPress);
		textOpenAllDoors->setActivated(bPress);
	}
	else if (button == TMFD::OSB7)
	{
		emit buttonChanged2(MfdControls::CloseAllDoors,bPress);
		textCloseAllDoors->setActivated(bPress);
	}
	else if (button == TMFD::OSB8)
	{
		emit buttonChanged2(MfdControls::LockAllDoors,bPress);
		textLockAllDoors->setActivated(bPress);
	}
	else if (button == TMFD::OSB9)
	{
		emit buttonChanged2(MfdControls::UnlockAllDoors,bPress);
		textUnlockAllDoors->setActivated(bPress);
	}
}

