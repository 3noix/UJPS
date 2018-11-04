#include "MfdPage_PWR.h"
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
MfdPage_PWR::MfdPage_PWR(QObject *parent) : AbstractMfdPage{parent}
{
	textPowerPreset1Increase   = new MfdTextItem{"PWR WEAP +",   2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	textPowerPreset2Increase   = new MfdTextItem{"PWR SHLD +",   2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	textPowerPreset3Increase   = new MfdTextItem{"PWR ENG  +",   2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	textResetPowerDistribution = new MfdTextItem{"RESET DISTRIB",2.0, Qt::AlignVCenter | Qt::AlignLeft, this};
	
	textPowerPreset1Increase->setPos(g.x0,g.y1);
	textPowerPreset2Increase->setPos(g.x0,g.y2);
	textPowerPreset3Increase->setPos(g.x0,g.y3);
	textResetPowerDistribution->setPos(g.x0,g.y4);
	
	textPowerPreset1OnOff = new MfdTextItem{"WEAP ON/OFF", 2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textPowerPreset2OnOff = new MfdTextItem{"SHLD ON/OFF", 2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textPowerPreset3OnOff = new MfdTextItem{"ENG  ON/OFF", 2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	textPowerOnOff        = new MfdTextItem{"ON/OFF",      2.0, Qt::AlignVCenter | Qt::AlignRight, this};
	
	textPowerPreset1OnOff->setPos(g.x6,g.y1);
	textPowerPreset2OnOff->setPos(g.x6,g.y2);
	textPowerPreset3OnOff->setPos(g.x6,g.y3);
	textPowerOnOff->setPos(g.x6,g.y4);
}

// PROCESS ////////////////////////////////////////////////////////////////////
void MfdPage_PWR::process(uint button, bool bPress)
{
	if (button == TMFD::OSB20)
	{
		emit buttonChanged2(MfdControls::PowerPreset1Increase,bPress);
		textPowerPreset1Increase->setActivated(bPress);
	}
	else if (button == TMFD::OSB19)
	{
		emit buttonChanged2(MfdControls::PowerPreset2Increase,bPress);
		textPowerPreset2Increase->setActivated(bPress);
	}
	else if (button == TMFD::OSB18)
	{
		emit buttonChanged2(MfdControls::PowerPreset3Increase,bPress);
		textPowerPreset3Increase->setActivated(bPress);
	}
	else if (button == TMFD::OSB17)
	{
		emit buttonChanged2(MfdControls::ResetPowerDistribution,bPress);
		textResetPowerDistribution->setActivated(bPress);
	}
	else if (button == TMFD::OSB6)
	{
		emit buttonChanged2(MfdControls::PowerPreset1OnOff,bPress);
		textPowerPreset1OnOff->setActivated(bPress);
	}
	else if (button == TMFD::OSB7)
	{
		emit buttonChanged2(MfdControls::PowerPreset2OnOff,bPress);
		textPowerPreset2OnOff->setActivated(bPress);
	}
	else if (button == TMFD::OSB8)
	{
		emit buttonChanged2(MfdControls::PowerPreset3OnOff,bPress);
		textPowerPreset3OnOff->setActivated(bPress);
	}
	else if (button == TMFD::OSB9)
	{
		emit buttonChanged2(MfdControls::PowerOnOff,bPress);
		textPowerOnOff->setActivated(bPress);
	}
}

