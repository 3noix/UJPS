// SWITCH SHIELDS MODES ///////////////////////////////////////////////////////
void Profile::switchShieldsMode()
{
	m_bShieldsHorizontalMode = !m_bShieldsHorizontalMode;
}

// SHIELDS DOWN ARROW /////////////////////////////////////////////////////////
void Profile::shieldsDownArrow()
{
	if (m_bShieldsHorizontalMode) {vj1->setButton(SC1::ShieldRaiseBack,true);}
	else {vj1->setButton(SC1::ShieldRaiseBottom,true);}
}

// SHIELDS UP ARROW ///////////////////////////////////////////////////////////
void Profile::shieldsUpArrow()
{
	if (m_bShieldsHorizontalMode) {vj1->setButton(SC1::ShieldRaiseFront,true);}
	else {vj1->setButton(SC1::ShieldRaiseTop,true);}
}

// RELEASE LONGI SHIELDS BUTTONS //////////////////////////////////////////////
void Profile::releaseLongiShieldsButtons()
{
	vj1->setButton(SC1::ShieldRaiseFront,false);
	vj1->setButton(SC1::ShieldRaiseBack,false);
	vj1->setButton(SC1::ShieldRaiseTop,false);
	vj1->setButton(SC1::ShieldRaiseBottom,false);
}

