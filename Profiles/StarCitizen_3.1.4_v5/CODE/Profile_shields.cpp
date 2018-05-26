// SWITCH SHIELDS MODES ///////////////////////////////////////////////////////
void Profile::switchShieldsMode()
{
	m_bShieldsHorizontalMode = !m_bShieldsHorizontalMode;
}

// SHIELDS DOWN ARROW /////////////////////////////////////////////////////////
void Profile::shieldsDownArrow()
{
	if (m_bShieldsHorizontalMode) {vj2->setButton(SC2::ShieldRaiseBack,true);}
	else {vj2->setButton(SC2::ShieldRaiseBottom,true);}
}

// SHIELDS UP ARROW ///////////////////////////////////////////////////////////
void Profile::shieldsUpArrow()
{
	if (m_bShieldsHorizontalMode) {vj2->setButton(SC2::ShieldRaiseFront,true);}
	else {vj2->setButton(SC2::ShieldRaiseTop,true);}
}

// RELEASE LONGI SHIELDS BUTTONS //////////////////////////////////////////////
void Profile::releaseLongiShieldsButtons()
{
	vj2->setButton(SC2::ShieldRaiseFront,false);
	vj2->setButton(SC2::ShieldRaiseBack,false);
	vj2->setButton(SC2::ShieldRaiseTop,false);
	vj2->setButton(SC2::ShieldRaiseBottom,false);
}

