int browseHostileTargets()
{
	NUM_TARGET_MODE = 1;
}

int browseAllTargets()
{
	NUM_TARGET_MODE = 2;
}

int browseFriendTargets()
{
	NUM_TARGET_MODE = 3;
}

int browsePinnedTargets()
{
	NUM_TARGET_MODE = 4;
}

int previousTarget()
{
	if (NUM_TARGET_MODE == 1)      {ActKey(KEYON+CycleHostileTargetsBack);}
	else if (NUM_TARGET_MODE == 2) {ActKey(KEYON+CycleAllTargetsBack);}
	else if (NUM_TARGET_MODE == 3) {ActKey(KEYON+CycleFriendlyTargetsBack);}
	else                           {ActKey(KEYON+CyclePinnedTargetsBack);}
}

int nextTarget()
{
	if (NUM_TARGET_MODE == 1)      {ActKey(KEYON+CycleHostileTargets);}
	else if (NUM_TARGET_MODE == 2) {ActKey(KEYON+CycleAllTargets);}
	else if (NUM_TARGET_MODE == 3) {ActKey(KEYON+CycleFriendlyTargets);}
	else                           {ActKey(KEYON+CyclePinnedTargets);}
}
