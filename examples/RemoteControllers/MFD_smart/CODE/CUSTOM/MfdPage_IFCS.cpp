#include "MfdPage_IFCS.h"
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
MfdPage_IFCS::MfdPage_IFCS(QObject *parent) : AbstractMfdPage{parent}
{
	textGForceSafetyToggle = new MfdTextItem{"G-SAFE",  2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	textComStabToggle      = new MfdTextItem{"COMSTAB", 2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	textEspToggle          = new MfdTextItem{"ESP",     2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	
	textGForceSafetyToggle->setPos(g.x0,g.y1);
	textComStabToggle->setPos(g.x0,g.y2);
	textEspToggle->setPos(g.x0,g.y3);
	
	textMatchTargetVelocity = new MfdTextItem{"MTCH SPD", 2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textLandingGearToggle   = new MfdTextItem{"LNDG",     2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textAutoland            = new MfdTextItem{"AUTOLAND", 2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textQuantumDriveToggle  = new MfdTextItem{"QT",       2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	
	textMatchTargetVelocity->setPos(g.x6,g.y1);
	textLandingGearToggle->setPos(g.x6,g.y2);
	textAutoland->setPos(g.x6,g.y3);
	textQuantumDriveToggle->setPos(g.x6,g.y4);
}

// PROCESS ////////////////////////////////////////////////////////////////////
void MfdPage_IFCS::process(uint button, bool bPress)
{
	if (button == TMFD::OSB20)
	{
		emit buttonChanged2(MfdControls::GForceSafetyToggle,bPress);
		textGForceSafetyToggle->setActivated(bPress);
	}
	else if (button == TMFD::OSB19)
	{
		emit buttonChanged2(MfdControls::ComStabToggle,bPress);
		textComStabToggle->setActivated(bPress);
	}
	else if (button == TMFD::OSB18)
	{
		emit buttonChanged2(MfdControls::EspToggle,bPress);
		textEspToggle->setActivated(bPress);
	}
	else if (button == TMFD::OSB6)
	{
		emit buttonChanged2(MfdControls::MatchTargetVelocity,bPress);
		textMatchTargetVelocity->setActivated(bPress);
	}
	else if (button == TMFD::OSB7)
	{
		emit buttonChanged2(MfdControls::LandingGearToggle,bPress);
		textLandingGearToggle->setActivated(bPress);
	}
	else if (button == TMFD::OSB8)
	{
		emit buttonChanged2(MfdControls::Autoland,bPress);
		textAutoland->setActivated(bPress);
	}
	else if (button == TMFD::OSB9)
	{
		emit buttonChanged2(MfdControls::QuantumDriveToggle,bPress);
		textQuantumDriveToggle->setActivated(bPress);
	}
}

