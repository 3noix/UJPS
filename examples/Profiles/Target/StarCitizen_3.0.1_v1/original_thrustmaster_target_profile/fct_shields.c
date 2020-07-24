int switchShieldsMode()
{
	B_SHIELDS_HORZ_MODE = !B_SHIELDS_HORZ_MODE;
	//if (B_SHIELDS_HORZ_MODE) {printf("Shields horizontal mode ON\xa");}
	//else {printf("Shields horizontal mode OFF\xa");}
}

int shieldsDownArrow()
{
	if (B_SHIELDS_HORZ_MODE) {ActKey(KEYON+ShieldRaiseBack);}
	else {ActKey(KEYON+ShieldRaiseBottom);}
}

int shieldsUpArrow()
{
	if (B_SHIELDS_HORZ_MODE) {ActKey(KEYON+ShieldRaiseFront);}
	else {ActKey(KEYON+ShieldRaiseTop);}
}

int releaseLongiShieldsButtons()
{
	ActKey(ShieldRaiseFront);
	ActKey(ShieldRaiseBack);
	ActKey(ShieldRaiseTop);
	ActKey(ShieldRaiseBottom);
}
