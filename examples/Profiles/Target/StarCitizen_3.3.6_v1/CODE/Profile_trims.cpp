// RESET DXXY TRIMS ///////////////////////////////////////////////////////////
void Profile::reset_dxxy_trims()
{
	tmwj->setAxisTrim(TMWJ::JOYX,0.0f);
	tmwj->setAxisTrim(TMWJ::JOYY,0.0f);
}

// SET DXXY TRIMS /////////////////////////////////////////////////////////////
void Profile::set_dxxy_trims()
{
	tmwj->setAxisTrim(TMWJ::JOYX,-tmwj->axisRawValue(TMWJ::JOYX));
	tmwj->setAxisTrim(TMWJ::JOYY,-tmwj->axisRawValue(TMWJ::JOYY));
}

