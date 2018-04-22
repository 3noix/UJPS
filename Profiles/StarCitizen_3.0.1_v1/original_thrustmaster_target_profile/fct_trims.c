int reset_dxxy_trims()
{
	TrimDXAxis(DX_X_AXIS,SET(0));
	TrimDXAxis(DX_Y_AXIS,SET(0));
	TrimDXAxis(DX_XROT_AXIS,SET(0));
	TrimDXAxis(DX_YROT_AXIS,SET(0));
}

int set_dxxy_trims()
{
	TrimDXAxis(DX_X_AXIS,SET(-AxisVal(Joystick[JOYX],&axdata)/32));
	TrimDXAxis(DX_Y_AXIS,SET(-AxisVal(Joystick[JOYY],&axdata)/32));
	TrimDXAxis(DX_XROT_AXIS,SET(-AxisVal(Joystick[JOYX],&axdata)/32));
	TrimDXAxis(DX_YROT_AXIS,SET(-AxisVal(Joystick[JOYY],&axdata)/32));
}
