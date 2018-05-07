// BROWSE HOSTILE TARGETS /////////////////////////////////////////////////////
void Profile::browseHostileTargets() {m_targetsTypeToCycle = 1;}

// BROWSE ALL TARGETS /////////////////////////////////////////////////////////
void Profile::browseAllTargets() {m_targetsTypeToCycle = 2;}

// BROWSE FRIEND TARGETS //////////////////////////////////////////////////////
void Profile::browseFriendTargets() {m_targetsTypeToCycle = 3;}

// BROWSE PINNED TARGETS //////////////////////////////////////////////////////
void Profile::browsePinnedTargets() {m_targetsTypeToCycle = 4;}


// PREVIOUS TARGET ////////////////////////////////////////////////////////////
void Profile::previousTarget()
{
	if (m_targetsTypeToCycle == 1)      {DoAction(new ActionButtonPulse{vj1,SC1::CycleHostileTargetsBack,ncPulse});}
	else if (m_targetsTypeToCycle == 2) {DoAction(new ActionButtonPulse{vj1,SC1::CycleAllTargetsBack,ncPulse});}
	else if (m_targetsTypeToCycle == 3) {DoAction(new ActionButtonPulse{vj1,SC1::CycleFriendlyTargetsBack,ncPulse});}
	else                                {DoAction(new ActionButtonPulse{vj1,SC1::CyclePinnedTargetsBack,ncPulse});}
}

// NEXT TARGET ////////////////////////////////////////////////////////////////
void Profile::nextTarget()
{
	if (m_targetsTypeToCycle == 1)      {DoAction(new ActionButtonPulse{vj1,SC1::CycleHostileTargets,ncPulse});}
	else if (m_targetsTypeToCycle == 2) {DoAction(new ActionButtonPulse{vj1,SC1::CycleAllTargets,ncPulse});}
	else if (m_targetsTypeToCycle == 3) {DoAction(new ActionButtonPulse{vj1,SC1::CycleFriendlyTargets,ncPulse});}
	else                                {DoAction(new ActionButtonPulse{vj1,SC1::CyclePinnedTargets,ncPulse});}
}

