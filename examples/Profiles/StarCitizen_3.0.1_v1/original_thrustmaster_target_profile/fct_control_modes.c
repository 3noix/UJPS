// setControlsGround
// setControlsFlightLanding
// setControlsFlightCruise
//
// set_JOYXY_for_turnNthrottle
// set_JOYXY_for_turnNbrake
// set_JOYXY_for_landing
// set_JOYXY_for_strafe
// set_JOYXY_for_rollNpitch
//
// set_S4_for_horn
// set_S4_for_landing
// set_S4_for_nothing
//
// set_BUTTONS_for_landing
// set_BUTTONS_for_cruise
//
// set_THR_for_nothing
// set_THR_for_ground
// set_THR_for_landing
// set_THR_for_cruise
//
// set_THRLEFT_for_groundForward
// set_THRLEFT_for_groundBackward
// set_THRLEFT_for_verticalStrafe
// set_THRLEFT_for_nothing
// set_THRRIGHT_for_flightThrottle
// set_THRRIGHT_for_nothing

include "curveParameters.c"

///////////////////////////////////////////////////////////
// MAIN FUNCTIONS /////////////////////////////////////////
///////////////////////////////////////////////////////////
int setControlsGround()
{
	if (1)
	{
		set_S4_for_horn();
		set_JOYXY_for_turnNbrake();
		set_BUTTONS_for_cruise();
		set_THR_for_ground();
	}
	else
	{
		set_S4_for_horn();
		set_JOYXY_for_turnNthrottle();
		set_BUTTONS_for_cruise();
		set_THR_for_nothing();
	}
	
	LAST_CONTROL_MODE = 0;
}

int setControlsFlightLanding()
{
	set_S4_for_landing(); // pour pouvoir repasser rapidement JOYXY sur rollNpitch rapidement
	set_JOYXY_for_landing();
	set_BUTTONS_for_landing();
	set_THR_for_landing();
	
	LAST_CONTROL_MODE = 1;
}

int setControlsFlightCruise()
{
	set_S4_for_nothing();
	set_JOYXY_for_rollNpitch();
	set_BUTTONS_for_cruise();
	set_THR_for_cruise();
	
	LAST_CONTROL_MODE = 2;
}


///////////////////////////////////////////////////////////
// JOYXY FUNCTIONS ////////////////////////////////////////
///////////////////////////////////////////////////////////
int set_JOYXY_for_turnNthrottle()
{
	MapAxis(&Joystick, JOYX, DX_X_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	MapAxis(&Joystick, JOYY, DX_Z_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	SetSCurve(&Joystick, JOYX, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	SetSCurve(&Joystick, JOYY, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	
	DXSetAxis(DX_Y_AXIS, 0);
	DXSetAxis(DX_XROT_AXIS, 0);
	DXSetAxis(DX_YROT_AXIS, 0);
	
	DXSetAxis(DX_X_AXIS, AxisVal(Joystick[JOYX],&axdata));
	DXSetAxis(DX_Z_AXIS, AxisVal(Joystick[JOYY],&axdata));
}

int set_JOYXY_for_turnNbrake()
{
	// joystick : turn et brake
	MapAxis(&Joystick, JOYX, DX_X_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	SetSCurve(&Joystick, JOYX, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	MapAxis(&Joystick, JOYY, 0, AXIS_NORMAL, MAP_ABSOLUTE);
	KeyAxis(&Joystick, JOYY, 0, AXMAP2(LIST(0,80,100), 0, Brake));
	SetSCurve(&Joystick, JOYY, 0, 0, 0, 0, 0);
	
	// on met les axes pitch et strafe a 0 (sinon ils gardent leurs dernieres valeurs)
	DXSetAxis(DX_Y_AXIS, 0);
	DXSetAxis(DX_XROT_AXIS, 0);
	DXSetAxis(DX_YROT_AXIS, 0);
	// et on met l'axe DX_X a la valeur qu'il faut (sinon il faut attendre un mouvement du stick)
	DXSetAxis(DX_X_AXIS, AxisVal(Joystick[JOYX],&axdata));
}

int set_JOYXY_for_landing()
{
	if (Joystick[S4])
		set_JOYXY_for_strafe();
	else
		set_JOYXY_for_rollNpitch();
}

int set_JOYXY_for_strafe()
{
	// joystick -> strafe
	MapAxis(&Joystick, JOYX, DX_XROT_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	MapAxis(&Joystick, JOYY, DX_YROT_AXIS, AXIS_REVERSED, MAP_ABSOLUTE);
	SetSCurve(&Joystick, JOYX, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	SetSCurve(&Joystick, JOYY, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	// on met les axes roll et pitch a 0 (sinon ils gardent leurs dernieres valeurs)
	DXSetAxis(DX_X_AXIS, 0);
	DXSetAxis(DX_Y_AXIS, 0);
	// et on met les axes strafe a la valeur qu'il faut (sinon il faut attendre un mouvement du stick)
	DXSetAxis(DX_XROT_AXIS, -AxisVal(Joystick[JOYX],&axdata));
	DXSetAxis(DX_YROT_AXIS, AxisVal(Joystick[JOYY],&axdata));
}

int set_JOYXY_for_rollNpitch()
{
	// joystick : roll et pitch
	MapAxis(&Joystick, JOYX, DX_X_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	MapAxis(&Joystick, JOYY, DX_Y_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	SetSCurve(&Joystick, JOYX, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	SetSCurve(&Joystick, JOYY, DeadZone_L, DeadZone_C, DeadZone_R, curveParam, 0);
	
	// on met les axes strafe a 0 (sinon ils gardent leurs dernieres valeurs)
	DXSetAxis(DX_XROT_AXIS, 0);
	DXSetAxis(DX_YROT_AXIS, 0);
	// et on met les axes roll et pitch a la valeur qu'il faut (sinon il faut attendre un mouvement du stick)
	DXSetAxis(DX_X_AXIS, AxisVal(Joystick[JOYX],&axdata));
	DXSetAxis(DX_Y_AXIS, AxisVal(Joystick[JOYY],&axdata));
}


///////////////////////////////////////////////////////////
// S4 FUNCTIONS ///////////////////////////////////////////
///////////////////////////////////////////////////////////
int set_S4_for_horn()
{
	MapKey(&Joystick, S4, Horn);
	MapKeyR(&Joystick, S4, 0);
}

int set_S4_for_landing()
{
	MapKey(&Joystick, S4,  EXEC("set_JOYXY_for_strafe();"));
	MapKeyR(&Joystick, S4,  EXEC("set_JOYXY_for_rollNpitch();"));
}

int set_S4_for_nothing()
{
	MapKey(&Joystick, S4, 0);
	MapKeyR(&Joystick, S4, 0);
}


///////////////////////////////////////////////////////////
// BUTTONS FUNCTIONS //////////////////////////////////////
///////////////////////////////////////////////////////////
int set_BUTTONS_for_landing()
{
	MapKeyIO(&Joystick, S1, TargetNearestHostile, CycleAllTargets); // pour cycler les plateformes d'atterrissage
	//MapKey(&Joystick, S2,  LandingTargetLockOnToggle); // pour selectionner une plateforme d'atterrissage
	MapKey(&Joystick, S2,  0);
	MapKey(&Joystick, H2U, StrafeUp);
	MapKey(&Joystick, H2D, StrafeDown);
	MapKey(&Joystick, H3U, StrafeForward);
	MapKey(&Joystick, H3D, StrafeBackwards);
}

int set_BUTTONS_for_cruise()
{
	MapKeyIO(&Joystick, S1, TargetNearestHostile, CycleHostileTargets);
	MapKey(&Joystick, S2,  LaunchMissile);
	MapKey(&Joystick, H2U, StrafeForward);
	MapKey(&Joystick, H2D, StrafeBackwards);
	MapKey(&Joystick, H3U, StrafeUp);
	MapKey(&Joystick, H3D, StrafeDown);
}


///////////////////////////////////////////////////////////
// THR FUNCTIONS //////////////////////////////////////////
///////////////////////////////////////////////////////////
int set_THR_for_nothing()
{
	SetSCurve(&Throttle, THR_LEFT, 0, 0, 0, 0, 0);
	SetSCurve(&Throttle, THR_RIGHT, 0, 0, 0, 0, 0);
	MapAxis(&Throttle, THR_LEFT, 0, AXIS_NORMAL, MAP_ABSOLUTE);
	MapAxis(&Throttle, THR_RIGHT, 0, AXIS_NORMAL, MAP_ABSOLUTE);
	MapKey(&Throttle, LTB,  0);
	MapKeyR(&Throttle, LTB, 0);
	DXSetAxis(DX_SLIDER_AXIS, 0); // on met l'axe de strafe vertical a 0 (sinon il garde sa derniere valeur)
}

int set_THR_for_ground()
{
	SetSCurve(&Throttle, THR_LEFT, 0, 0, 0, 0, 0);
	SetSCurve(&Throttle, THR_RIGHT, 0, 0, 0, 0, 0);
	MapAxis(&Throttle, THR_RIGHT, 0, AXIS_NORMAL, MAP_ABSOLUTE);
	
	if (Throttle[LTB])
		set_THRLEFT_for_groundBackward();
	else
		set_THRLEFT_for_groundForward();
	
	MapKey(&Throttle, LTB,  EXEC("set_THRLEFT_for_groundBackward();"));
	MapKeyR(&Throttle, LTB, EXEC("set_THRLEFT_for_groundForward();"));
}

int set_THR_for_landing()
{
	SetSCurve(&Throttle, THR_LEFT, 0, 0, 0, 0, 0);
	SetSCurve(&Throttle, THR_RIGHT, 0, 0, 0, 0, 0);
	set_THRRIGHT_for_flightThrottle();
	
	if (Throttle[LTB])
		set_THRLEFT_for_nothing();
	else
		set_THRLEFT_for_verticalStrafe();
	
	MapKey(&Throttle, LTB,  EXEC("set_THRLEFT_for_nothing();"));
	MapKeyR(&Throttle, LTB, EXEC("set_THRLEFT_for_verticalStrafe();"));
}

int set_THR_for_cruise()
{
	SetSCurve(&Throttle, THR_LEFT, 0, 0, 0, 0, 0);
	SetSCurve(&Throttle, THR_RIGHT, 0, 0, 0, 0, 0);
	set_THRRIGHT_for_flightThrottle();
	
	set_THRLEFT_for_nothing();
	MapKey(&Throttle, LTB,  0);
	MapKeyR(&Throttle, LTB, 0);
}


///////////////////////////////////////////////////////////
// THRLEFT / RIGHT FUNCTIONS //////////////////////////////
///////////////////////////////////////////////////////////
int set_THRLEFT_for_groundForward() // a modifier, ça doit pas etre comme ça !
{
	MapAxis(&Throttle, THR_LEFT, DX_Z_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	//TrimDXAxis(DX_Z_AXIS,SET(0));
	SetCustomCurve(&Throttle, THR_LEFT, LIST(0,50,  100,100));
	DXSetAxis(DX_Z_AXIS, -AxisVal(Throttle[THR_LEFT],&axdata));
	DXSetAxis(DX_SLIDER_AXIS, 0); // on met l'axe de strafe vertical a 0 (sinon il garde sa derniere valeur)
}

int set_THRLEFT_for_groundBackward() // a modifier, ça doit pas etre comme ça !
{
	MapAxis(&Throttle, THR_LEFT, DX_Z_AXIS, AXIS_NORMAL, MAP_ABSOLUTE);
	SetCustomCurve(&Throttle, THR_LEFT, LIST(0,50,  100,0));
	//TrimDXAxis(DX_Z_AXIS,SET(0));
	DXSetAxis(DX_Z_AXIS, -AxisVal(Throttle[THR_LEFT],&axdata));
	DXSetAxis(DX_SLIDER_AXIS, 0); // on met l'axe de strafe vertical a 0 (sinon il garde sa derniere valeur)
}

int set_THRLEFT_for_verticalStrafe()
{
	MapAxis(&Throttle, THR_LEFT, DX_SLIDER_AXIS, AXIS_REVERSED, MAP_ABSOLUTE);
	int reductionFactor = 5;
	int v1 = 50 - 50 / reductionFactor;
	int v2 = 50 + 50 / reductionFactor;
	SetCustomCurve(&Throttle, THR_LEFT, LIST(0,v1,  100,v2));
	TrimDXAxis(DX_SLIDER_AXIS,SET(AxisVal(Throttle[THR_LEFT],&axdata)/32));
	DXSetAxis(DX_SLIDER_AXIS, 0); // on met à 0 dans les 2 cas (passage sur APAH ou relachement de LTB) par sécurité
}

int set_THRLEFT_for_nothing()
{
	MapAxis(&Throttle, THR_LEFT, 0, AXIS_REVERSED, MAP_ABSOLUTE); // THR_LEFT ne fait rien (plus de strafe vertical)
	DXSetAxis(DX_SLIDER_AXIS, 0); // on met l'axe de strafe vertical a 0 (sinon il garde sa derniere valeur)
}

int set_THRRIGHT_for_flightThrottle()
{
	MapAxis(&Throttle, THR_RIGHT, DX_Z_AXIS, AXIS_NORMAL, MAP_ABSOLUTE); // THR_RIGHT s'occupe des gaz
	DXSetAxis(DX_Z_AXIS, -AxisVal(Throttle[THR_RIGHT],&axdata)); // on met l'axe a la bonne valeur (sinon il faut attendre que la manette bouge)
}

