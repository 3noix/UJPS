// SET CONTROLS GROUND ////////////////////////////////////////////////////////
void Profile::setControlsGround()
{
	if (bUseLed)
	{
		tmwt->setData("LED1",true);
		tmwt->setData("LED2",false);
		tmwt->setData("LED3",false);
	}
	
	vj1->setAxis(SC1::AxisFlightRoll, 0.0f);
	vj1->setAxis(SC1::AxisFlightPitch, 0.0f);
	vj1->setAxis(SC1::AxisFlightThrust, 0.0f);
	vj1->setAxis(SC1::AxisFlightStrafeLat, 0.0f);
	vj1->setAxis(SC1::AxisFlightStrafeLongi, 0.0f);
	vj1->setAxis(SC1::AxisFlightYaw, 0.0f);
	vj1->setAxis(SC1::AxisFlightStrafeVertical, 0.0f);
	
	this->set_S4_for_horn();
	this->set_JOYXY_for_turn();
	this->set_BUTTONS_for_cruise();
	this->set_THR_and_pedals();
}

// SET CONTROLS FLIGHT LANDING ////////////////////////////////////////////////
void Profile::setControlsFlightLanding()
{
	if (bUseLed)
	{
		tmwt->setData("LED1",false);
		tmwt->setData("LED2",true);
		tmwt->setData("LED3",false);
	}
	
	vj2->setAxis(SC2::AxisGroundLat, 0.0f);
	vj2->setAxis(SC2::AxisGroundThrust, 0.0f);
	vj2->setButton(SC2::Brake,false);
	
	this->set_S4_for_landing(); // to quickly switch JOYXY from roll&pitch to strafe and vice-versa
	this->set_JOYXY_for_landing();
	this->set_BUTTONS_for_landing();
	this->set_THR_for_landing();
}

// SET CONTROLS FLIGHT CRUISE /////////////////////////////////////////////////
void Profile::setControlsFlightCruise()
{
	if (bUseLed)
	{
		tmwt->setData("LED1",false);
		tmwt->setData("LED2",false);
		tmwt->setData("LED3",true);
	}
	
	vj2->setAxis(SC2::AxisGroundLat, 0.0f);
	vj2->setAxis(SC2::AxisGroundThrust, 0.0f);
	vj2->setButton(SC2::Brake,false);
	vj1->setAxis(SC1::AxisFlightStrafeVertical, 0.0f);
	
	this->set_S4_for_nothing();
	this->set_JOYXY_for_rollNpitch();
	this->set_BUTTONS_for_cruise();
	this->set_THR_for_cruise();
}








// set_S4_for_horn
// set_S4_for_landing
// set_S4_for_nothing
void Profile::set_S4_for_horn()
{
	UnmapButton(tmwj, TMWJ::S4);
	MapButton(tmwj, TMWJ::S4, AllLayers, vj2, SC2::Horn);
}

void Profile::set_S4_for_landing()
{
	UnmapButton(tmwj, TMWJ::S4);
	Map(tmwj, ControlType::Button, TMWJ::S4, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_JOYXY_for_strafe();}});
	Map(tmwj, ControlType::Button, TMWJ::S4, AllLayers, new TriggerButtonRelease{}, new ActionCallback{[this]() {this->set_JOYXY_for_rollNpitch();}});
}

void Profile::set_S4_for_nothing()
{
	UnmapButton(tmwj, TMWJ::S4);
}








// set_JOYXY_for_turn
// set_JOYXY_for_landing
// set_JOYXY_for_strafe
// set_JOYXY_for_rollNpitch
void Profile::set_JOYXY_for_turn()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj2, SC2::AxisGroundLat, AxisDirection::Normal);
	vj2->setAxis(SC2::AxisGroundLat, tmwj->axisValue(TMWJ::JOYX));
}

void Profile::set_JOYXY_for_landing()
{
	if (tmwj->buttonPressed(TMWJ::S4))
		this->set_JOYXY_for_strafe();
	else
		this->set_JOYXY_for_rollNpitch();
}

void Profile::set_JOYXY_for_strafe()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	// set roll and pitch axes at 0, otherwise they keep their last values
	vj1->setAxis(SC1::AxisFlightRoll, 0.0f);
	vj1->setAxis(SC1::AxisFlightPitch, 0.0f);
	
	// joystick -> strafe
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, SC1::AxisFlightStrafeLat, AxisDirection::Normal);
	MapAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, SC1::AxisFlightStrafeLongi, AxisDirection::Reversed);
	
	// set strafe axes at correct value, otherwise it is necessary to wait for a movement of the stick
	vj1->setAxis(SC1::AxisFlightStrafeLat, tmwj->axisValue(TMWJ::JOYX));
	vj1->setAxis(SC1::AxisFlightStrafeLongi, -tmwj->axisValue(TMWJ::JOYY));
	vj2->setButton(SC2::Brake,false);
}

void Profile::set_JOYXY_for_rollNpitch()
{
	UnmapAxis(tmwj, TMWJ::JOYX);
	UnmapAxis(tmwj, TMWJ::JOYY);
	
	// set strafe axes at 0, otherwise they keep their last values
	vj1->setAxis(SC1::AxisFlightStrafeLat, 0.0f);
	vj1->setAxis(SC1::AxisFlightStrafeLongi, 0.0f);
	
	// joystick : roll and pitch
	MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, SC1::AxisFlightRoll, AxisDirection::Normal);
	MapAxis(tmwj, TMWJ::JOYY, AllLayers, vj1, SC1::AxisFlightPitch, AxisDirection::Normal);
	
	// set roll and pitch axes at correct value, otherwise it is necessary to wait for a movement of the stick
	vj1->setAxis(SC1::AxisFlightRoll, tmwj->axisValue(TMWJ::JOYX));
	vj1->setAxis(SC1::AxisFlightPitch, tmwj->axisValue(TMWJ::JOYY));
	vj2->setButton(SC2::Brake,false);
}





// set_BUTTONS_for_landing
// set_BUTTONS_for_cruise
void Profile::set_BUTTONS_for_landing()
{
	UnmapButton(tmwj, TMWJ::S1);
	UnmapButton(tmwj, TMWJ::S2);
	UnmapButton(tmwj, TMWJ::H2U);
	UnmapButton(tmwj, TMWJ::H2D);
	UnmapButton(tmwj, TMWJ::H3U);
	UnmapButton(tmwj, TMWJ::H3D);
	
	MapButton(tmwj, TMWJ::S1, {"i"}, vj1, SC1::TargetNearestHostile);
	MapButton(tmwj, TMWJ::S1, {"o"}, vj1, SC1::CycleAllTargets); // to cycle landing pads
	//MapButton(tmwj, TMWJ::S2, AllLayers, vj1, SC1::LandingTargetLockOnToggle); // to select a landing pad
	
	MapButton(tmwj, TMWJ::H2U, AllLayers, vj1, SC1::StrafeUp);
	MapButton(tmwj, TMWJ::H2D, AllLayers, vj1, SC1::StrafeDown);
	MapButton(tmwj, TMWJ::H3U, AllLayers, vj1, SC1::StrafeForward);
	MapButton(tmwj, TMWJ::H3D, AllLayers, vj1, SC1::StrafeBackwards);
}

void Profile::set_BUTTONS_for_cruise()
{
	UnmapButton(tmwj, TMWJ::S1);
	UnmapButton(tmwj, TMWJ::S2);
	UnmapButton(tmwj, TMWJ::H2U);
	UnmapButton(tmwj, TMWJ::H2D);
	UnmapButton(tmwj, TMWJ::H3U);
	UnmapButton(tmwj, TMWJ::H3D);
	
	MapButton(tmwj, TMWJ::S1, {"i"}, vj1, SC1::TargetNearestHostile);
	MapButton(tmwj, TMWJ::S1, {"o"}, vj1, SC1::CycleHostileTargets);
	MapButton(tmwj, TMWJ::S2, AllLayers, vj1, SC1::LaunchMissile);
	
	MapButton(tmwj, TMWJ::H2U, AllLayers, vj1, SC1::StrafeForward);
	MapButton(tmwj, TMWJ::H2D, AllLayers, vj1, SC1::StrafeBackwards);
	MapButton(tmwj, TMWJ::H3U, AllLayers, vj1, SC1::StrafeUp);
	MapButton(tmwj, TMWJ::H3D, AllLayers, vj1, SC1::StrafeDown);
}


// reset_THR_and_pedals
// set_THR_and_pedals
// set_THR_for_nothing
// set_THR_for_landing
// set_THR_for_cruise
void Profile::reset_THR_and_pedals()
{
	UnmapAxis(mfgx, MFGX::BRK_LEFT);
	UnmapAxis(mfgx, MFGX::BRK_RIGHT);
	this->set_THRLEFT_for_nothing();
	UnmapAxis(tmwt, TMWT::THR_RIGHT);
	tmwt->removeCurve(TMWT::THR_LEFT);
	tmwt->removeCurve(TMWT::THR_RIGHT);
	UnmapButton(tmwt, TMWT::LTB);
}

void Profile::set_THR_and_pedals()
{
	this->reset_THR_and_pedals();
	
	// mapping BRK_RIGHT function of THR_RIGHT position
	MapAxis2(tmwt, TMWT::THR_RIGHT, AllLayers, 1, {
		new ActionCallback{[this](){this->set_BRKRIGHT_for_groundForward();}},
		new ActionCallback{[this](){this->set_BRKRIGHT_for_groundBackward();}}
	});
	if (tmwt->axisValue(TMWT::THR_RIGHT) < 0)
		this->set_BRKRIGHT_for_groundForward();
	else
		this->set_BRKRIGHT_for_groundBackward();
	
	// mapping BRK_LEFT for brake
	Map(mfgx, ControlType::Axis, MFGX::BRK_LEFT, AllLayers, new TriggerAxisChangeComparison{true,thrBreak}, new ActionButtonPress{vj2,SC2::Brake});
	Map(mfgx, ControlType::Axis, MFGX::BRK_LEFT, AllLayers, new TriggerAxisChangeComparison{false,thrBreak}, new ActionButtonRelease{vj2,SC2::Brake});
	bool bBreak = mfgx->axisValue(MFGX::BRK_LEFT) > thrBreak;
	vj2->setButton(SC2::Brake, bBreak);
}

void Profile::set_THR_for_landing()
{
	this->reset_THR_and_pedals();
	
	// mapping THR_RIGHT and THR_LEFT
	this->set_THRRIGHT_for_flightThrottle();
	if (tmwt->buttonPressed(TMWT::LTB))
		this->set_THRLEFT_for_nothing();
	else
		this->set_THRLEFT_for_verticalStrafe();
	
	// mapping LTB (to switch the role of THR_LEFT)
	Map(tmwt, ControlType::Button, TMWT::LTB, AllLayers, new TriggerButtonPress{}, new ActionCallback{[this]() {this->set_THRLEFT_for_nothing();}});
	Map(tmwt, ControlType::Button, TMWT::LTB, AllLayers, new TriggerButtonRelease{}, new ActionCallback{[this]() {this->set_THRLEFT_for_verticalStrafe();}});
}

void Profile::set_THR_for_cruise()
{
	this->reset_THR_and_pedals();
	this->set_THRRIGHT_for_flightThrottle();
	this->set_THRLEFT_for_nothing();
}


// set_BRKRIGHT_for_groundForward
// set_BRKRIGHT_for_groundBackward
// set_THRLEFT_for_verticalStrafe
// set_THRLEFT_for_nothing
// set_THRRIGHT_for_flightThrottle
void Profile::set_BRKRIGHT_for_groundForward()
{
	MapAxis(mfgx, MFGX::BRK_RIGHT, AllLayers, vj2, SC2::AxisGroundThrust, AxisDirection::Normal);
	mfgx->setCustomCurve(MFGX::BRK_RIGHT, {-1.0f+2.0f*brkRight_LDZ,0.0f,  1.0f-2.0f*brkRight_RDZ,1.0f});
	vj2->setAxis(SC2::AxisGroundThrust, mfgx->axisValue(MFGX::BRK_RIGHT));
}

void Profile::set_BRKRIGHT_for_groundBackward()
{
	MapAxis(mfgx, MFGX::BRK_RIGHT, AllLayers, vj2, SC2::AxisGroundThrust, AxisDirection::Normal);
	mfgx->setCustomCurve(MFGX::BRK_RIGHT, {-1.0f+2.0f*brkRight_LDZ,0.0f,  1.0f-2.0f*brkRight_RDZ,-1.0f});
	vj2->setAxis(SC2::AxisGroundThrust, mfgx->axisValue(MFGX::BRK_RIGHT));
}

void Profile::set_THRLEFT_for_verticalStrafe()
{
	MapAxis(tmwt, TMWT::THR_LEFT, AllLayers, vj1, SC1::AxisFlightStrafeVertical, AxisDirection::Reversed);
	float reductionFactor = 0.2f;
	tmwt->setCustomCurve(TMWT::THR_LEFT, {-1.0f,-reductionFactor,  1.0f,reductionFactor});
	vj1->setAxis(SC1::AxisFlightStrafeVertical, 0.0f);
	vj1->setAxisTrim(SC1::AxisFlightStrafeVertical, tmwt->axisValue(TMWT::THR_LEFT));
}

void Profile::set_THRLEFT_for_nothing()
{
	UnmapAxis(tmwt, TMWT::THR_LEFT);
	vj1->setAxis(SC1::AxisFlightStrafeVertical, 0.0f); // set vertical strafe axis at 0, otherwise they keep their last values
}

void Profile::set_THRRIGHT_for_flightThrottle()
{
	MapAxis(tmwt, TMWT::THR_RIGHT, AllLayers, vj1, SC1::AxisFlightThrust, AxisDirection::Normal); // THR_RIGHT mapped to thrust
	vj1->setAxis(SC1::AxisFlightThrust, tmwt->axisValue(TMWT::THR_RIGHT)); // set axis at correct value, otherwise it is necessary to wait for a movement of the throttle
}


