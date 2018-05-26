// LED BRIGHTNESS DOWN ////////////////////////////////////////////////////////
void Profile::ledBrightnessDown()
{
	if (m_brightness > 0)
	{
		m_brightness = lim<quint8>(m_brightness-1,0,5);
		tmwt->setData("BRIGHTNESS",m_brightness);
	}
}

// LED BRIGHTNESS UP //////////////////////////////////////////////////////////
void Profile::ledBrightnessUp()
{
	if (m_brightness < 5)
	{
		m_brightness = lim<quint8>(m_brightness+1,0,5);
		tmwt->setData("BRIGHTNESS",m_brightness);
	}
}

// TOGGLE BACKLIT /////////////////////////////////////////////////////////////
void Profile::toggleBacklit()
{
	m_bBacklit = !m_bBacklit;
	tmwt->setData("BACKLIT",m_bBacklit);
}



